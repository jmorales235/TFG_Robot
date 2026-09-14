#include <Arduino.h>
#include <libreria_robot.h> 
/*los ficheros .h y.cpp que nos creamos como usuario deben estar en una carpeta llamada "libraries" situada en el "sketchbook location" definido en "Preferences", para que el compilador las vea.
asegurarse de que la extension real de los ficheros sean .h y .cpp y NO sea .txt,para ello habilitar la opcion visualizar extension de fichero en windows.
dentro de libraries ya hacemos una carpeta que se llame como el fichero .h y .cpp que deben estar dentro.*/

#include <config_pines_arduino.h> //en este fichero mapeamos las variables de pin a los pines fisicos de arduino con directivas #define
/*config_pines define las señales: dir_y, pul_y, ena_y, dir_x ,dir_x ,pul_x ,ena_x, dir_z, pul_z ,ena_z ,bomba ,pin_servo ,sensor_x ,sensor_y ,sensor_z
*/

//////////////////////////////////////////////////////////////
// ESTRUCTURAS
//////////////////////////////////////////////////////////////

struct Bandeja   //Variable tipo estructura. Representa los datos característicos de una bandeja tipo JEDEC
{
    long x0; //coordenadas EN PASOS de la primera celda de la bandeja en esquina superior izquierda
    long y0;

    long pasoX; //numero de pasos que hay entre celdas consecutivas de la bandeja.
    long pasoY;

    int filas; //numero total de filas en bandeja
    int columnas; //numero otal de columnas en bandeja
};

struct Celda //Variable tipo estructura. Representa una coordenada en formato (x,y) de una bandeja,tanto de origen como destino
{
    int fila;
    int columna;
};

//////////////////////////////////////////////////////////////
// PINES
//////////////////////////////////////////////////////////////

const int dir_x  = 2;
const int step_x = 3;

const int dir_y  = 4;
const int step_y = 5;

const int dir_z  = 6;
const int step_z = 7;

const int vacuum = 8;

//////////////////////////////////////////////////////////////
// POSICION ACTUAL CABEZAL
//////////////////////////////////////////////////////////////

long posActualX = 0;
long posActualY = 0;

//////////////////////////////////////////////////////////////
// PARAMETROS
//////////////////////////////////////////////////////////////

const int delayStep = 300;

const int pasosZ = 2000;

//////////////////////////////////////////////////////////////
// STEP MOTOR
//////////////////////////////////////////////////////////////

void stepMotor(int pinStep)
{
    digitalWrite(pinStep,HIGH);
    delayMicroseconds(delayStep);

    digitalWrite(pinStep,LOW);
    delayMicroseconds(delayStep);
}

//////////////////////////////////////////////////////////////
// MOTOR X
//////////////////////////////////////////////////////////////

void moverMotorX(long dx)  //Funcion que mueve en x un numero de pasos calculados en la funcion moverXY(....)
{
    if(dx == 0)
    {
        return;
    }

    if(dx > 0)
    {
        digitalWrite(dir_x,HIGH); //connfiguramos el motor x en avance
    }
    else
    {
        digitalWrite(dir_x,LOW); //configuramos el motor x en retroceso
        dx = -dx; //negamos los pasos recibidos para que siempre salgan positivos en el for
    }

    for(long i=0;i<dx;i++)
    {
        stepMotor(step_x);
    }
}

//////////////////////////////////////////////////////////////
// MOTOR Y
//////////////////////////////////////////////////////////////

void moverMotorY(long dy)
{
    if(dy == 0)
    {
        return;
    }

    if(dy > 0)
    {
        digitalWrite(dir_y,HIGH); //connfiguramos el motor y en avance
    }
    else
    {
        digitalWrite(dir_y,LOW); //connfiguramos el motor y en retroceso
        dy = -dy;
    }

    for(long i=0;i<dy;i++)
    {
        stepMotor(step_y);
    }
}

//////////////////////////////////////////////////////////////
// MOVER XY
//////////////////////////////////////////////////////////////

void moverXY(long xDestino,long yDestino) //xDestino e yDestino calculados en funcion coordenadaFisica (...);
{
    //////////////////////////////////////////////////////////
    // CALCULO DEL MOVIMIENTO
    //////////////////////////////////////////////////////////

    long dx = xDestino - posActualX; //Aqui se determina el sentido del movimiento a ejecutar y el numero de pasos
    long dy = yDestino - posActualY;

    //////////////////////////////////////////////////////////
    // MOVIMIENTO REAL
    //////////////////////////////////////////////////////////

    moverMotorX(dx); 
    moverMotorY(dy);

    //////////////////////////////////////////////////////////
    // ACTUALIZAR POSICION
    //////////////////////////////////////////////////////////

    posActualX = xDestino;
    posActualY = yDestino;
}

