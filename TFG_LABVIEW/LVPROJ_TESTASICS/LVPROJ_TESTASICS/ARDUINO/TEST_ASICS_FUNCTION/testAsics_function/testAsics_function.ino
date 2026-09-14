
#include "libreria_tareas.h"
#include "libreria_robot.h"
#include <Arduino.h>
#include <config_pines_arduino.h>


////////////////////////////////////////////////////////////////////////////TEST ASICS/////////////////////////////////////////////////////////

void testAsics() {

//////////////////////////////////////////////////////////////
// POSICION ACTUAL CABEZAL
//////////////////////////////////////////////////////////////
//Posicion posActual; //VARIABLE GLOBAL QUE GUARDA LA POSICION ABSOLUTA DEL CABEZAL CADA VEZ QUE SE REALIZA UN MOVIMIENTO

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


