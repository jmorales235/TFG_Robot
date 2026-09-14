void leerQR(){

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
              while(!Serial.available()){}; //POLLING DE ESCUCHA DE DATOS DE MOVIMIENTO Ó COMANDO DE SALIR
              delay(50);
              char charRecibido = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos
              if (charRecibido=='E'){ 
                    Serial.read(); //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    Serial.print(primerChar);
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
              delay(100);
      
              mystate = RECIBIR_DATOS_ESTACION ;
         }
    
    break;

    case  RECIBIR_DATOS_ESTACION: //LISTEN TO LABVIEW: RECIBE UNA TRAMA DE BYTES DE STRING CUANDO PRESIONAMOS UN BOTON BOOLEANO EN LABVIEW
                                  //TRAMA ENVIADA DESDE LABVIEW ---> DATOS BANDEJA DE ENTRADA + DATOS BANDEJA OK + DATOS BANDEJA NOK + DATOS SOCKET
          {                                
              Serial.print("4"); //ENVÍO A LABVIEW FLAG DE ESTADO 
    
              while(!Serial.available()){}; //POLLING BOTON ENVIAR DATOS LABVIEW//////////////////////////////////
              delay(50);
              char primerChar = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos

              if (primerChar=='E'){ 
                    Serial.print(primerChar);//ECHO
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
                                    //TRAMA ENVIADA DESDE LABVIEW ---> DATOS BANDEJA DE ENTRADA + DATOS BANDEJA OK + DATOS BANDEJA NOK + DATOS SOCKET
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
              char primerChar = Serial.peek(); //Consultamos el primer caracter que llega pero no lo saca del buffer.Si es comando para salir E, entonces nos salimos

              if (primerChar=='E'){ 
                    Serial.print(primerChar);//ECHO
                    Serial.read();//limpio buffer de RX
                     //Aqui ya, SI retiramos el caracter del buffer con una lectura normal para que no afecte a las siguientes lecturas.
                    
                    mystate = START;
                    return;
              }
              else if (primerChar=='1'){
                    posActual.x=0;
                    posActual.y=0;
                    posActual.altura_z=0;
                    Celda celdaQR  = celda_INICIO_QR; //Variable Celda de INICIO. En la primera iteracion contendrá el valor de la coordenada de inicio que le enviamos desde labview. Despues se irá actualizando en el bucle
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

    case  DEJAR_SOCKET: //DEJA UN CHIP EN EL SOCKET

        {   dejarEnSocket(socket); 
            Serial.print("1");                         //CALCULA EL TRAYECTO PARA IR AL SOCKET DESDE LA POSICION QUE SE ENCUENTRE EL CABEZAL Y LA POSICION FIJA DEL SOCKET.
                                                       //EJECUTA EL MOVIMIENTO
                                                       //ACTUALIZA LA POSICION ABSOLUTA DEL CABEZAL EN X,Y,Z--> posActual
            
            mystate = ESPERAR_LECTURA_QR;

        }
    
    break;

    case  ESPERAR_LECTURA_QR: //ESPERA AQUE SE EJECUTE EL TEST Y LABVIEW MANDE EL RESULTADO
        {   
            
            esperar_LecturaQR (&resultado_Lectura);
            if (resultado_Lectura=="OK"){
                 mystate = COGER_SOCKET;} 
        
            else {
                 mystate = START;
            }
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
    if (fin_LECTURA_QR =="SI") //si labview determina que ha terminado de testear todos los asics nos envía SI  
    {      Home(); 
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
