


enum state { START, ESPERA_COMANDO_HOME ,HACER_HOME, MOVER_POSICION_INICIO, RECIBIR_DATOS_MOVIMIENTO, MOVER_X , MOVER_Y , MOVER_Z , TERMINAR_MOVIMIENTO } mystate=START;
void setup() {
  Serial.begin(9600); 

  /*pinMode(sensor_x,INPUT);
  pinMode(sensor_y,INPUT);
  pinMode(sensor_z,INPUT);
  pinMode(Led,OUTPUT);
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
  digitalWrite(ena_x,HIGH);
  digitalWrite(ena_y,HIGH);
  digitalWrite(ena_z,HIGH);

*/
}

void loop() {
 
 //Home();
  
  //mystate = START;
  Serial.print("VUELVO");
  delay(2000);
  switch (mystate){
    
    case START:

       Serial.print("entro START");
       
       mystate = ESPERA_COMANDO_HOME; 
    
    break;

    case ESPERA_COMANDO_HOME: //LEEMOS UN BYTE 'H' PARA HACER HOME    //LISTEN TO LABVIEW
    
    Serial.print("entro ESPERA_COMANDO_HOME ");

   
       mystate = HACER_HOME;

     
    
    break;
    
    case HACER_HOME: //codigo para hacer home

    Serial.print("entro HACER_HOME ");
      
      mystate = MOVER_POSICION_INICIO;
    
    break;

    case MOVER_POSICION_INICIO: //esperar para recibir la orden de posicion de inicio codigo para ir a posicion de inicio //LISTEN TO LABVIEW
       Serial.print("MOVER_POSICION_INICIO ");
       mystate = HACER_HOME;

       
    

    break;

    case  RECIBIR_DATOS_MOVIMIENTO: // leer datos de labview y decidir que eje mover    //LISTEN TO LABVIEW   //puede irse a mover x , mover y , mover z ó a terminar movimiento
    
    

    break;

    case  MOVER_X: // codigo para mover motores cierto numero de pasos 

      mystate = RECIBIR_DATOS_MOVIMIENTO;
    
    break;

    case  MOVER_Y: // codigo para mover motores cierto numero de pasos

      mystate = RECIBIR_DATOS_MOVIMIENTO;
    
    break;

    case  MOVER_Z: // codigo para mover motores cierto numero de pasos

      mystate = RECIBIR_DATOS_MOVIMIENTO;
    
    break;

    case  TERMINAR_MOVIMIENTO: //codigo que vuelve a start y hacer home

      mystate = START;
    
    break;

}

}
