



/*VÁLIDO PARA ARDUINO MEGA 2650
EL CODIGO ARDUINO MASTER DEBE:
CONFIGURAR EL PUERTO SERIAL
CONTENER LAS VARIABLES y FUNCIONES GLOBALES QUE SE UTILIZARÁN A LO LARGO DEL PROGRAMA
INICIALIZAR EL VALOR DE LAS VARIABLES POR DEFECTO
ESPERAR A QUE LABVIEW LE DIGA QUÉ TAREA REALIZAR, NO QUEDA MÁS REMEDIO QUE HACER POLLING EN EL PUERTO SERIAL
CONTENER LA RUTINA/S DE ECHO CON LABVIEW ANTES DE COMENZAR UNA TAREA CONFIRMANDO LA ORDEN QUE HA RECIBIDO
GESTIONAR LA TRAMA DE DATOS QUE RECIBE DE LABVIEW, Y SELECCIONAR LA TAREA EN FUNCION DE ELLO

QUEDARSE ESPERANDO A QUE LA TAREA SE TERMINE (¿QUIEN INDICA QUE SE HA ACABADO LA TAREA, LABVIEW A ARDUINO Ó ARDUINO A LABVIEW?)

LOS DATOS QUE SE VAN A INTERCAMBIAR ARDUINO Y LABVIEW SERÁN EN TRAMAS DE BYTES CONSECUTIVAS Ó DE FLAGS DE 1 BYTE.
*/


#include <libreria_robot.h> 
/*los ficheros .h y.cpp que nos creamos como usuario deben estar en una carpeta llamada "libraries" situada en el "sketchbook location" definido en "Preferences", para que el compilador las vea.
asegurarse de que la extension real de los ficheros sean .h y .cpp y NO sea .txt,para ello habilitar la opcion visualizar extension de fichero en windows.
dentro de libraries ya hacemos una carpeta que se llame como el fichero .h y .cpp que deben estar dentro.*/

#include <config_pines_arduino.h> //en este fichero mapeamos las variables de pin a los pines fisicos de arduino con directivas #define
/*config_pines define las señales: dir_y, pul_y, ena_y, dir_x ,dir_x ,pul_x ,ena_x, dir_z, pul_z ,ena_z ,bomba ,pin_servo ,sensor_x ,sensor_y ,sensor_z*/

#include <libreria_tareas.h>
#include <libreria_funciones_tareas.h>



enum state {ESPERA_PING , ESPERA_TAREA, MOVER_CABEZAL, TEST_ASICS, LEER_QR , TRASLADO_ASICS, CONFIG_ESTACION} state=ESPERA_PING;


void setup() {
  
  Serial.begin(9600); //velocidad suficiente para el sistema de COM
  
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

  
  digitalWrite(pul_x, LOW);
  digitalWrite(pul_y, LOW);
  digitalWrite(pul_z, LOW);
  disableMotores();
  


  initServo();
  //SERVO DEL SOCKET
  relajacionSocket();
  
  }


void loop() {
  
  switch (state) {
      
      case ESPERA_PING: //FRONT PANEL DE LABVIEW : ROBOT MASTER
      {
         while (!Serial.available()){} //espero Ping desde labview: "Q?"  POLLING
         
         char primerChar = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos
         if (primerChar =='E'){ //checkeamos si el usuario ha presionado "exit" en front panel de Robot Master en labview en vez de "Init Com"
                    Serial.print(primerChar);//echo
                    Serial.read(); //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas. Labview se detiene al recibir echo.
                    
                    state = ESPERA_PING;
                    return;
         }
         String comandoPing=Serial.readString(); //si no hay exit, recibimos string de ping, si el caracter recibido es erroneo
  
         if (comandoPing.equals("Q?")) //Si labview me hace ping contesto que estoy preparado para recibir tarea
                   {Serial.print("R!");//si no fuese Q! el string recibido no devolveria R!. Labivew daría error de timeout en Visa read y todo se para.
                  state = ESPERA_TAREA;} //contesto ready
         else { 
                state = ESPERA_PING;
         }
      }
        
        
        break;
      case ESPERA_TAREA: //Espera a que se pulse un boton del panel de tareas o a que se pulse el boton salirnos del programa robot master una vez confirmado la COM
      {
          while (!Serial.available()){} //espero comando tarea
          char primerChar = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos
          if (primerChar =='E'){
                    Serial.print(primerChar);
                    Serial.read(); //Aqui ya, retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    
                    state = ESPERA_PING;
                    return;
         }
          char comandotarea = Serial.read(); //leemos comando tarea
          Serial.print(comandotarea); //echo , ack ACUSE DE RECIBO a labview
          if (comandotarea == 'M'){ 
              state = MOVER_CABEZAL;
          }
          else if (comandotarea == 'S'){ 
              state = CONFIG_ESTACION;
          }
          
          else if (comandotarea== 'T'){
              state = TEST_ASICS;
          }

          else if (comandotarea== 'Q'){
              state = LEER_QR;
          }
          else if (comandotarea== 'U'){
              state = TRASLADO_ASICS;
          }
          else {state = ESPERA_PING;}
      }
          
        
        break;
      case MOVER_CABEZAL: //FRONT PANEL DE LABVIEW : MOVER CABEZAL
        {
           //Serial.print('2');
           enableMotores();//energiza los motores , no se pueden mover con la mano
           Home_inicial();
           moverCabezal(); //llama a la maquina de estados que mueve el cabezal manualmente
           state = ESPERA_PING;

        }

        
        break;
      case TEST_ASICS: //FRONT PANEL DE LABVIEW : TEST_ASICS
        enableMotores();//energiza los motores , no se pueden mover con la mano
        Home_inicial();
        testAsics();

        state = ESPERA_PING;
        
        break;

      case LEER_QR:    //FRONT PANEL DE LABVIEW : LEER QR
        Home_inicial();
        leerQR();
        state = ESPERA_PING;

        break;

      case TRASLADO_ASICS: //FRONT PANEL DE LABVIEW : MOVER ASICS

        traspasoAsics();
        state = ESPERA_PING;

        break;

      case CONFIG_ESTACION: //FRONT PANEL DE LABVIEW : CONFIG ESTACION
        {
            bool salirConfig = false;

            while (!salirConfig)
            {
                while (!Serial.available()) {} //esperamos comando C o E del VI de configurar estacion

                char comando = Serial.read();

                if (comando == 'C')   //  Se ha presionado el boton de labview "Set coordenadas bandejas"
                {
                     //Serial.print(comando);  // echo si quieres mantener tu protocolo
                     enableMotores();
                     Home_inicial();
                     moverCabezal(); //LAbview entra en el VI de movercabezal en el modo configuracion

            // Cuando termina moverCabezal(),
            // seguimos dentro del while.
            // Arduino vuelve a esperar comandos
            // del VI Config Estación.
                 }

                else if (comando == 'E')   // Exit del VI Config Estación
                {
                     //Serial.print(comando);

                     salirConfig = true;
                }
              }

               state = ESPERA_PING;
            }
      break;
    }

  
}