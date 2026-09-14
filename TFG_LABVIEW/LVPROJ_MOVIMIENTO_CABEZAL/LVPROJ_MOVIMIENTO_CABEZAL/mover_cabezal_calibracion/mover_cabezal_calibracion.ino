/* Teoricamente en X e Y:
1mm= 91 pasos
1cm = 910 pasos
10 cm = 9100 pasos
0.1 mm = 9 pasos aprox
*/

//El eje Z se mueve 1 mm por cada 3200 pulsos. Desde la ventosa hasta el tablero metalico hay aprox. 45mm (144000 pulsos teoricamente, NO PONER NUNCA ÉSTE VALOR )




#define dir_y 29
#define pul_y 31
#define ena_y 33
#define dir_x 23
#define pul_x 25
#define ena_x 27
#define dir_z 35
#define pul_z 37
#define ena_z 39


#define sensor_x 21
#define sensor_y 20
#define sensor_z 19


const long pulsos_rev = 6400; //Numero de pulsos por revolucion del motor





int const size=10;
long arrayData[size];
//int ind=0;

long PASOS_X;
long PASOS_Y;
long PASOS_Z;

//boolean reinicio=true;



/*String *ArrayDatos (){

const int size = 10;//10 datos de tamaño dinámico cada uno
//long int arrayData[size];
static String arrayData[size]; //cada posicion del array pueden ser datos de cualquier numero de bytes, en funcion de lo que le venga. String es dinámico hasta el limite de la RAM. 
                               //necesita ser static porque sino se destruye el array construido despues de salir de la funcion.
                               //cuando se llame otra vez a la funcion sobreescribirá los datos que haya .
String dato="";
while (!Serial.available()){} //ESPERO PARAMETROS DE ENTRADA DESDE LABVIEW,SALE DEL BUCLE SI HAY DATOS
//delay(100);
int ind=0;
//coordenada x, coordenada y entrada, + coordenada x , coordenada y salida, modo, 
unsigned long int tiempoDatoIn = millis();

while (millis()- tiempoDatoIn< 10){ //TIMEOUT PARA RECIBIR DATO DE 10 ms
  
  while (Serial.available()>0){

  char caracter = Serial.read(); //lee un byte 
  dato += caracter;
  tiempoDatoIn=millis();
  //Serial.print(caracter);
  
  if(caracter == '\n'){ 
  arrayData[ind]= dato; //convertimos a long int el valor acumulado como string en "coordenada" y lo guardamos en el array
  dato ="";  //limpiamos el string para la siguiente entrada porque sino se va acumulando todo junto en el "else"
  
  ind++;
}
}
}
return arrayData;
}*/


void movimiento(int salida, long pulsos, long tiempo) 
{
  long t;
  
//EL MOVIMIENTO EN LOS EJES SE EJECUTA A TRAVÉS DE UN BUCLE FOR QUE REALIZA UNA ITERACIÓN POR CADA PULSO(PASO)
//  }

  for (long i=0;i<(pulsos);i++)
  {

                                         //ESTOS "if" anidados es un algoritmo de aceleración/deceleración de la velocidad de rotacion de los motores
                                         //al inicio y final de cada movimiento para evitar movimientos bruscos cuando sale del socket (HOME) y cuando llega a la bandeja                                         
                                         //va modificando el tiempo entre pulsos para aumentar o reducir la velocidad.
    

    if((i<pulsos/64)or(i>63*pulsos/64))  {
      t=tiempo*6;
    }
    else if((i<2*pulsos/64)or(i>62*pulsos/64))
    {
      t=tiempo*3;
    }
    else if((i<3*pulsos/64)or(i>61*pulsos/64))
    {
      t=tiempo*2;
    }
    else if((i<4*pulsos/64)or(i>60*pulsos/64))
    {
      t=tiempo*1.5;
    }
    else if((i<5*pulsos/64)or(i>59*pulsos/64))
    {
      t=tiempo*1.2;
    }
    else if((i<6*pulsos/64)or(i>58*pulsos/64))
    {
      t=tiempo*1.1;
    }
    else
    {
      t=tiempo;
    }
    //Ejecución de los pulsos (señal cuadrada).El tiempo en alto y bajo "t" es determinado previamente con un dato que lee desde labview (POR qué no es una constante?)
    
    digitalWrite(salida,HIGH); //Salida a nivel alto
    delayMicroseconds(t);      //espera
    digitalWrite(salida,LOW);  //Salida a nivel bajo
    delayMicroseconds(t);      //espera
  }
}

void mover1000pasosY(){
for (int i=0 ; i<1000 ; i++){
    digitalWrite(pul_y,HIGH); //Salida a nivel alto
    delayMicroseconds(3000);      //espera
    digitalWrite(pul_y,LOW);  //Salida a nivel bajo
    delayMicroseconds(3000);  
}   
}