//////////////////////////////////////////////////////////////
// BAJAR Z
//////////////////////////////////////////////////////////////

void bajarZ()
{
    digitalWrite(dir_z,LOW);

    for(int i=0;i<pasosZ;i++)
    {
        stepMotor(step_z);
    }
}

//////////////////////////////////////////////////////////////
// SUBIR Z
//////////////////////////////////////////////////////////////

void subirZ()
{
    digitalWrite(dir_z,HIGH);

    for(int i=0;i<pasosZ;i++)
    {
        stepMotor(step_z);
    }
}

//////////////////////////////////////////////////////////////
// VACIO
//////////////////////////////////////////////////////////////

void vacuumON()
{
    digitalWrite(vacuum,HIGH);
}

void vacuumOFF()
{
    digitalWrite(vacuum,LOW);
}

//////////////////////////////////////////////////////////////
// COGER CHIP
//////////////////////////////////////////////////////////////

void cogerChip()
{
    bajarZ();

    vacuumON();

    delay(100);

    subirZ();
}

//////////////////////////////////////////////////////////////
// DEJAR CHIP
//////////////////////////////////////////////////////////////

void dejarChip()
{
    bajarZ();

    vacuumOFF();

    delay(100);

    subirZ();
}

//////////////////////////////////////////////////////////////
// FILA/COLUMNA -> XY
//////////////////////////////////////////////////////////////

void coordenadaFisica(//Asocia una bandeja(origen o destino) a una celda actualizada de esa bandeja a la que nos vamos a mover. Recibe puntero (a struct) a la bandeja en particular
    Bandeja *b,       //Recibe la celda actualizada de esa bandeja. Calcula el numero de pasos a esa coordenada teniendo en cuenta la posicion absoluta en pasos de la celda (0,0) x0 ,y0 de esa bandeja.
    Celda c,          //Recibe un puntero a las coordenadas que almacenarán el valor en pasos.
    long *x,
    long *y)
{
    *x = b->x0 + c.columna * b->pasoX; //*x es el valor calculado sacado de la coordenada (x,y) a la que nos queremos mover. (Usamos la expresion :b->x0 ó *(b).x0 para acceder al campo x0 de la variable donde apunta el puntero b.)
  

    *y = b->y0 + c.fila * b->pasoY;    //*x es el valor calculado sacado de la coordenada (x,y) a la que nos queremos mover
}

//////////////////////////////////////////////////////////////
// SIGUIENTE CELDA
//////////////////////////////////////////////////////////////

void siguienteCelda(Bandeja *b,Celda *c) //Calcula la siguiente celda de una bandeja en formato coordenadas (x,y),actualiza la variable Celda, tanto de la bandeja de origen como la de destino
                                         //Recibe puntero a una Bandeja (struct) para optimizar memoria y otro puntero a una celda para cambiar el valor de la variable Celda
{                                        //Ésta funcion se ejecuta cuando terminemos un traslado, para calcular tanto la coordenada de origen siguiente como la de destino.
    //////////////////////////////////////////////////////////
    // AQUI SE CALCULA LA SIGUIENTE COORDENADA
    //////////////////////////////////////////////////////////

    c->columna++;

    //////////////////////////////////////////////////////////
    // CAMBIO DE FILA
    //////////////////////////////////////////////////////////

    if(c->columna >= b->columnas)
    {
        c->columna = 0;

        c->fila++;
    }

    //////////////////////////////////////////////////////////
    // FIN BANDEJA
    //////////////////////////////////////////////////////////

    if(c->fila >= b->filas)
    {
        c->fila = 0;
    }
}

//////////////////////////////////////////////////////////////
// TRANSFERIR
//////////////////////////////////////////////////////////////

