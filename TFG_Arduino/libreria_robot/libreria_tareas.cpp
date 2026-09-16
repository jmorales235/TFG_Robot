#include "libreria_tareas.h"
#include "libreria_funciones_tareas.h"
#include "libreria_robot.h"
#include <Arduino.h>
#include <config_pines_arduino.h>

/////////////////////////////////////////////////////////////////////FUNCIONES DE ALTO NIVEL QUE EJECTUAN LAS TAREAS DEL ROBOT CON MAQUINAS DE ESTADO//////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////MOVER CABEZAL///////////////////////////////////////////////////////////////////
void moverCabezal(){

struct tramaMovimiento{
      uint8_t sentido;
      long pasos;
      char eje;
};

tramaMovimiento trama;


enum state { START, ESPERA_COMANDO_HOME ,HACER_HOME, ESPERA_POSICION_INICIO, RECIBIR_DATOS_MOVIMIENTO, MOVER_X , MOVER_Y , MOVER_Z , TERMINAR_MOVIMIENTO } mystate=START;

  while(true){
  switch (mystate){
    
       case START:
       {
           while (!Serial.available()){} //espero Ping desde labview: "Q?"  POLLING
           String comandoPing=Serial.readString(); //funcion para leer cadena de texto
  
           if (comandoPing.equals("Q?")) //SSi labview me hace ping contesto que estoy preparado para comenzar COM
                {
                Serial.print("R!");
                //delay(100);
				
                
                mystate = ESPERA_COMANDO_HOME;
                
                
                } 

           else {
                
                mystate = START;
                }
        }     
     
    
    break;

        case ESPERA_COMANDO_HOME:  //LISTEN TO LABVIEW : LEEMOS UN BYTE 'H' PARA HACER HOME   
        {
             
              Serial.print("2");
              
              
              while(!Serial.available()){}; //POLLING DE ESCUCHA DE DATOS DE MOVIMIENTO Ó COMANDO DE SALIR
             
              char charRecibido = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos
              if (charRecibido =='E'){ 
                                                //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    Serial.print(charRecibido);
                    Serial.read(); //limpiaMos el buffer RX el caracter E
                    mystate = START;
                    return;
                    }

              else if (charRecibido== 'H'){
                    Serial.read();
                    mystate=HACER_HOME;
                    
              }
        }
    

    break;
    
         case HACER_HOME: 

         {

              Serial.print("3"); //ENVÍO A LABVIEW FLAG DE ESTADO
              Home(); //AQUI MOVEMOS MOTORES A HOME POR SI EL CABEZAL POR ALGUNA SITUACION INESPERADA SE ENCUENTRA FUERA DE HOME ANTES DE COMENZAR LA TAREA.
              Serial.print("FH");//ENVIO A LABVBIEW UN COMANDO DE FIN DEL MOVIMIENTO.
              delay(100);
      
              mystate = RECIBIR_DATOS_MOVIMIENTO;
         }
    
    break;

    

    case  RECIBIR_DATOS_MOVIMIENTO: //LISTEN TO LABVIEW: RECIBE UNA TRAMA DE BYTES DE STRING CUANDO PRESIONAMOS UN BOTON BOOLEANO EN LABVIEW
                                    //TRAMA ENVIADA DESDE LABVIEW ---> 1 BYTE : SENTIDO [0,1] + \n + "n BYTES de PASOS" + \n + 1BYTE: eje [X ó Y]+\n 
                                    //, y puede irse a mover x , mover y , mover z ó a terminar movimiento
          {                                
              Serial.print("6"); //ENVÍO A LABVIEW FLAG DE ESTADO 
    
              while(!Serial.available()){}; //POLLING DE ESCUCHA DE DATOS DE MOVIMIENTO Ó COMANDO DE SALIR
              
              delay(10);
              char primerChar = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos

              if (primerChar=='E'){ 
                    Serial.print(primerChar);//ECHO
                    Serial.read();//limpio buffer de RX
                     //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    
                    mystate = START;
                    return;
              }

              else{
              
                    String dato; //LEEMOS LOS 3 DATOS DE MOVIMIENTO SENTIDO + PASOS + EJE
                    dato = Serial.readStringUntil('\n');
                    trama.sentido=dato.toInt();
                    dato = Serial.readStringUntil('\n');
                    trama.pasos=dato.toInt();
                    String ejeStr = Serial.readStringUntil('\n');
                    trama.eje = ejeStr.charAt(0); //eje está declarado como char y el dato del puerto es un String, aunque sea solo 1 letra, hay que hacer conversion de tipo

              }
       
              // y ahora decido qué hacer en funcion de esos valores
              if (trama.eje== 'Y'){
                      mystate = MOVER_Y;
              }
              else if (trama.eje== 'X'){
                      mystate = MOVER_X;
              }

              else if (trama.eje== 'Z'){
                      mystate = MOVER_Z;
              }

              else if (trama.eje== '0'){ //SI HABIENDO EMPEZADO A MOVER EL CABEZAL YA POR EL TABLERO DECIDIMOS TERMINAR Y MOVER A HOME ENVIAMOS DESDE LABVIEW EJE=0
                      mystate = TERMINAR_MOVIMIENTO;
              }
              else {
              mystate = RECIBIR_DATOS_MOVIMIENTO;
              }
          } 
                          
    break;

    case  MOVER_X: // codigo para mover motores cierto numero de pasos 

     //Serial.print("7"); //ENVÍO A LABVIEW FLAG DE ESTADO
          {
                if(trama.sentido==0){
                      derecha_X();
                      if(trama.pasos>5000) {movimiento(pul_x,trama.pasos,150);}
                      else {movimientoCorto(pul_x,trama.pasos);}
                
                

                } 
                else if (trama.sentido==1){
                      izquierda_X();
                      if(trama.pasos>5000) {movimiento(pul_x,trama.pasos,150);}
                      else {movimientoCorto(pul_x,trama.pasos);}
                 }


                Serial.print("FX"); //ENVIO A LAVBIEW UN COMANDO DE FIN DEL MOVIMIENTO.
                delay(500);

          }

    
      mystate = RECIBIR_DATOS_MOVIMIENTO;
    
    break;

    case  MOVER_Y: // codigo para mover motores cierto numero de pasos

    //Serial.print("8"); //ENVÍO A LABVIEW FLAG DE ESTADO
          {
                if(trama.sentido==0){
                     avance_Y();
                     if(trama.pasos>5000) {movimiento(pul_y,trama.pasos,150);}
                     else {movimientoCorto(pul_y,trama.pasos);}    
                 
                 } //avanza
                 else if (trama.sentido==1){
                     retroceso_Y();
                     if(trama.pasos>5000) {movimiento(pul_y,trama.pasos,150);}
                     else {movimientoCorto(pul_y,trama.pasos);}
            }

            Serial.print("FY"); //ENVIO A LAVBIEW UN COMANDO DE FIN DEL MOVIMIENTO.
            delay(500);

            mystate = RECIBIR_DATOS_MOVIMIENTO;
        }
    break;

    case  MOVER_Z: // codigo para mover motores cierto numero de pasos

    {  //Serial.print("9"); //ENVÍO A LABVIEW FLAG DE ESTADO
                if(trama.sentido==0){
                    bajar_Z();
                    movimiento(pul_z,trama.pasos,50);

                  } //avanza

                else if (trama.sentido==1){
                    subir_Z();
                    movimiento(pul_z,trama.pasos,50);
     }


      Serial.print("FZ"); //ENVIO A LAVBIEW UN COMANDO DE FIN DEL MOVIMIENTO.
      delay(500);

      mystate = RECIBIR_DATOS_MOVIMIENTO;

      }
    
    break;

    case  TERMINAR_MOVIMIENTO: //codigo que vuelve a start y hacer home
{
      
    mystate = ESPERA_COMANDO_HOME ;
}   
    break;

}

}
}

