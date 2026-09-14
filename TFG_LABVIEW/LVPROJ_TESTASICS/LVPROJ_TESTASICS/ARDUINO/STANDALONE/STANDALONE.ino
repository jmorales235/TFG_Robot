/* Teoricamente:
1mm= 91 pasos
1cm = 910 pasos
10 cm = 9100 pasos
0.1 mm = 9 pasos aprox
*/

#include <libreria_robot.h> 
/*los ficheros .h y.cpp que nos creamos como usuario deben estar en una carpeta llamada "libraries" situada en el "sketchbook location" definido en "Preferences", para que el compilador las vea.
asegurarse de que la extension real de los ficheros sean .h y .cpp y NO sea .txt,para ello habilitar la opcion visualizar extension de fichero en windows.
dentro de libraries ya hacemos una carpeta que se llame como el fichero .h y .cpp que deben estar dentro.*/

#include <config_pines_arduino.h> //en este fichero mapeamos las variables de pin a los pines fisicos de arduino con directivas #define
/*config_pines define las señales: dir_y, pul_y, ena_y, dir_x ,dir_x ,pul_x ,ena_x, dir_z, pul_z ,ena_z ,bomba ,pin_servo ,sensor_x ,sensor_y ,sensor_z
*/

/*
VARIABLES: STRUCT BANDEJA ENTRADA , STRUCT BANDEJA OK , STRUCT BANDEJA NOK ,struct socket
           COORDENADA SIGUIENTE BANDEJA ENTRADA (X,Y), COORDENADA ACTUAL BANDEJA ENTRADA (X,Y)
           COORDENADA SIGUIENTE BANDEJA OK (X,Y), COORDENADA ACTUAL OK (X,Y)
           COORDENADA SIGUIENTE BANDEJA NOK (X,Y), COORDENADA ACTUAL NOK (X,Y)
           NUMERO DE ASICS PROBADOS
           NUMERO DE FAILS
           NUMERO  DE OK'S

FUNCIONES: CALCULO DE SIGUIENTE COORDENADA EN BANDEJAS ENTRADA , OK Y NOK EN FORMATO (X,Y)
           PASAR DE FORMATO (X,Y) A PASOS DE MOTOR EN COORDENADAS BANDEJAS
0- PING
1- RECIBIR DATOS : DATOS DE BANDEJA , COORDENADAS DE PRIMERA CELDA DE LAS TRES BANDEJAS, COORDENADAS DEL SOCKET, NUMERO DE ASICS A TESTEAR
2- GUARDAR DATOS EN VARIABLES
3- ESPERAR SEÑAL COMIENZO---------------POLLING-----------------------

////FUNCION TEST////////////////////////////////////////////
3- IR A POSICION SOCKET--PUEDE ESTAR EN HOME O NO
3- CALCULAR TRAYECTO IDA
4-IR A CELDA ASIC
5-ACTIVAR BOMBA
6-BAJAR Z CELDA
7-SUBIR Z
7-CALCULAR TRAYECTO VUELTA
8-IR A SOCKET
8-ABRIR SERVO SOCKET
9-BAJAR Z SOCKET
9-DESACTIVAR BOMBA
10-SUBIR Z SOCKET
10-CERRAR SERVO SOCKET
11-ENVIAR A LABVIEW FLAG PARA QUE LLAME A LEER QR
10- ESPERAR A TEST--------------------POLLING-------------------------------------
11-RECIBIR RESULTADO TEST
13-DECIDIR BANDEJA DE RESULTADO-----IF....
13-CALCULAR TRAYECTORIA BANDEJA RESULTADO
13-ABRIR SERVO SOCKET
14-BAJAR Z SOCKET
15-ACTIVAR BOMBA
16-SUBIR Z SOCKET
16-CERRAR SERVO SOCKET
17-IR A BANDEJA RESULTADO
17-BAJAR Z BANDEJA RESULTADO
17-DESACTIVAR BOMBA
18-SUBIR Z BANDEJA RESULTADO
18- CALCULAR TRAYECTORIA VUELTA
18-IR A SOCKET
18-INCREMENTO ASICS PROBADOS
19-COMPRUEBA SI HA TERMINADO DE TESTEAR
20-VUELVE A EMPEZAR DESDE 3



CONSIDERACIONES IMPORTANTE: 1-CUANDO EMPIEZA CADA TEST TANTO LA PRIMERA VEZ COMO LAS SIGUIENTES, EL CABEZAL DEBE ESTAR EN POSICION DE HOME Y NO EN LA DE SOCKET
                          2-CUANDO ACABA UN TEST COMPLETO DE UN NUMERO DE ASICS DETERMINADO DEBE IRSE A HOME (Y NO QUEDARSE EN EL SOCKET)PARA EMPEZAR DESDE AHI EL SIGUIENTE TEST
                          3-SI CANCELAMOS UN TEST EN MITAD DE UNA SECUENCIA DE MOVIMIENTO, SÓLO VOLVEREMOS A HOME CUANDO DENTRO DE ESA SECUENCIA EL CABEZAL ESTÉ PARADO (EVITAR FRENAZOS)
                          4-SI NOS SALIMOS DEL VI DE TESTasICS (BOTON EXIT EN LABVIEW), ANTES HAREMOS UN HOME 
VARIABLES QUE NECESITAN SER RESETEADAS ANTES DE COMENZAR UN NUEVO TEST:

posActual


*/




