/* Teoricamente:
1mm= 91 pasos
1cm = 910 pasos
10 cm = 9100 pasos
0.1 mm = 9 pasos aprox
*/



struct tramaMovimiento{
      uint8_t sentido;
      long pasos;
      char eje;
};

tramaMovimiento trama;


enum state { START, ESPERA_COMANDO_HOME ,HACER_HOME, ESPERA_POSICION_INICIO, MOVER_POSICION_INICIO, RECIBIR_DATOS_MOVIMIENTO, MOVER_X , MOVER_Y , MOVER_Z , TERMINAR_MOVIMIENTO } mystate=START;

while(true){
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
                } 

           else {
                mystate = START;
                }
        }     
     
    
    break;

        case ESPERA_COMANDO_HOME: //LISTEN TO LABVIEW : LEEMOS UN BYTE 'H' PARA HACER HOME *********************punto de exit**********************
        {
     
              Serial.print("2"); //ENVÍO A LABVIEW FLAG DE ESTADO
              while(!Serial.available()){}; //POLLING DE ESCUCHA DE DATOS DE MOVIMIENTO Ó COMANDO DE SALIR
              delay(50);
              char charRecibido = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos
              if (charRecibido=='E'){ 
                    Serial.read(); //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    Serial.print(charRecibido);
                    mystate = START;
                    return;
                    }

              else if (charRecibido == 'H'){
                    mystate=HACER_HOME;
              }
        }
    

    break;
    
         case HACER_HOME: //codigo para hacer home

         {

              Serial.print("3"); //ENVÍO A LABVIEW FLAG DE ESTADO
              Home(); //AQUI MOVEMOS MOTORES
              Serial.print("FH");//ENVIO A LABVBIEW UN COMANDO DE FIN DEL MOVIMIENTO.
              delay(500);
      
              mystate = ESPERA_POSICION_INICIO;
         }
    
    break;

   

    case  RECIBIR_DATOS_MOVIMIENTO: //LISTEN TO LABVIEW: RECIBE UNA TRAMA DE BYTES DE STRING CUANDO PRESIONAMOS UN BOTON BOOLEANO EN LABVIEW
                                    //TRAMA ENVIADA DESDE LABVIEW ---> 1 BYTE : SENTIDO [0,1] + \n + "n BYTES de PASOS" + \n + 1BYTE: eje [X ó Y]+\n 
                                    //, y puede irse a mover x , mover y , mover z ó a terminar movimiento
          {                                
              Serial.print("6"); //ENVÍO A LABVIEW FLAG DE ESTADO 
    
              while(!Serial.available()){}; //POLLING DE ESCUCHA DE DATOS DE MOVIMIENTO Ó COMANDO DE SALIR
              
              delay(50);
              char primerChar = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos

              if (primerChar=='E'){ 
                    
                    Serial.read(); //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    Serial.print(primerChar);
                    mystate = START;
                    return;
              }

              else{
              
                    String dato;
                    dato = Serial.readStringUntil('\n');
                    trama.sentido=dato.toInt();
                    dato = Serial.readStringUntil('\n');
                    trama.pasos=dato.toInt();
                    String ejeStr = Serial.readStringUntil('\n');
                    trama.eje = ejeStr.charAt(0);

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
                
                

                } //avanza
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