void mover1000pasosX(){
for (int i=0 ; i<50 ; i++){
    digitalWrite(pul_x,HIGH); //Salida a nivel alto
    delayMicroseconds(800);      //espera
    digitalWrite(pul_x,LOW);  //Salida a nivel bajo
    delayMicroseconds(800);     

}
}

void Home(){
  
              

    digitalWrite(pul_x,LOW);
    delay(100);
    digitalWrite(pul_y,LOW);
    delay(100);
    digitalWrite(pul_z,LOW);
    
    
    digitalWrite(ena_z,LOW);
    delay(1000);
    digitalWrite(dir_z,HIGH);
    delay(100);

    while(digitalRead(sensor_z)==LOW)
    {
      digitalWrite(pul_z,HIGH);
      delayMicroseconds(10); //90
      digitalWrite(pul_z,LOW);
      delayMicroseconds(10); //90
    }
    digitalWrite(ena_z,HIGH);
    delay(1000);
    digitalWrite(ena_z,LOW);
    delay(1000);
    digitalWrite(ena_z,HIGH);
    delay(100);
    
    
    digitalWrite(ena_y,LOW);
    delay(1000);
    digitalWrite(dir_y,LOW);
    delay(100);

    while(digitalRead(sensor_y)==LOW)
    {
      digitalWrite(pul_y,HIGH);
      delayMicroseconds(800);//400
      digitalWrite(pul_y,LOW);
      delayMicroseconds(800);
    }

    digitalWrite(ena_y,HIGH);
    delay(1000);
    digitalWrite(ena_y,LOW);
    delay(1000);
    digitalWrite(ena_y,HIGH);
    delay(100);
    
    
    digitalWrite(ena_x,LOW);
    delay(1000);
    digitalWrite(dir_x,LOW);
    delay(100);

    while(digitalRead(sensor_x)==LOW)
    {
      digitalWrite(pul_x,HIGH);
      delayMicroseconds(800);//400
      digitalWrite(pul_x,LOW);
      delayMicroseconds(800);
    }
    
    digitalWrite(ena_x,HIGH);
    delay(1000);
    digitalWrite(ena_x,LOW);
    delay(1000);
    digitalWrite(ena_x,HIGH);
    delay(100);

  


}

void enableMotorX() {
  digitalWrite(pul_x,LOW);
  delay(100);
  digitalWrite(ena_x,LOW);
  delay(100);

}

void enableMotorY() {
  digitalWrite(pul_y,LOW);
  delay(100);
  digitalWrite(ena_y,LOW);
  delay(100);

}

void enableMotorZ() {
  digitalWrite(pul_z,LOW);
  delay(100);
  digitalWrite(ena_z,LOW);
  delay(100);

}

void recibirDatos(){
  while (!Serial.available()){} //ESPERO COORDENADAS EN PASOS DESDE LABVIEW
    delay(100); //espero a que todos los datos me lleguen porque a veces arduino vacía el buffer antes de que labview le termine de enviar los datos
    int ind=0; //si ind la declaro local aquí como int ind = 0 , tengo que poner llaves en éste case, porque sino el switch no funciona (el compilador hace cosas raras).
           //así que declaro ind como global.
    String coordenada="";

    while (Serial.available()>0){//empiezo a leer datos asegurandome que ya están todos 
    
    char caracter = Serial.read(); //lee un byte 
   // Serial.print(caracter);
  
    if(caracter == '\n'){  //cada coordenada en X, Y o Z van separadas por \n
    arrayData[ind]= coordenada.toInt(); //convertimos a int el valor acumulado como string en "coordenada" y lo guardamos en el array
    coordenada ="";  //limpiamos el string para la siguiente entrada del dato porque sino se va acumulando todo junto en el "else"
  
    ind++;
     }
    else{
    
    coordenada += caracter; //acumulamos en el String coordenada la sucesión de bytes que envia labview hasta que se encuentra un /n de separacion de dato
   }
   
    }
}




 




void setup() { //Ésta funcion se ejecuta en cada reinicio del micro sólo una vez
 
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
  //pinMode(bomba,OUTPUT);
  digitalWrite(ena_x,HIGH);
  digitalWrite(ena_y,HIGH);
  digitalWrite(ena_z,HIGH);
  Home();
  digitalWrite(ena_x,HIGH);
  digitalWrite(ena_y,HIGH);
  digitalWrite(ena_z,HIGH);
  enableMotorX();

  
  

}

void loop() {
  delay(2000);
  enableMotorX();
  digitalWrite(dir_x,HIGH);
  delay(100);
  mover1000pasosX();
  
  Home();
  delay(1000);



}