//const long pulsos_rev = 6400; //Numero de pulsos por revolucion del motor

struct Posicion //POSICION ABSOLUTA CUALQUIERA EN PASOS DENTRO DEL TABLERO
{
    long x; //PASOS
    long y;
    long altura_z;
    
};

struct Bandeja   //Variable tipo estructura. Representa los datos característicos de una bandeja tipo JEDEC
{
    Posicion origen;      // Coordenadas absolutas de la celda (0,0)
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
// POSICION ACTUAL CABEZAL
//////////////////////////////////////////////////////////////
Posicion posActual; //VARIABLE GLOBAL QUE GUARDA LA POSICION ABSOLUTA DEL CABEZAL CADA VEZ QUE SE REALIZA UN MOVIMIENTO

//////////////////////////////////////////////////////////////
// POSICION SOCKET
//////////////////////////////////////////////////////////////
Posicion socket;

//////////////////////////////////////////////////////////////
// BANDEJAS Y CELDAS DE TEST
//////////////////////////////////////////////////////////////

Bandeja bandeja_IN;
Bandeja bandeja_OK;
Bandeja bandeja_NOK;

Celda celda_IN_INICIO;
Celda celda_OK_INICIO;
Celda celda_NOK_INICIO;

Celda celdaEntrada; //Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
Celda celdaOK; //Variable Celda de .En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview.Despues se irá actualizando en el bucle
Celda celdaNOK;

String resultadoTest;

enum state {START,ESPERA_HOME,HACER_HOME,RECIBIR_DATOS_ESTACION,RECIBIR_DATOS_TEST, ESPERAR_COMIENZO,IR_ENTRADA, DEJAR_SOCKET ,ESPERAR_TEST,COGER_SOCKET,DEJAR_OK_NOK,SIGUIENTE_CHIP,TERMINAR} mystate=START;








//////////////////////////////////////////////////////////////
// FILA/COLUMNA -> XY
//////////////////////////////////////////////////////////////

Posicion coordenadaFisica(Bandeja *b, Celda c) //CALCULA POSICION ABSOLUTA EN PASOS DE UNA COORDENADA DE BANDEJA A LA QUE SE MOVERÁ EL CABEZAL EN FUNCION DEL VALOR CELDA .SÓLO CALCULA, NO MUEVE NADA.
{
    Posicion p;

    p.x = b->origen.x + c.columna * b->pasoX; //POSICION ABSOLUTA EN PASOS DE LA CELDA RESPECTO DEL ZERO DEL ROBOT 

    p.y = b->origen.y + c.fila * b->pasoY;

    return p;
}
/*void test(
    Bandeja *bandejaIN, //recibe un puntero a tipo Bandeja que se llamará bandejaIN. Luego en la llamada los argumentos que se pasen llevarán "&"
    Bandeja *bandejaOK, //recibe un puntero que se llamará bandejaOK.
    Bandeja *bandejaNOK,//recibe un puntero que se llamará bandejaNOK.

    Celda inicioIN, //recibe una copia de un tipo Celda
    Celda inicioOK,//DATOS 
    Celda inicioNOK,

   

    int cantidad)
{
    //////////////////////////////////////////////////////////
    // CELDAS ACTUALES
    //////////////////////////////////////////////////////////

    Celda celdaEntrada  = inicioIN; //Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
    Celda celdaOK = inicioOK; //Variable Celda de .En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview.Despues se irá actualizando en el bucle
    Celda celdaNOK = inicioNOK; 

    





    //////////////////////////////////////////////////////////
    // BUCLE PRINCIPAL
    //////////////////////////////////////////////////////////

    for(int i=0;i<cantidad;i++)
    {
        //////////////////////////////////////////////////////
        // CALCULAR COORDENADAS BANDEJA DE ENTRADA
        //////////////////////////////////////////////////////

        cogerDeBandeja(&bandeja_IN, celdaEntrada);

        dejarEnSocket(socket);
        esperarResultado();

        cogerDelSocket(socket);

        if(resultadoTest == OK)
          {
             dejarEnBandeja(&bandeja_OK, celdaOK);

             siguienteCelda(&bandeja_OK, celdaOK);
           }
        else
        {
            dejarEnBandeja(&bandeja_NOK, celdaNOK);

            siguienteCelda(&bandeja_NOK, celdaNOK);
         }

        siguienteCelda(&bandeja_IN, &celdaEntrada);
        }
}*/


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
    // AQUI SE CALCULA LA SIGUIENTE COORDENADA EN FORMATO (X,Y)
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
    moverMotorY(dy);
    moverMotorX(dx);// el argumento podrá ser positivo o negativo. 
    

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
       movimiento(pul_x,dx,150);
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
       movimiento(pul_y,dy,150);
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
        digitalWrite(dir_z,HIGH); //connfiguramos el motor y en avance
    }
    else
    {
        digitalWrite(dir_z,LOW); //connfiguramos el motor y en retroceso
        dz = -dz;//negamos los pasos recibidos para que siempre salgan positivos en el for
    }

    movimiento(pul_z,dz,50);
}

