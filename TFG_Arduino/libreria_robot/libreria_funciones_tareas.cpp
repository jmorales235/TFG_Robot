#include "libreria_robot.h"
#include <Arduino.h>
#include <config_pines_arduino.h>
#include "libreria_funciones_tareas.h"
#include <Servo.h>

// IMPORTANTE:
// En C++ no se pueden ejecutar instrucciones sueltas en el ámbito global del .cpp.
// Solo se permiten declaraciones/definiciones globales.
// Llamadas a métodos como servo.attach(), digitalWrite(), etc.
// deben ejecutarse dentro de funciones, métodos o constructores.
//
// Correcto:
//   Servo servoSocket;   // declaración global
//
// Incorrecto:
//   servoSocket.attach(pin_servo); // llamada ejecutable fuera de función , debe meterse dentro de una función

Posicion posActual;

//////////////////////////////////////////////////////////////
// FILA/COLUMNA -> XY
//////////////////////////////////////////////////////////////

Posicion coordenadaFisica(Bandeja *b, Celda c) //CALCULA POSICION EN PASOS DE UNA COORDENADA DE BANDEJA A LA QUE SE MOVERÁ EL CABEZAL EN FUNCION DEL VALOR CELDA .SÓLO CALCULA, NO MUEVE NADA.
{
    Posicion p;

    p.x = b->origen.x + (long)(c.columna * b->pasoX);

    p.y = b->origen.y - (long)(c.fila * b->pasoY);

    return p;
}



//////////////////////////////////////////////////////////////
// SIGUIENTE CELDA
//////////////////////////////////////////////////////////////

/*Calcula la siguiente celda de una bandeja en formato coordenadas (x,y),actualiza la variable Celda, tanto de la bandeja de origen como la de desti
Recibe puntero a una Bandeja (struct) para optimizar memoria y otro puntero a una celda para cambiar el valor de la variable Celda
Ésta funcion se ejecuta cuando terminamos un movimiento, para calcular tanto la coordenada de origen siguiente como la de destino
Al principio de la ejecución valdrá la coordenada de comienzo que le enviamos desde labview, después la función la va incrementando.
Además calcula si se ha llegado al final de la fila y/o columna de la bandeja.*/

