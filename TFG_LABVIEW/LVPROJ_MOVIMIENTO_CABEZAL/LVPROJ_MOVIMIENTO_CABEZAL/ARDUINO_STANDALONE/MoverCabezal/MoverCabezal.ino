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




//const long pulsos_rev = 6400; //Numero de pulsos por revolucion del motor






struct tramaMovimiento{
      uint8_t sentido;
      long pasos;
      char eje;
};

tramaMovimiento trama;


enum state { START, ESPERA_COMANDO_HOME ,HACER_HOME, ESPERA_POSICION_INICIO, MOVER_POSICION_INICIO, RECIBIR_DATOS_MOVIMIENTO, MOVER_X , MOVER_Y , MOVER_Z , TERMINAR_MOVIMIENTO } mystate=START;

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
  enableMotores();
  Home();
  //Home();

  

}

void loop() {


  switch (mystate){
    
       case START:
       {
           while (!Serial.available()){} //espero Ping desde labview: "Q?"  POLLING
           String comandoPing=Serial.readString(); //funcion para leer cadena de texto
  
           if (comandoPing.equals("Q?")) //SSi labview me hace ping contesto que estoy preparado para comenzar COM
                {
                Serial.print("R!");
                delay(100);
   //contesto ready
                mystate = ESPERA_COMANDO_HOME;
                } //contesto ready

           else {
                mystate = START;
                }
        }     
     
    
    break;

        case ESPERA_COMANDO_HOME:  //LISTEN TO LABVIEW : LEEMOS UN BYTE 'H' PARA HACER HOME   
        {
     //ENVÍO A LABVIEW FLAG DE ESTADO
              Serial.print("2");
              char comandoHome=LeerComando_1byte();
    
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
              delay(500);
      
              mystate = RECIBIR_DATOS_MOVIMIENTO ;
         }
    
    break;

    /*case ESPERA_POSICION_INICIO: //LISTEN TO LABVIEW: ESPERAMOS A QUE LABVIEW NOS ENVIE EL COMANDO DE IR A POSICION DE INICIO CON EL CABEZAL
     {
               Serial.print("4"); //ENVÍO A LABVIEW FLAG DE ESTADO
               char comandoInicio=LeerComando_1byte();
               if (comandoInicio == 'I') { //SI EL COMANDO ES EL CORRECTO MUEVO EL CABEZAL DESDE HOME HASTA UNA POSICION DE INICIO
                   mystate = MOVER_POSICION_INICIO;
    //Serial.print(comando1);

                 }
               else if(comandoInicio != 'I') {
               mystate = ESPERA_POSICION_INICIO;

                  }
       }
    

    break;

    case MOVER_POSICION_INICIO : //CODIGO PARA MOVER MOTORES Y COLOCAR EL CABEZAL EN POSICION DE INICIO 
         {
               Serial.print("5");
               enableMotores();
               digitalWrite(pul_x,LOW);
               delay(10);
               digitalWrite(pul_y,LOW);
               delay(10);
               derecha_X();
               delay(10);
               movimiento(pul_x,5000,50); //FUNCION QUE ENVIA 25000 PASOS AL MOTOR Y
               avance_Y();
               delay(100);
               movimiento(pul_y,5000,50); //FUNCION QUE ENVIA 25000 PASOS AL MOTOR Y
               delay(10);
               Serial.print("FI"); //ENVIO A LAVBIEW UN COMANDO DE FIN DEL MOVIMIENTO.
               delay(500);

    mystate = RECIBIR_DATOS_MOVIMIENTO;

    }

    break;*/

    case  RECIBIR_DATOS_MOVIMIENTO: //LISTEN TO LABVIEW: RECIBE UNA TRAMA DE BYTES DE STRING CUANDO PRESIONAMOS UN BOTON BOOLEANO EN LABVIEW
                                    //TRAMA ENVIADA DESDE LABVIEW ---> 1 BYTE : SENTIDO [0,1] + \n + "n BYTES de PASOS" + \n + 1BYTE: eje [X ó Y]+\n 
                                    //, y puede irse a mover x , mover y , mover z ó a terminar movimiento
          {                                
              Serial.print("6"); //ENVÍO A LABVIEW FLAG DE ESTADO 
    
              while(!Serial.available()){};
    
              String dato;
              delay(50);

              dato = Serial.readStringUntil('\n');
              trama.sentido=dato.toInt();
              dato = Serial.readStringUntil('\n');
              trama.pasos=dato.toInt();
              String ejeStr = Serial.readStringUntil('\n');
              trama.eje = ejeStr.charAt(0);
       
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
                      if(trama.pasos>5000) {movimiento(pul_x,trama.pasos,50);}
                      else {movimientoCorto(pul_x,trama.pasos);}
                
                

                } //avanza
                else if (trama.sentido==1){
                      izquierda_X();
                      if(trama.pasos>5000) {movimiento(pul_x,trama.pasos,50);}
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
                if(trama.pasos>5000) {movimiento(pul_y,trama.pasos,50);}
                else {movimientoCorto(pul_y,trama.pasos);}    
                 
                 } //avanza
                 else if (trama.sentido==1){
                 retroceso_Y();
                 if(trama.pasos>5000) {movimiento(pul_y,trama.pasos,50);}
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