void moverZ(long zDestino) //MUEVE LA ALTURA DEL CABEZAL HACIA ARRIBA O ABAJO EN FUNCION DEL SIGNO DE dz. Evitamos así tener una funcion para bajary otra para subir
{
    long dz = zDestino - posActual.altura_z; //posicion actual.z siempre será ó 0 (cuando se posicione arriba) ó zDestino cuando se encuentre abajo.

    moverMotorZ(dz);

    posActual.altura_z = zDestino;//muy importante durante el programa actualizar de manera correcta la posActual.altura_z
}

void cogerDeBandeja(Bandeja *b,Celda c) //RECIBE PUNTERO A UNA BANDEJA PARA ACCEDER A SUS ATRIBUTOS DIRECTAMENTE SIN TENER QUE CREAR UNA COPIA EN MEMORIA
                                        //CALCULA UNA POSICION DE BANDEJA DONDE IR,SE MUEVE A ESA POSICION,ACTIVA VACÍO Y COGE EL CHIP
{
    Posicion p = coordenadaFisica(b,c); //UTILIZA LOS ARGUMENTOS BANDEJA Y CELDA PARA CALCULAR LA POSICION A LA QUE MOVERSE

    moverXY(p); //SE MUEVE A LA BANDEJA DONDE COGERÁ CHIP
    
    
    moverZ(p.altura_z); //BAJA Z

    activarBomba(); //ACTIVA BOMBA,COGE CHIP

    delay(100);

    moverZ(0); //SUBE Z
}

void dejarEnBandeja(Bandeja *b,Celda c) //MISMA SECUENCIA EN Z QUE COGER DE BANDEJA, PERO SOLTANDO EL CHIP QUE LLEVE EN OTRA BANDEJA
{
    Posicion p = coordenadaFisica(b,c); //UTILIZA LOS ARGUMENTOS BANDEJA Y CELDA PARA CALCULAR LA POSICION A LA QUE MOVERSE

    moverXY(p); //SE MUEVE A LA BANDEJA DONDE DEJARÁ CHIP

    moverZ(p.altura_z);

    desactivarBomba();

    delay(100);

    moverZ(0);
}