void siguienteCelda(Bandeja *b,Celda *c) {
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
// MOVER XY
//CALCULO DEL NUMERO DE PASOS ENTRE 2 POSICIONES (ABSOLUTAS) ORIGEN Y DESTINO y ACTUALIZA LA POSICION DEL CABEZAL
//TAMBIÉN SE DETERMINA EL SENTIDO DEL MOVIMIENTO QUE SERÁ EL SIGNO DE LA OPERACIÓN "dx" y "dy"
//////////////////////////////////////////////////////////////

void moverXY(Posicion destino) //xDestino e yDestino calculados en funcion coordenadaFisica (...);
{
    //////////////////////////////////////////////////////////
    // CALCULO DEL MOVIMIENTO
    //////////////////////////////////////////////////////////

    long dx = destino.x - posActual.x;

    long dy = destino.y - posActual.y;
    //Aqui se determina el sentido(signo) del movimiento a ejecutar y el numero de pasos. Positivo (a derechas) si posicion destino > posicion origen y viceversa.


    //////////////////////////////////////////////////////////
    // MOVIMIENTO REAL DE MOTORES
    //////////////////////////////////////////////////////////

    
    
	moverMotorX(dx);// el argumento podrá ser positivo o negativo. 
    moverMotorY(dy);
    //////////////////////////////////////////////////////////
    // ACTUALIZAR POSICION
    //////////////////////////////////////////////////////////

    posActual.x = destino.x;
    posActual.y = destino.y;
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

    if(dx>5000) 
    {   
       movimiento(pul_x,dx,100);
    }
    else 
    {   
       movimientoCorto(pul_x,dx);
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
        dy = -dy;//negamos los pasos recibidos para que siempre salgan positivos en el for
    }

    if(dy>5000) 
    {   
       movimiento(pul_y,dy,100);
    }
    else 
    {   
       movimientoCorto(pul_y,dy);
    }    
}

void moverMotorZ(long dz)
{
    if(dz == 0)
    {
        return;
    }

    if(dz > 0)
    {
        digitalWrite(dir_z,LOW); //connfiguramos el motor z en avance (bajada)
    }
    else
    {
        digitalWrite(dir_z,HIGH); //connfiguramos el motor z en retroceso (subida)
        dz = -dz;//negamos los pasos recibidos para que siempre salgan positivos en el for
    }

    movimiento(pul_z,dz,30);
}

void moverZ(long zDestino) //MUEVE LA ALTURA DEL CABEZAL HACIA ARRIBA O ABAJO EN FUNCION DEL SIGNO DE dz. Evitamos así tener una funcion para bajary otra para subir
{
    long dz = zDestino - posActual.z; //posicion actual.z siempre será ó 0 (cuando se posicione arriba) ó zDestino cuando se encuentre abajo.

    moverMotorZ(dz);

    posActual.z = zDestino;//muy importante durante el programa actualizar de manera correcta la posActual.z
}

void cogerDeBandeja(Bandeja *b,Celda c) //RECIBE PUNTERO A UNA BANDEJA PARA ACCEDER A SUS ATRIBUTOS DIRECTAMENTE SIN TENER QUE CREAR UNA COPIA EN MEMORIA
                                        //CALCULA UNA POSICION DE BANDEJA DONDE IR,SE MUEVE A ESA POSICION,ACTIVA VACÍO Y COGE EL CHIP
{
    Posicion p = coordenadaFisica(b,c); //UTILIZA LOS ARGUMENTOS BANDEJA Y CELDA PARA CALCULAR LA POSICION A LA QUE MOVERSE

    moverXY(p); //SE MUEVE A LA BANDEJA DONDE COGERÁ CHIP Y ACTUALIZA POSICION ACTUAL
    
    
    moverZ(b->origen.z); //BAJA Z

    activarBomba(); //ACTIVA BOMBA,COGE CHIP

    delay(100);

    moverZ(0);  //SUBE Z
}

void dejarEnBandeja(Bandeja *b,Celda c) //MISMA SECUENCIA EN Z QUE COGER DE BANDEJA, PERO SOLTANDO EL CHIP QUE LLEVE EN OTRA BANDEJA
{
    Posicion p = coordenadaFisica(b,c); //UTILIZA LOS ARGUMENTOS BANDEJA Y CELDA PARA CALCULAR LA POSICION A LA QUE MOVERSE

    moverXY(p); //SE MUEVE A LA BANDEJA DONDE DEJARÁ CHIP

    moverZ(b->origen.z);

    desactivarBomba();

    delay(100);

    moverZ(0);
}

void cogerDelSocket(Posicion socket) //SECUENCIA PARA COGER UN CHIP DEL SOCKET, RECIBE LA POSICION DEL SOCKET (X,Y,Z)
{
    
    moverXY(socket); //aqui el desplazamiento daria cero y no se mueve

    accionamientoSocket();

    moverZ(socket.z);

    activarBomba();

    delay(100);

    moverZ(0);
	
	relajacionSocket();
	
	
}

void dejarEnSocket(Posicion socket)
{
    moverXY(socket);

    accionamientoSocket();
    
	moverZ(socket.z);

    desactivarBomba();

    delay(100);

    moverZ(0);
	
	relajacionSocket();
}

//////////////////////////////////////////////////////////////////////////////FUNCIONES TEST ASICS///////////////////////////

void recibirDatosEstacion(Bandeja *b1 , Bandeja *b2 , Bandeja *b3 , Posicion *socket ){ //recibo punteros para cambiar el valor de la variable real

    const byte NUM_DATOS = 24;
    long datos[NUM_DATOS];
    
    for (byte i = 0; i < NUM_DATOS; i++)
    {
        String dato = Serial.readStringUntil('\n');

        datos[i] = dato.toInt();

    }
    b1->origen.x = datos[0];
    b1->origen.y = datos[1];
    b1->origen.z = datos[2];
	b1->pasoX = datos[3];
	b1->pasoY = datos[4];
	b1->filas = datos[5];
	b1->columnas = datos[6];

    b2->origen.x = datos[7];
    b2->origen.y =datos[8];
    b2->origen.z =datos[9];
	b2->pasoX = datos[10];
	b2->pasoY = datos[11];
	b2->filas = datos[12];
	b2->columnas = datos[13];

    b3->origen.x = datos[14];
    b3->origen.y = datos[15];
    b3->origen.z =datos[16];
	b3->pasoX = datos[17];
	b3->pasoY = datos[18];
	b3->filas = datos[19];
	b3->columnas = datos[20];

    socket->x = datos[21];
    socket->y = datos[22];
    socket->z = datos[23];
    
    // Echo exactamente igual que se recibió
    Serial.print(b1->origen.x);
    Serial.print('\n');        
    Serial.print(b1->origen.y);
    Serial.print('\n');        
    Serial.print(b1->origen.z);
    Serial.print('\n'); 
    Serial.print(b1->pasoX);
    Serial.print('\n');  
    Serial.print(b1->pasoY);
    Serial.print('\n');	
	Serial.print(b1->filas);
	Serial.print('\n');
	Serial.print(b1->columnas);
    Serial.print('\n');
	
    Serial.print(b2->origen.x);
    Serial.print('\n');          
    Serial.print(b2->origen.y);
    Serial.print('\n');          
    Serial.print(b2->origen.z);
    Serial.print('\n'); 
    Serial.print(b2->pasoX);
    Serial.print('\n');  
    Serial.print(b2->pasoY);
    Serial.print('\n');	
	Serial.print(b2->filas);
	Serial.print('\n');
	Serial.print(b2->columnas);
	Serial.print('\n');
	
    Serial.print(b3->origen.x);
    Serial.print('\n');          
    Serial.print(b3->origen.y);
    Serial.print('\n');          
    Serial.print(b3->origen.z);
    Serial.print('\n');
    Serial.print(b3->pasoX);
    Serial.print('\n');  
    Serial.print(b3->pasoY);
    Serial.print('\n');	
	Serial.print(b3->filas);
	Serial.print('\n');
	Serial.print(b3->columnas);	
	Serial.print('\n');
    Serial.print(socket->x);
    Serial.print('\n');            
    Serial.print(socket->y);
    Serial.print('\n');             
    Serial.print(socket->z);
     
}

void recibirDatosTest(Celda *c1 , Celda *c2 , Celda *c3){ //recibo punteros para cambiar el valor de la variable real

    const byte NUM_DATOS = 6;
    long datos[NUM_DATOS];
    

    for (byte i = 0; i < NUM_DATOS; i++)
    {
        String dato = Serial.readStringUntil('\n');
        datos[i] = dato.toInt(); //en arduino mega toInt() devuelve un long , que en mega son 32 bits.
    }
    c1->columna = datos[0];
    c1->fila = datos[1];
    
    c2->columna = datos[2];
    c2->fila = datos[3];
    
    c3->columna = datos[4];
    c3->fila = datos[5];
    // Echo exactamente igual que se recibió
    Serial.print(c1->columna);           Serial.print('\n');
    Serial.print(c1->fila);              Serial.print('\n');
    Serial.print(c2->columna);           Serial.print('\n');
    Serial.print(c2->fila);              Serial.print('\n');
    Serial.print(c3->columna);           Serial.print('\n');
    Serial.print(c3->fila);              
    }

void esperarResultado (String *resultado ){
     while (!Serial.available()){};
     *resultado = Serial.readString();
     
}

/////////////////////////////////////////////////////////////////////////FUNCIONES LEER QR/////////////////////////////////////////

void recibirDatosEstacion_QR(Bandeja *b1 , Posicion *socket ){ //recibo punteros para cambiar el valor de la variable real

    const byte NUM_DATOS = 10;
    long datos[NUM_DATOS];
    
    for (byte i = 0; i < NUM_DATOS; i++)
    {
        String dato = Serial.readStringUntil('\n');

        datos[i] = dato.toInt();

    }
    b1->origen.x = datos[0];
    b1->origen.y = datos[1];
    b1->origen.z =datos[2];
	b1->pasoX = datos[3];
	b1->pasoY = datos[4];
	b1->filas = datos[5];
	b1->columnas = datos[6];



    socket->x = datos[7];
    socket->y = datos[8];
    socket->z =datos[9];
    
    // Echo exactamente igual que se recibió
    Serial.print(b1->origen.x);        Serial.print('\n');
    Serial.print(b1->origen.y);        Serial.print('\n');
    Serial.print(b1->origen.z);        Serial.print('\n');
	Serial.print(b1->pasoX);           Serial.print('\n');
	Serial.print(b1->pasoY);           Serial.print('\n');
	Serial.print(b1->filas);           Serial.print('\n');
	Serial.print(b1->columnas);        Serial.print('\n');
    
    Serial.print(socket->x);           Serial.print('\n');
    Serial.print(socket->y);           Serial.print('\n');
    Serial.print(socket->z);    
}

void recibirDatos_LecturaQR(Celda *c1){ //recibo punteros para cambiar el valor de la variable real

    const byte NUM_DATOS = 2;
    long datos[NUM_DATOS];
    

    for (byte i = 0; i < NUM_DATOS; i++)
    {
        String dato = Serial.readStringUntil('\n');
        datos[i] = dato.toInt();
    }
    c1->columna = datos[0];
    c1->fila = datos[1];
    
    // Echo exactamente igual que se recibió
    Serial.print(c1->columna);           Serial.print('\n');
    Serial.print(c1->fila);              
    
    }

void esperar_LecturaQR (String *resultado ){
     while (!Serial.available()){};
     *resultado = Serial.readString();
     
}
////////////////////////////////////////////////////////////////////FUNCIONES TRASPASO ASICS////////////////////////////////////////////////////////

void recibirDatosEstacion_TRASPASO(Bandeja *b1 , Bandeja *b2){ //recibo punteros para cambiar el valor de la variable real

    const byte NUM_DATOS = 14;
    long datos[NUM_DATOS];
    
    for (byte i = 0; i < NUM_DATOS; i++)
    {
        String dato = Serial.readStringUntil('\n');

        datos[i] = dato.toInt();

    }
    b1->origen.x = datos[0];
    b1->origen.y = datos[1];
    b1->origen.z = datos[2];
	b1->pasoX = datos[3];
	b1->pasoY = datos[4];
	b1->filas = datos[5];
	b1->columnas = datos[6];

    b2->origen.x = datos[7];
    b2->origen.y =datos[8];
    b2->origen.z =datos[9];
	b2->pasoX = datos[10];
	b2->pasoY = datos[11];
	b2->filas = datos[12];
	b2->columnas = datos[13];

    
    // Echo exactamente igual que se recibió
    Serial.print(b1->origen.x);        Serial.print('\n');
    Serial.print(b1->origen.y);        Serial.print('\n');
    Serial.print(b1->origen.z);        Serial.print('\n');
	Serial.print(b1->pasoX);            Serial.print('\n');
	Serial.print(b1->pasoY);            Serial.print('\n');
	Serial.print(b1->filas);            Serial.print('\n');
	Serial.print(b1->columnas);         Serial.print('\n');
	
    Serial.print(b2->origen.x);        Serial.print('\n');
    Serial.print(b2->origen.y);        Serial.print('\n');
    Serial.print(b2->origen.z);        Serial.print('\n');
	Serial.print(b2->pasoX);            Serial.print('\n');
	Serial.print(b2->pasoY);            Serial.print('\n');
	Serial.print(b2->filas);            Serial.print('\n');
	Serial.print(b2->columnas);         
	
    
}

void recibirDatosTest_TRASPASO(Celda *c1 , Celda *c2){ //recibo punteros para cambiar el valor de la variable real

    const byte NUM_DATOS = 4;
    long datos[NUM_DATOS];
    

    for (byte i = 0; i < NUM_DATOS; i++)
    {
        String dato = Serial.readStringUntil('\n');
        datos[i] = dato.toInt();
    }
    c1->columna = datos[0];
    c1->fila = datos[1];
    
    c2->columna = datos[2];
    c2->fila = datos[3];
    
   
    // Echo exactamente igual que se recibió
    Serial.print(c1->columna);           Serial.print('\n');
    Serial.print(c1->fila);              Serial.print('\n');
    Serial.print(c2->columna);           Serial.print('\n');
    Serial.print(c2->fila);              
    
    }