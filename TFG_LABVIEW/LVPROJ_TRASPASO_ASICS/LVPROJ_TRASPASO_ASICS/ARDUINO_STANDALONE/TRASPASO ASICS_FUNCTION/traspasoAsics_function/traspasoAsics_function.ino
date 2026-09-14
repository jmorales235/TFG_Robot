void traspasoAsics(){

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
Bandeja bandeja_ORIGEN;
Bandeja bandeja_DESTINO;
Celda celda_COMIENZO_ORIGEN;
Celda celda_COMIENZO_DESTINO;

Celda celdaORIGEN;
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
              delay(500);
      
              mystate = RECIBIR_DATOS_ESTACION ;
         }
    
    break;

    case  RECIBIR_DATOS_ESTACION: 
          {                                
              Serial.print("4"); //ENVÍO A LABVIEW FLAG DE ESTADO 
    
              while(!Serial.available()){}; //POLLING ESPERA A BOTON ENVIAR DATOS
              delay(50);
              recibirDatosEstacion_TRASPASO(&bandeja_ORIGEN , &bandeja_DESTINO);//leo datos estación y ademas hago ECHO a labview

              
              mystate = RECIBIR_DATOS_TEST;
      
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
            while(!Serial.available()){}; //POLLINg BOTON COMENZAR
            char flag = Serial.read();
            if (flag=='1'){
                     posActual.x=0;
                     posActual.y=0;
                     posActual.altura_z=0;
                     Celda celdaORIGEN  = celda_COMIENZO_ORIGEN; //Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
                     Celda celdaDESTINO = celda_COMIENZO_DESTINO; //Variable Celda de .En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview.Despues se irá actualizando en el bucle
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
            cogerDeBandeja(&bandeja_ORIGEN, celdaORIGEN); //RECIBE PUNTERO A UNA BANDEJA PARA ACCEDER A SUS ATRIBUTOS DIRECTAMENTE SIN TENER QUE CREAR UNA COPIA EN MEMORIA
            siguienteCelda(&bandeja_ORIGEN, &celdaORIGEN);//CALCULA UNA POSICION DE BANDEJA DONDE IR,SE MUEVE A ESA POSICION,ACTIVA VACÍO Y COGE EL CHIP
                                                       //ACTUALIZA LA POSICION ABSOLUTA DEL CABEZAL EN X,Y,Z--> posActual
            mystate = IR_BANDEJA_DESTINO;
        }
    break;

    case  IR_BANDEJA_DESTINO: //DEJA UN CHIP EN EL SOCKET

        {   
           dejarEnBandeja(&bandeja_DESTINO, celdaDESTINO);                     //CALCULA EL TRAYECTO PARA IR AL SOCKET DESDE LA POSICION QUE SE ENCUENTRE EL CABEZAL Y LA POSICION FIJA DEL SOCKET.
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