/////////////////////////////////////////////////////////////////////////////////TEST ASICS/////////////////////////////////////////////////////////////////////////////////7

void testAsics() {

//////////////////////////////////////////////////////////////
// POSICION ACTUAL CABEZAL
//////////////////////////////////////////////////////////////
//Posicion posActual; //VARIABLE GLOBAL QUE GUARDA LA POSICION ABSOLUTA DEL CABEZAL CADA VEZ QUE SE REALIZA UN MOVIMIENTO. se decide declararla como extern en una libreria

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

Celda celda_IN_INICIO; //DESDE LABVIEW
Celda celda_OK_INICIO;
Celda celda_NOK_INICIO;

Celda celdaEntrada; //Variable Celda de entrada. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
Celda celdaOK; 
Celda celdaNOK;

String resultadoTest;

enum state {START,ESPERA_HOME,HACER_HOME,RECIBIR_DATOS_ESTACION,RECIBIR_DATOS_TEST, ESPERAR_COMIENZO,IR_ENTRADA, DEJAR_SOCKET ,ESPERAR_TEST,COGER_SOCKET,DEJAR_OK_NOK,SIGUIENTE_CHIP,TERMINAR} mystate=START;


while (true){
      
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
              delay(100);
      
              mystate = RECIBIR_DATOS_ESTACION ;
         }
    
    break;

    case  RECIBIR_DATOS_ESTACION: //LISTEN TO LABVIEW: RECIBE UNA TRAMA DE BYTES DE STRING CUANDO PRESIONAMOS UN BOTON BOOLEANO EN LABVIEW
                                    //TRAMA ENVIADA DESDE LABVIEW ---> DATOS BANDEJA DE ENTRADA + DATOS BANDEJA OK + DATOS BANDEJA NOK + DATOS SOCKET
          {                                
              Serial.print("4"); //LABVIEW DEBE LEER ESTADO 4 
    
              while(!Serial.available()){}; //POLLING//////////////////////////////////
              delay(50);
			  char charRecibido = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos
              if (charRecibido =='E'){ 
                                                
                    Serial.print(charRecibido); //ECHO
                    Serial.read(); //limpianos del buffer RX el caracter E PARA QUE NO AFECTE A LAS SIGUIENTES LECTURAS EN LABVIEW
                    mystate = START;
                    return;
                    }

               else{
				   recibirDatosEstacion(&bandeja_IN , &bandeja_OK , &bandeja_NOK , &socket );//leo datos estación y ademas hago ECHO a labview
                   mystate = RECIBIR_DATOS_TEST;
				   }
      
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
			delay(50);
			char charRecibido = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos
              if (charRecibido =='E'){ 
                                                //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    Serial.print(charRecibido);
                    Serial.read(); //limpianos del buffer RX el caracter E
                    mystate = START;
                    return;
                    }
           
             else if (charRecibido=='1'){   //CARÁCTER ENVIADO POR LABVIEW COMO SEÑAL DE COMIENZO
			      Serial.read();
                  posActual.x=0; //reseteamos la strcutura que almacena el calculo de la posicion del cabezal en cada movimiento, antes de comenzar la tarea
                  posActual.y=0;
                  posActual.z=0;
                  celdaEntrada.fila  = celda_IN_INICIO.fila;
                  celdaEntrada.columna  = celda_IN_INICIO.columna;//Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
                  celdaOK.fila = celda_OK_INICIO.fila; 
				  celdaOK.columna = celda_OK_INICIO.columna;
                  celdaNOK.fila = celda_NOK_INICIO.fila;
				  celdaNOK.columna = celda_NOK_INICIO.columna;

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

    case  ESPERAR_TEST: //ESPERA AQUE SE LEA EL QR Y SE EJECUTE EL TEST Y LABVIEW MANDE EL RESULTADO
        {   
            
            esperarResultado(&resultadoTest); //POLLING HASTA QUE SE LEA EL RESULTADO ENVIADO POR LABVIEW OK O NOK ESCRIBIENDO EN LA VARIABLE "resultadoTest"
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

}


//////////////////////////////////////////////////////////////////////////////////////////////////TRASPASO ASICS///////////////////////////////////////////////////////////////////

void traspasoAsics(){

  //////////////////////////////////////////////////////////////
// POSICION ACTUAL CABEZAL
//////////////////////////////////////////////////////////////
//Posicion posActual; //VARIABLE GLOBAL QUE GUARDA LA POSICION ABSOLUTA DEL CABEZAL CADA VEZ QUE SE REALIZA UN MOVIMIENTO. se decide declararla como extern en una libreria

//////////////////////////////////////////////////////////////
// POSICION SOCKET
//////////////////////////////////////////////////////////////
//Posicion socket; //CONSTANTE A LO LARGO DEL PROGRAMA

//////////////////////////////////////////////////////////////
// BANDEJAS Y CELDAS DE TEST
//////////////////////////////////////////////////////////////
Bandeja bandeja_ORIGEN;
Bandeja bandeja_DESTINO;
Celda celda_COMIENZO_ORIGEN; //struct celdas formato (x,y) que recibo de Labview como datos de comienzo
Celda celda_COMIENZO_DESTINO;

Celda celdaORIGEN; // struct celdas formato (x,y) cuyas coordenadas se van incrementando a lo largo del programa
Celda celdaDESTINO;

/*Bandeja bandeja_IN;
Bandeja bandeja_OK;
Bandeja bandeja_NOK;

Celda celda_IN_INICIO;
Celda celda_OK_INICIO;
Celda celda_NOK_INICIO;

Celda celdaEntrada; //Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
Celda celdaOK; //Variable Celda de .En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview.Despues se irá actualizando en el bucle
Celda celdaNOK;*/



enum state {START,ESPERA_HOME,HACER_HOME,RECIBIR_DATOS_ESTACION,RECIBIR_DATOS_TEST, ESPERAR_COMIENZO,IR_BANDEJA_ORIGEN,IR_BANDEJA_DESTINO,SIGUIENTE_CHIP,TERMINAR} mystate=START;

while(true){
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
              Serial.print("2");
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

              Serial.print("3"); //ENVÍO A LABVIEW FLAG DE ESTADO
              Home(); //AQUI MOVEMOS MOTORES
              Serial.print("FH");//ENVIO A LABVBIEW UN COMANDO DE FIN DEL MOVIMIENTO.
              delay(100);
      
              mystate = RECIBIR_DATOS_ESTACION ;
         }
    
    break;

    case  RECIBIR_DATOS_ESTACION: 
          {                                
              Serial.print("4"); //ENVÍO A LABVIEW FLAG DE ESTADO 
    
              while(!Serial.available()){}; //POLLING DE ESCUCHA DE DATOS DE MOVIMIENTO Ó COMANDO DE SALIR
              delay(50);
              char charRecibido = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos
              if (charRecibido =='E'){ 
                                                
                    Serial.print(charRecibido); //ECHO
                    Serial.read(); //limpianos del buffer RX el caracter E PARA QUE NO AFECTE A LAS SIGUIENTES LECTURAS EN LABVIEW
                    mystate = START;
                    return;
                    }

              else {
                    recibirDatosEstacion_TRASPASO(&bandeja_ORIGEN , &bandeja_DESTINO);//leo datos estación y ademas la funcion hace echo a labview : 14 datos 

              
                    mystate = RECIBIR_DATOS_TEST;}
      
          } 

          
                          
    break;


    case  RECIBIR_DATOS_TEST: 
          {                                
              Serial.print("5"); //ENVÍO A LABVIEW FLAG DE ESTADO 
    
              while(!Serial.available()){}; //POLLING//////////////////////////////////
              delay(50);
    
              recibirDatosTest_TRASPASO(&celda_COMIENZO_ORIGEN, &celda_COMIENZO_DESTINO); //leo datos de test y ademas hago echo a labview
       
              mystate = ESPERAR_COMIENZO;
          } 

          
                          
    break;

    case  ESPERAR_COMIENZO: //AQUI PUEDO RESETEAR TODAS LOS CALCULOS DEL ULTIMO TEST EJECUTADO QUE NECESITEN PARTIR DE CERO

     //Serial.print("7"); //ENVÍO A LABVIEW FLAG DE ESTADO
          {
            
              while(!Serial.available()){}; //POLLING DE ESCUCHA DE BOTON COMENZAR Ó COMANDO DE SALIR
              delay(50);
              char charRecibido = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos
              if (charRecibido =='E'){ 
                                                //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    Serial.print(charRecibido);
                    Serial.read(); //limpianos del buffer RX el caracter E
                    mystate = START;
                    return;
                    }
              else if (charRecibido =='1'){
				     Serial.read();
                     posActual.x=0; //se pone a cero posActual , posicion del cabezal en el tablero.
                     posActual.y=0;
                     posActual.z=0;
                     celdaORIGEN.fila  = celda_COMIENZO_ORIGEN.fila;
                     celdaORIGEN.columna  = celda_COMIENZO_ORIGEN.columna;					 //Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
                     celdaDESTINO.fila = celda_COMIENZO_DESTINO.fila;
                     celdaDESTINO.columna = celda_COMIENZO_DESTINO.columna;					 //Variable Celda de .En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview.Despues se irá actualizando en el bucle
            //Celda celdaNOK = celda_NOK_INICIO;

                     mystate = IR_BANDEJA_ORIGEN;}
              else
            {
                     mystate = START;}
               
            }

    
    break;

    case  IR_BANDEJA_ORIGEN: //IR A LA BANDEJA DE ENTRADA A COGER CHIP

    //Serial.print("8"); //ENVÍO A LABVIEW FLAG DE ESTADO
        {
            cogerDeBandeja(&bandeja_ORIGEN, celdaORIGEN);
            delay(500);			                               //RECIBE PUNTERO A UNA BANDEJA PARA ACCEDER A SUS ATRIBUTOS DIRECTAMENTE SIN TENER QUE CREAR UNA COPIA EN MEMORIA
            siguienteCelda(&bandeja_ORIGEN, &celdaORIGEN);    //CALCULA UNA POSICION DE BANDEJA DONDE IR,SE MUEVE A ESA POSICION,ACTIVA VACÍO Y COGE EL CHIP
                                                              //ACTUALIZA LA POSICION ABSOLUTA DEL CABEZAL EN X,Y,Z--> posActual
            mystate = IR_BANDEJA_DESTINO;
        }
    break;

    case  IR_BANDEJA_DESTINO: //DEJA UN CHIP EN EL SOCKET

        {   
           dejarEnBandeja(&bandeja_DESTINO, celdaDESTINO);
           delay(500);		   //CALCULA EL TRAYECTO PARA IR AL SOCKET DESDE LA POSICION QUE SE ENCUENTRE EL CABEZAL Y LA POSICION FIJA DEL SOCKET.
           siguienteCelda(&bandeja_DESTINO, &celdaDESTINO);
           Serial.print("FM");                                                                    //EJECUTA EL MOVIMIENTO
                                                                                //ACTUALIZA LA POSICION ABSOLUTA DEL CABEZAL EN X,Y,Z--> posActual
            
            mystate = SIGUIENTE_CHIP;

        }
    
    break;

    case SIGUIENTE_CHIP: //ESPERAMOS A QUE LABVIEW NOS DIGA SI SE HA TERMINADO LA TANDA DE CHIPS O SEGUIMOS CON EL SIGUIENTE
    {
    while(!Serial.available()){}; //POLLING//////////////////////////////////
    String finTest = Serial.readString();
    if (finTest =="SI") //si labview determina que ha terminado de testear todos los asics nos envía SI  
    {      Home(); 
           Serial.print("FH");
           mystate = RECIBIR_DATOS_ESTACION; 
    }
    else if(finTest =="NO"){ //SI NO HA TERMINADO VUELVO A COGER OTRO ASIC , MIENTRAS LABVIEW ESPERA 
    mystate = IR_BANDEJA_ORIGEN;
    }
    else { mystate = START; }
      
    
    }
    break;


}
}
}

/////////////////////////////////////////////////////////////////////////////////////LECTURA QR///////////////////////////////////////////////////

void leerQR(){

  //////////////////////////////////////////////////////////////
// POSICION ACTUAL CABEZAL
//////////////////////////////////////////////////////////////
//Posicion posActual; //VARIABLE GLOBAL QUE GUARDA LA POSICION ABSOLUTA DEL CABEZAL CADA VEZ QUE SE REALIZA UN MOVIMIENTO. se decide declararla como extern en una libreria

//////////////////////////////////////////////////////////////
// POSICION SOCKET
//////////////////////////////////////////////////////////////
Posicion socket; 

//////////////////////////////////////////////////////////////
// BANDEJAS Y CELDAS DE TEST
//////////////////////////////////////////////////////////////

Bandeja bandeja_QR;
//Bandeja bandeja_OK;
//Bandeja bandeja_NOK;

Celda celda_INICIO_QR;
//Celda celda_OK_INICIO;
//Celda celda_NOK_INICIO;

Celda celdaQR; //Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
//Celda celdaOK; //Variable Celda de .En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview.Despues se irá actualizando en el bucle
//Celda celdaNOK;

String resultado_Lectura;

initServo();
relajacionSocket();

enum state {START,ESPERA_HOME,HACER_HOME,RECIBIR_DATOS_ESTACION,RECIBIR_DATOS_LECTURAQR, ESPERAR_COMIENZO,IR_ENTRADA_QR, DEJAR_SOCKET ,ESPERAR_LECTURA_QR,COGER_SOCKET,DEJAR_EN_BANDEJA,SIGUIENTE_CHIP,TERMINAR} mystate=START;
while(true){
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
              Serial.print("2");
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

              Serial.print("3"); //ENVÍO A LABVIEW FLAG DE ESTADO
              Home(); //AQUI MOVEMOS MOTORES
              Serial.print("FH");//ENVIO A LABVBIEW UN COMANDO DE FIN DEL MOVIMIENTO.
              delay(100);
      
              mystate = RECIBIR_DATOS_ESTACION ;
         }
    
    break;

    case  RECIBIR_DATOS_ESTACION: //LISTEN TO LABVIEW: RECIBE UNA TRAMA DE BYTES DE STRING CUANDO PRESIONAMOS UN BOTON BOOLEANO EN LABVIEW
                                  //TRAMA ENVIADA DESDE LABVIEW ---> DATOS BANDEJA DE ENTRADA 
          {                                
              Serial.print("4"); //ENVÍO A LABVIEW FLAG DE ESTADO QUE LEO EN EL ESTADO DE LABVIEW "ENVIAR_CONFIG_TEST"
    
              while(!Serial.available()){}; //POLLING BOTON ENVIAR DATOS LABVIEW//////////////////////////////////
              delay(50);
              char charRecibido = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos

              if (charRecibido=='E'){ 
                    Serial.print(charRecibido);//ECHO
                    Serial.read();//limpio buffer de RX
                     //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    
                    mystate = START;
                    return;
              }

              else {
                    recibirDatosEstacion_QR(&bandeja_QR, &socket );//leo datos estación y ademas hago ECHO a labview
                    mystate = RECIBIR_DATOS_LECTURAQR;
                   }
          } 

          break;


    case  RECIBIR_DATOS_LECTURAQR: //LISTEN TO LABVIEW: RECIBE UNA TRAMA DE BYTES DE STRING CUANDO PRESIONAMOS UN BOTON BOOLEANO EN LABVIEW
                                    //TRAMA ENVIADA DESDE LABVIEW ---> DATOS celda DE ENTRADA
          {                                
              Serial.print("5"); //ENVÍO A LABVIEW FLAG DE ESTADO 
    
              while(!Serial.available()){}; //POLLING//////////////////////////////////
              delay(50);
    
              recibirDatos_LecturaQR(&celda_INICIO_QR); //leo datos de test y ademas hago echo a labview
       
              mystate = ESPERAR_COMIENZO;
          } 

          
                          
    break;

    case  ESPERAR_COMIENZO: //AQUI PUEDO RESETEAR TODAS LOS CALCULOS DEL ULTIMO TEST EJECUTADO QUE NECESITEN PARTIR DE CERO

         //Serial.print("7"); //ENVÍO A LABVIEW FLAG DE ESTADO
          {
           
            while(!Serial.available()){}; //POLLING//////////////////////////////////
            delay(50);
              char charRecibido = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos

              if (charRecibido=='E'){ 
                    Serial.print(charRecibido);//ECHO
                    Serial.read();//limpio buffer de RX
                     //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    
                    mystate = START;
                    return;
              }
              else if (charRecibido =='1'){
				    Serial.read();
                    posActual.x=0;
                    posActual.y=0;
                    posActual.z=0;
                    celdaQR.fila  = celda_INICIO_QR.fila; 
					celdaQR.columna  = celda_INICIO_QR.columna; //Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
            //Celda celdaOK = celda_OK_INICIO; //Variable Celda de .En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview.Despues se irá actualizando en el bucle
            //Celda celdaNOK = celda_NOK_INICIO;

                    mystate = IR_ENTRADA_QR;
               
          }
              else {
                    mystate = START;}
           }

    break;

    case  IR_ENTRADA_QR: //IR A LA BANDEJA DE ENTRADA A COGER CHIP

    //Serial.print("8"); //ENVÍO A LABVIEW FLAG DE ESTADO
        {
            cogerDeBandeja(&bandeja_QR, celdaQR); //RECIBE PUNTERO A UNA BANDEJA PARA ACCEDER A SUS ATRIBUTOS DIRECTAMENTE SIN TENER QUE CREAR UNA COPIA EN MEMORIA
                                                       //CALCULA UNA POSICION DE BANDEJA DONDE IR,SE MUEVE A ESA POSICION,ACTIVA VACÍO Y COGE EL CHIP
                                                       //ACTUALIZA LA POSICION ABSOLUTA DEL CABEZAL EN X,Y,Z--> posActual
            mystate = DEJAR_SOCKET;
        }
    break;

    case  DEJAR_SOCKET://DEJA UN CHIP EN EL SOCKET

        {   dejarEnSocket(socket); 
            Serial.print("1");	//CALCULA EL TRAYECTO PARA IR AL SOCKET DESDE LA POSICION QUE SE ENCUENTRE EL CABEZAL Y LA POSICION FIJA DEL SOCKET.
            delay(500);         //EJECUTA EL MOVIMIENTO
                                //ACTUALIZA LA POSICION ABSOLUTA DEL CABEZAL EN X,Y,Z--> posActual
            
            mystate = ESPERAR_LECTURA_QR;

        }
    
    break;

    case  ESPERAR_LECTURA_QR: //ESPERA AQUE SE EJECUTE EL TEST Y LABVIEW MANDE EL RESULTADO
        {   
            Serial.print("6");
			
			
			while(!Serial.available()){};
			
			String lectura = Serial.readString();
			//Serial.print(lectura);
			//mystate = COGER_SOCKET;
			
			
            if (lectura =="OK"){
				 Serial.print("OK");
				 
                 mystate = COGER_SOCKET;} 
        
            else if (lectura == "NOK"){
                 mystate = START;
				 Serial.print("NOK");
            }
			
			else{ mystate = START;}
        }   
    break;

    case COGER_SOCKET:
        {  
            cogerDelSocket(socket); //CALCULA EL TRAYECTO X,Y,Z PARA IR AL SOCKET , PERO COMO YA ESTÁ EN LA POSICION DE SOCKET (LA ULTIMA QUE GUARDÓ) EL CABEZAL NO SE MUEVE EN X,Y
            mystate = DEJAR_EN_BANDEJA;
        }
    break;

    case DEJAR_EN_BANDEJA:
    {      
           dejarEnBandeja(&bandeja_QR, celdaQR);
        
           siguienteCelda(&bandeja_QR, &celdaQR);//modifica la coordenada actual de la celda de entrada para el siguiente chip
           Serial.print("FM"); //enviamos a labview que ha terminado de depositar el chip
           mystate = SIGUIENTE_CHIP;
    }
    break;

    case SIGUIENTE_CHIP: //ESPERAMOS A QUE LABVIEW NOS DIGA SI SE HA TERMINADO LA TANDA DE CHIPS O SEGUIMOS CON EL SIGUIENTE
    {
            while(!Serial.available()){}; //POLLING//////////////////////////////////
            String fin_LECTURA_QR = Serial.readString();
            if (fin_LECTURA_QR =="SI") //si labview determina que ha terminado de leer todos los QR nos envía SI  
    {             Home(); 
                  Serial.print("FH");
                  mystate = RECIBIR_DATOS_ESTACION; 
    }
            else if(fin_LECTURA_QR =="NO"){ //SI NO HA TERMINADO VUELVO A COGER OTRO ASIC , MIENTRAS LABVIEW ESPERA 
                  mystate = IR_ENTRADA_QR;
    }
            else { mystate = START; }
    
    }
    break;
}
}
}