void transferir(
    Bandeja *origen,
    Bandeja *destino,

    Celda inicioOrigen,
    Celda inicioDestino,

    int cantidad)
{
    //////////////////////////////////////////////////////////
    // CELDAS ACTUALES
    //////////////////////////////////////////////////////////

    Celda celdaOrigen  = inicioOrigen; //Variable Celda de origen. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
    Celda celdaDestino = inicioDestino; //Variable Celda de destino.En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview.Despues se irá actualizando en el bucle

    //////////////////////////////////////////////////////////
    // BUCLE PRINCIPAL
    //////////////////////////////////////////////////////////

    for(int i=0;i<cantidad;i++)
    {
        //////////////////////////////////////////////////////
        // CALCULAR COORDENADAS ORIGEN
        //////////////////////////////////////////////////////

        long xo,yo; //COORDENADA ACTUAL EN PASOS DE LA BANDEJA ORIGEN.Creamos las variables para calcular la coordenada actual en pasos a la que nos vamos a mover.

        coordenadaFisica(
            origen,
            celdaOrigen,
            &xo,
            &yo
        );

        //////////////////////////////////////////////////////
        // IR A ORIGEN
        //////////////////////////////////////////////////////

        moverXY(xo,yo);

        //////////////////////////////////////////////////////
        // COGER CHIP
        //////////////////////////////////////////////////////

        cogerChip();

        //////////////////////////////////////////////////////
        // CALCULAR COORDENADAS DESTINO
        //////////////////////////////////////////////////////

        long xd,yd; //COORDENADA ACTUAL EN PASOS DE LA BANDEJA DESTINO.Creamos las variables para calcular la coordenada actual en pasos a la que nos vamos a mover.

        coordenadaFisica(
            destino,
            celdaDestino,
            &xd,
            &yd
        );

        //////////////////////////////////////////////////////
        // IR A DESTINO
        //////////////////////////////////////////////////////

        moverXY(xd,yd);

        //////////////////////////////////////////////////////
        // DEJAR CHIP
        //////////////////////////////////////////////////////

        dejarChip();

        //////////////////////////////////////////////////////
        // CALCULAR SIGUIENTE ORIGEN
        //////////////////////////////////////////////////////

        siguienteCelda(
            origen,
            &celdaOrigen
        );

        //////////////////////////////////////////////////////
        // CALCULAR SIGUIENTE DESTINO
        //////////////////////////////////////////////////////

        siguienteCelda(
            destino,
            &celdaDestino
        );
    }
}

void setup()
{
  //////////////////////////////////////////////////////////////
// SETUP
//////////////////////////////////////////////////////////////

  Serial.begin(9600);
  
  initServo();

  pinMode(sensor_x,INPUT);
  pinMode(sensor_y,INPUT);
  pinMode(sensor_z,INPUT);
  pinMode(dir_x,OUTPUT);
  pinMode(pul_x,OUTPUT);
  pinMode(dir_y,OUTPUT);
  pinMode(pul_y,OUTPUT);
  pinMode(dir_z,OUTPUT);
  pinMode(pul_z,OUTPUT);
  pinMode(ena_x,OUTPUT);
  pinMode(ena_y,OUTPUT);
  pinMode(ena_z,OUTPUT);
  pinMode(bomba,OUTPUT);
  
  enableMotores();
  Home();


    //////////////////////////////////////////////////////////
    // PINES
    //////////////////////////////////////////////////////////

    /*pinMode(dir_x,OUTPUT);
    pinMode(step_x,OUTPUT);

    pinMode(dir_y,OUTPUT);
    pinMode(step_y,OUTPUT);

    pinMode(dir_z,OUTPUT);
    pinMode(step_z,OUTPUT);

    pinMode(vacuum,OUTPUT);*/

    

}

void loop()
{
Home();

//////////////////////////////////////////////////////////
    // DEFINIR BANDEJAS
    //////////////////////////////////////////////////////////

    Bandeja origen =
    {
        32661,
        39199,

        1169,
        1078,

        15,
        10
    };

    Bandeja destino =
    {
        20227,
        39199,

        1169,
        1078,

        15,
        10
    };

    //////////////////////////////////////////////////////////
    // POSICIONES INICIALES
    //////////////////////////////////////////////////////////

    Celda inicioOrigen =
    {
        5,
        9
    };

    Celda inicioDestino =
    {
        2,
        8
    };

/*1.Calcular en pasos la coordenada origen  de la bandeja Origen 
  2.Moverse a esa coordenada 
  3.Coger chip
  4.Calcular en pasos la coordenada destino de la Bandeja Destino
  5.Moverse a esa coordenada
  6.Soltar chip
  7.Calcular la siguiente coordenada de origen en formato (x,y) actualizando la variable Celda de bandeja Origen
  8.Calcular la siguiente coordenada de destino en formato (x,y)actualizando la variable Celda de la bandeja destino
  */
      //////////////////////////////////////////////////////////
    // MOVER 3 CHIPS
    //////////////////////////////////////////////////////////

    transferir(
        &origen, 
        &destino,

        inicioOrigen,
        inicioDestino,

        3
    );

Home();
}