void cogerDelSocket(Posicion socket) //SECUENCIA PARA COGER UN CHIP DEL SOCKET, RECIBE LA POSICION DEL SOCKET (X,Y,Z)
{
    
    moverXY(socket);

    accionamientoSocket();

    moverZ(socket.altura_z);

    activarBomba();

    delay(100);

    moverZ(0);
}

void dejarEnSocket(Posicion socket)
{
    moverXY(socket);

    relajacionSocket();

    moverZ(socket.altura_z);

    desactivarBomba();

    delay(100);

    moverZ(0);
}


void recibirDatosEstacion(Bandeja *b1 , Bandeja *b2 , Bandeja *b3 , Posicion *socket ){ //recibo punteros para cambiar el valor de la variable real

    const byte NUM_DATOS = 12;
    long datos[NUM_DATOS];
    
    for (byte i = 0; i < NUM_DATOS; i++)
    {
        String dato = Serial.readStringUntil('\n');

        datos[i] = dato.toInt();

    }
    b1->origen.x = datos[0];
    b1->origen.y = datos[1];
    b1->origen.altura_z =datos[2];

    b2->origen.x = datos[3];
    b2->origen.y =datos[4];
    b2->origen.altura_z =datos[5];

    b3->origen.x = datos[6];
    b3->origen.y = datos[7];
    b3->origen.altura_z =datos[8];

    socket->x = datos[9];
    socket->y = datos[10];
    socket->altura_z =datos[11];
    
    // Echo exactamente igual que se recibió
    Serial.print(b1->origen.x);
    Serial.print('\n');        
    Serial.print(b1->origen.y);
    Serial.print('\n');        
    Serial.print(b1->origen.altura_z);
    Serial.print('\n');   
    Serial.print(b2->origen.x);
    Serial.print('\n');          
    Serial.print(b2->origen.y);
    Serial.print('\n');          
    Serial.print(b2->origen.altura_z);
    Serial.print('\n');   
    Serial.print(b3->origen.x);
    Serial.print('\n');          
    Serial.print(b3->origen.y);
    Serial.print('\n');          
    Serial.print(b3->origen.altura_z);
    Serial.print('\n');   
    Serial.print(socket->x);
    Serial.print('\n');            
    Serial.print(socket->y);
    Serial.print('\n');             
    Serial.print(socket->altura_z);
     
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

/*struct tramaMovimiento{
      uint8_t sentido;
      long pasos;
      char eje;
};

tramaMovimiento trama;*/


//enum state { START, ESPERA_COMANDO_HOME ,HACER_HOME, ESPERA_POSICION_INICIO, MOVER_POSICION_INICIO, RECIBIR_DATOS_MOVIMIENTO, MOVER_X , MOVER_Y , MOVER_Z , TERMINAR_MOVIMIENTO } mystate=START;


void setup() {
 
  Serial.begin(9600); 
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
  
  Home();
  //Home();

  

}

void loop() {


  switch (mystate){
    
       case START:
       {
           while (!Serial.available()){}; //espero Ping desde labview: "Q?"  POLLING
           String comandoPing=Serial.readString(); //funcion para leer cadena de texto
  
           if (comandoPing.equals("Q?")) //SSi labview me hace ping contesto que estoy preparado para comenzar COM
                {
                Serial.print("R!");
                delay(100);
   //contesto ready
                mystate = ESPERA_HOME;
                } //contesto ready

           else {
                mystate = START;
                }
        }     
     
    
    break;

        case ESPERA_HOME:  //LISTEN TO LABVIEW : LEEMOS UN BYTE 'H' PARA HACER HOME   
        {
     //ENVÍO A LABVIEW FLAG DE ESTADO
              Serial.print("2");//LABVIEW DEBE LEER ESTADO 2
              char comandoHome=LeerComando_1byte();//polling
    
              if (comandoHome == 'H') {
              //Serial.print(comando);
               mystate = HACER_HOME;
              }
              else if (comandoHome!= 'H') {
              mystate = START;
              } 
        }
    

    break;
    
         case HACER_HOME: //codigo para hacer home

         {

              Serial.print("3"); //LABVIEW DEBE LEER ESTADO 3
              Home(); //AQUI MOVEMOS MOTORES , LABIVEW ESPERA
              Serial.print("FH");//ENVIO A LABVBIEW UN COMANDO DE FIN DEL MOVIMIENTO.
              delay(500);
      
              mystate = RECIBIR_DATOS_ESTACION ;
         }
    
    break;

    case  RECIBIR_DATOS_ESTACION: //LISTEN TO LABVIEW: RECIBE UNA TRAMA DE BYTES DE STRING CUANDO PRESIONAMOS UN BOTON BOOLEANO EN LABVIEW
                                    //TRAMA ENVIADA DESDE LABVIEW ---> DATOS BANDEJA DE ENTRADA + DATOS BANDEJA OK + DATOS BANDEJA NOK + DATOS SOCKET
          {                                
              Serial.print("4"); //LABVIEW DEBE LEER ESTADO 4 
    
              while(!Serial.available()){}; //POLLING//////////////////////////////////
              delay(50);
              recibirDatosEstacion(&bandeja_IN , &bandeja_OK , &bandeja_NOK , &socket );//leo datos estación y ademas hago ECHO a labview
              

              
              mystate = RECIBIR_DATOS_TEST;
      
          } 

          
                          
    break;


    case  RECIBIR_DATOS_TEST: //LISTEN TO LABVIEW: RECIBE UNA TRAMA DE BYTES DE STRING CUANDO PRESIONAMOS UN BOTON BOOLEANO EN LABVIEW
                                    //TRAMA ENVIADA DESDE LABVIEW ---> DATOS BANDEJA DE ENTRADA + DATOS BANDEJA OK + DATOS BANDEJA NOK + DATOS SOCKET
          {                                
              Serial.print("5"); //LABVIEW DEBE LEER ESTADO 5
    
              while(!Serial.available()){}; //POLLING//////////////////////////////////
              delay(50);
    
              recibirDatosTest(&celda_IN_INICIO, &celda_OK_INICIO, &celda_NOK_INICIO); //leo datos de test y ademas hago echo a labview
       
              mystate = ESPERAR_COMIENZO;
          } 

          
    break;

    case  ESPERAR_COMIENZO: //AQUI PUEDO RESETEAR TODAS LOS CALCULOS DEL ULTIMO TEST EJECUTADO QUE NECESITEN PARTIR DE CERO

     //Serial.print("7"); //ENVÍO A LABVIEW FLAG DE ESTADO
          {
            while(!Serial.available()){}; //POLLING//////////////////////////////////
            char flag =Serial.read(); //CARÁCTER ENVIADO POR LABVIEW COMO SEÑAL DE COMIENZO
            if (flag=='1'){
                  posActual.x=0;
                  posActual.y=0;
                  posActual.altura_z=0;
                  Celda celdaEntrada  = celda_IN_INICIO; //Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
                  Celda celdaOK = celda_OK_INICIO; //Variable Celda de .En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview.Despues se irá actualizando en el bucle
                  Celda celdaNOK = celda_NOK_INICIO;

                  mystate = IR_ENTRADA;}
            else {
                  mystate = START;
            }
            }

    break;

    case  IR_ENTRADA: //IR A LA BANDEJA DE ENTRADA A COGER CHIP

    //Serial.print("8"); //ENVÍO A LABVIEW FLAG DE ESTADO
        {
            cogerDeBandeja(&bandeja_IN, celdaEntrada); //RECIBE PUNTERO A UNA BANDEJA PARA ACCEDER A SUS ATRIBUTOS DIRECTAMENTE SIN TENER QUE CREAR UNA COPIA EN MEMORIA
                                                       //1.LLAMA A COORDENADA FISICA,DEVUELVE UNA POSICION EN PASOS, 2.LLAMA A MOVER_XY,MUEVE Y ACTUALIZA POSICION DE XY,3.LLAMA A MOVER Z Y BAJA Z.4 ACTUALIZA POSICION Z. 5.ACTIVA BOMBA 6.SUBE Z Y ACTUALIZA POSCION Z
                                                       //CALCULA UNA POSICION DE BANDEJA DONDE IR,SE MUEVE A ESA POSICION,ACTIVA VACÍO Y COGE EL CHIP
                                                       //ACTUALIZA LA POSICION ABSOLUTA DEL CABEZAL EN X,Y,Z--> posActual
            mystate = DEJAR_SOCKET;
        }
    break;

    case  DEJAR_SOCKET: //DEJA UN CHIP EN EL SOCKET

        {   dejarEnSocket(socket); 
            Serial.print("1");                         //CALCULA EL TRAYECTO PARA IR AL SOCKET DESDE LA POSICION QUE SE ENCUENTRE EL CABEZAL Y LA POSICION FIJA DEL SOCKET.
                                                       //EJECUTA EL MOVIMIENTO
                                                       //ACTUALIZA LA POSICION ABSOLUTA DEL CABEZAL EN X,Y,Z--> posActual
                                                       //ENVIA A LABVIEW UN CARACTER PARA INDICAR QUE HA COLOCADO EL CHIP EN EL SOCKET
            
            mystate = ESPERAR_TEST;

        }
    
    break;

    case  ESPERAR_TEST: //ESPERA AQUE SE EJECUTE EL TEST Y LABVIEW MANDE EL RESULTADO
        {   
            
            esperarResultado(&resultadoTest); //POLLING HASTA QUE SE LEA EL RESULTADO ENVIADO POR LABVIEW OK O NOK ESCRIBIENDO EN LA VARIABLE GLOBAL resultadoTest
            mystate = COGER_SOCKET;
        }   
    break;

    case COGER_SOCKET:
        {  
           cogerDelSocket(socket); //CALCULA EL TRAYECTO X,Y,Z PARA IR AL SOCKET , PERO COMO YA ESTÁ EN LA POSICION DE SOCKET (LA ULTIMA QUE GUARDÓ) EL CABEZAL NO SE MUEVE EN X,Y
           mystate = DEJAR_OK_NOK;
        }
    break;

    case DEJAR_OK_NOK:
    {      
        
        if(resultadoTest == "OK")
          {
             dejarEnBandeja(&bandeja_OK, celdaOK);  //calcula trayecto , ejecuta movimiento, suelta chip , y actualiza posicion cabezal

             siguienteCelda(&bandeja_OK, &celdaOK); //modifica la coordenada actual de la celda OK en formato (x,y) para el siguiente chip
             Serial.print("FM");
           }
        else if (resultadoTest == "NOK")
        {
             dejarEnBandeja(&bandeja_NOK, celdaNOK); //calcula trayecto , ejecuta movimiento, suelta chip , y actualiza posicion cabezal

             siguienteCelda(&bandeja_NOK, &celdaNOK);//modifica la coordenada actual de la celda nok para el siguiente chip
             Serial.print("FM");
         }

        siguienteCelda(&bandeja_IN, &celdaEntrada);//modifica la coordenada actual de la celda de entrada para el siguiente chip
        //Serial.print(); //enviamos a labview que ha terminado de depositar el chip
        mystate = SIGUIENTE_CHIP;
    }
    break;

    case SIGUIENTE_CHIP: //ESPERAMOS A QUE LABVIEW NOS DIGA SI SE HA TERMINADO LA TANDA DE CHIPS O SEGUIMOS CON EL SIGUIENTE
    {
    while(!Serial.available()){}; //POLLING//////////////////////////////////
    String finTest = Serial.readString();
    if (finTest=="SI") //si labview determina que ha terminado de testear todos los asics nos envía SI  
    {      Home(); 
           Serial.print("FH");
           mystate = RECIBIR_DATOS_ESTACION; 
    }
    else if(finTest =="NO"){ //SI NO HA TERMINADO VUELVO A COGER OTRO ASIC , MIENTRAS LABVIEW ESPERA 
    mystate = IR_ENTRADA;
    }
    else { mystate = START; }
    }
    break;


}
}
