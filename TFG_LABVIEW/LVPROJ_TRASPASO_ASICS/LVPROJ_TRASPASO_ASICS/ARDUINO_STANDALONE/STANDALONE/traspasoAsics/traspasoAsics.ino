#include <Servo.h>
#include <Math.h>

#define Led 13
#define dir_y 29
#define pul_y 31
#define ena_y 33
#define dir_x 23
#define pul_x 25
#define ena_x 27
#define dir_z 35
#define pul_z 37
#define ena_z 39

#define bomba 7
#define pin_servo 8

#define sensor_x 21
#define sensor_y 20
#define sensor_z 19

Servo myservo;

const unsigned long pulsos_rev = 6400; //Numero de pulsos por revolucion del motor eje z
unsigned long pulsos_z_coger_bandeja = 104320;//(pulsos_rev/200)*3260; //Estaba en *3500 //El eje Z se mueve 1 mm por cada 3200 pulsos ya que,
unsigned long pulsos_z_soltar_bandeja = 95000;//(pulsos_rev/200)*3000;//con el microstepping de 6400 pulsos por revolucion de motor, el husillo roscado
unsigned long pulsos_z_coger_socket = (pulsos_rev/200)*2450;  //que avanza 2mm por revolucion segun espec. necesita 3200 pulsos para desplazarse 1mm.
unsigned long pulsos_z_soltar_socket = (pulsos_rev/200)*2150;

int const size=5;
/*int*/int arrayData[size];
char const StartMovement = 'S';
int fin;
//#define HOME

int coordenadaX_origen; //datos de partida
int coordenadaY_origen;
int coordenadaX_destino;
int coordenadaY_destino;
int numAsics_amover;



long PASOS_X_A_PRIMERA_ORIGEN=32661;// 43151 NOK 18320 IN 30780 ok
long PASOS_Y_A_PRIMERA_ORIGEN=39199; //34364 ok 34476 nok 34364 IN
long PASOS_X_A_PRIMERA_DESTINO=20227; //30780 ok 43151 nok 18320 IN
long PASOS_Y_A_PRIMERA_DESTINO=39199;//34364 ok 34476 nok 34364 IN

long PASOS_COORD_BANDEJAORIGEN_X;
long PASOS_COORD_BANDEJAORIGEN_Y;

long PASOS_COORD_BANDEJADESTINO_X;
long PASOS_COORD_BANDEJADESTINO_Y;

long PASOS_TRASLADO_X;
long PASOS_TRASLADO_Y;

long PASOS_VUELTA_X;
long PASOS_VUELTA_Y;

long pasoCeldaX = 1169;
long pasoCeldaY = 1078;



int coord_siguiente_ORIGEN_X;
int coord_siguiente_ORIGEN_Y;
int coord_siguiente_DESTINO_X;
int coord_siguiente_DESTINO_Y;


int correcion=1;
int espera =100;

int sentido_TrasladoX;
int sentido_VueltaX;

int sentido_TrasladoY ;
int sentido_VueltaY ;



void movimiento(int salida, long pulsos, long tiempo) 
{
  long t;
  //EL MOVIMIENTO EN LOS EJES SE EJECUTA A TRAVÉS DE UN BUCLE FOR QUE REALIZA UNA ITERACIÓN POR CADA PULSO(PASO)
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
void movimientoCorto(int salida, long pulsos) 
{
  
  //EL MOVIMIENTO EN LOS EJES SE EJECUTA A TRAVÉS DE UN BUCLE FOR QUE REALIZA UNA ITERACIÓN POR CADA PULSO(PASO)
  for (long i=0;i<(pulsos);i++)
  {

                                         //ESTOS "if" anidados es un algoritmo de aceleración/deceleración de la velocidad de rotacion de los motores
                                         //al inicio y final de cada movimiento para evitar movimientos bruscos cuando sale del socket (HOME) y cuando llega a la bandeja                                         
                                         //va modificando el tiempo entre pulsos para aumentar o reducir la velocidad.
    //Ejecución de los pulsos (señal cuadrada).El tiempo en alto y bajo "t" es determinado previamente con un dato que lee desde labview (POR qué no es una constante?)
    if (i<pulsos){
    digitalWrite(salida,HIGH); //Salida a nivel alto
    delayMicroseconds(400);      //espera
    digitalWrite(salida,LOW);  //Salida a nivel bajo
    delayMicroseconds(400);      //espera
  }
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
      delayMicroseconds(90);//400
      digitalWrite(pul_y,LOW);
      delayMicroseconds(90);
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
      delayMicroseconds(90);//400
      digitalWrite(pul_x,LOW);
      delayMicroseconds(90);
    }
    
    digitalWrite(ena_x,HIGH);
    delay(1000);
    digitalWrite(ena_x,LOW);
    delay(1000);
    digitalWrite(ena_x,HIGH);
    delay(100);

  


}
void setup() {
  Serial.begin(9600);
 
  myservo.attach(pin_servo);
  pinMode(sensor_x,INPUT);
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
  digitalWrite(bomba,LOW);
  //Serial.setTimeout(50);
  // put your setup code here, to run once:
}

void loop() {


String coordenada="";

while (!Serial.available()){} //ESPERO PARAMETROS DE ENTRADA DESDE LABVIEW
delay(100);
int ind=0;
//coordenada x, coordenada y entrada, + coordenada x , coordenada y salida, modo, 
while (Serial.available()>0){

  char caracter = Serial.read(); //lee un byte 
  Serial.print(caracter);
  
  if(caracter == '\n'){ 
  arrayData[ind]= coordenada.toInt(); //convertimos a int el valor acumulado como string en "coordenada" y lo guardamos en el array
  coordenada ="";  //limpiamos el string para la siguiente entrada porque sino se va acumulando todo junto en el "else"
  
  ind++;
}
  else{ //si no llega el separador de dato \n concatenamos el caracter
    
    coordenada += caracter;
  }
  coordenadaX_origen=arrayData[0]; //almacenamos los parámetros iniciales enviados desde labview en las variables a utilizar
  coordenadaY_origen=arrayData[1];
  coordenadaX_destino=arrayData[2];
  coordenadaY_destino=arrayData[3];
  numAsics_amover= arrayData[4];
}





while (!Serial.available()){} //ESPERO COMANDO "S" DE LABVIEW PARA COMENZAR MOVIMIENTO
while (Serial.read()!=StartMovement){

//Serial.print(numAsics_amover);
} 
Serial.print("COMIENZO MOVIMIENTO"); //MANDAMOS MENSAJE A LABVIEW COMO RESPUESTA DE QUE HA RECIBIDO EL COMANDO "S"

//////////////////////////////////////////REFERENCIA A ORIGEN HOME////////////////////////////////////////////
  
  //Desplazamiento a la posición de referencia (origen HOME) utilizando los sensores fin de carrera.
  //Sólo se hace ésta referencia a origen, como se puede ver, cuando la variable "fin" vale cero, es decir que sólo se
  //referencia al principio del test cuando va a coger el primer asic de la bandeja de entrad
  

Home();
//////////////////////////////////////////FIN DE REFERENCIA A ORIGEN HOME/////////////////////////////////////

 
coord_siguiente_ORIGEN_Y=coordenadaY_origen;  //PUNTO DE PARTIDA PARA LA COORDENADA_SIGUIENTE
coord_siguiente_DESTINO_Y=coordenadaY_destino;

if (PASOS_X_A_PRIMERA_ORIGEN<PASOS_X_A_PRIMERA_DESTINO) //MOVIMIENTO DE TRASLADO DE IZQ A DERECH , BANDEJA ORIGEN A LA IZQ
{
  sentido_TrasladoX=1;
  sentido_VueltaX=0;
}
if (PASOS_X_A_PRIMERA_ORIGEN>PASOS_X_A_PRIMERA_DESTINO) //MOVIMIENTO DE TRASLADO DE DERECH A IZQ , BANDEJA ORIGEN A LA DERECH
{
  sentido_TrasladoX=0;
  sentido_VueltaX=1;
}
////////////////////////////////////////////////////////////////////////////COMIENZA BUCLE DE TRASPASO DE CHIPS//////////////////////////////////////////////////////////////////

for (int numTraslados=0; numTraslados<numAsics_amover; numTraslados++){

  coord_siguiente_ORIGEN_X= coordenadaX_origen + 1;
  coord_siguiente_DESTINO_X= coordenadaX_destino + 1;

  if(coordenadaY_origen==coordenadaY_destino){

      if (coordenadaX_destino > coordenadaX_origen ){
        sentido_TrasladoY = 0;
        sentido_VueltaY =1;
      }
      if (coordenadaX_destino < coordenadaX_origen ){
        sentido_TrasladoY = 1;
        sentido_VueltaY =0;
      }
      if (coordenadaX_destino == coordenadaX_origen ){
        sentido_VueltaY=0;
      }

  }

  else if (coordenadaY_destino > coordenadaY_origen){

        sentido_TrasladoY = 0;
        sentido_VueltaY =1;
}

  else if (coordenadaY_destino < coordenadaY_origen){
         
        sentido_TrasladoY = 1;
        sentido_VueltaY =0;
  }


  

  if(coordenadaX_origen==9){

    coord_siguiente_ORIGEN_X=0;
    coord_siguiente_ORIGEN_Y=coord_siguiente_ORIGEN_Y + 1;

  }

  if(coordenadaX_destino==9){

    coord_siguiente_DESTINO_X=0;
    coord_siguiente_DESTINO_Y=coord_siguiente_DESTINO_Y + 1;

  }



//calculo de pasos a coordenada bandeja de origen respecto de la posicion HOME
PASOS_COORD_BANDEJAORIGEN_X = (PASOS_X_A_PRIMERA_ORIGEN +pasoCeldaX*coordenadaX_origen);
//coordenadaX_origen*1166*cos((3.14159/180)*(0.496)) + coordenadaY_origen*1077*sin(3.14159/180*(0.289));

PASOS_COORD_BANDEJAORIGEN_Y = ((PASOS_Y_A_PRIMERA_ORIGEN) -(pasoCeldaY*coordenadaY_origen));
//coordenadaX_origen*1166*sin((3.14159/180)*(0.496)) - coordenadaY_origen*1077*cos(3.14159/180*(0.289));


//calculos de pasos a coordenada bandeja destino respecto de la posicion HOME
PASOS_COORD_BANDEJADESTINO_X = ((PASOS_X_A_PRIMERA_DESTINO)+(pasoCeldaX*coordenadaX_destino));
//coordenadaX_destino*1166*cos((3.14159/180)*(0.496)) + coordenadaY_destino*1077*sin(3.14159/180*(0.289));

PASOS_COORD_BANDEJADESTINO_Y = ((PASOS_Y_A_PRIMERA_DESTINO)-(pasoCeldaY*coordenadaY_destino));
//coordenadaX_destino*1166*cos((3.14159/180)*(0.496)) - coordenadaY_destino*1077*sin(3.14159/180*(0.289));


//calculo de pasos movimiento de traslado,y el sentido es en funcion del sentido del traslado, izquierda a derecha ó derecha a izquierda
PASOS_TRASLADO_X= abs(PASOS_COORD_BANDEJADESTINO_X - PASOS_COORD_BANDEJAORIGEN_X); //SERÁ VALOR POSITIVO SI EL TRASLADO ES DE IZQ A DERECH //SERÁ NEGATIVO EN CASO CONTRARIO

PASOS_TRASLADO_Y= abs(PASOS_COORD_BANDEJADESTINO_Y - PASOS_COORD_BANDEJAORIGEN_Y); //SERÁ VALOR POSITIVO SI LA COORDENADA "Y" DESTINO ES MAYOR QUE LA DE ORIGEN. SERÁ NEGATIVO EN CASO CONTRARIO

//calculo de pasos vuelta para coger siguiente Asic
if (PASOS_X_A_PRIMERA_ORIGEN < PASOS_X_A_PRIMERA_DESTINO) //MOVIMIENTO DE TRASLADO DE IZQ A DERECH , BANDEJA ORIGEN A LA IZQ
{
 PASOS_VUELTA_X = abs((PASOS_TRASLADO_X)-(pasoCeldaX*(coord_siguiente_ORIGEN_X - coordenadaX_origen)));
}
if (PASOS_X_A_PRIMERA_ORIGEN > PASOS_X_A_PRIMERA_DESTINO) //MOVIMIENTO DE TRASLADO DE IZQ A DERECH , BANDEJA ORIGEN A LA IZQ
{
 PASOS_VUELTA_X = abs((PASOS_TRASLADO_X)+(pasoCeldaX*(coord_siguiente_ORIGEN_X - coordenadaX_origen)));
}
if ((coordenadaY_origen > coordenadaY_destino) && (coordenadaX_origen==coordenadaX_destino) && (coordenadaX_origen==9)){
PASOS_VUELTA_Y = abs((PASOS_TRASLADO_Y)+(pasoCeldaY*(coord_siguiente_ORIGEN_Y - coordenadaY_origen)));
}
else{
  PASOS_VUELTA_Y = abs((PASOS_TRASLADO_Y)-(pasoCeldaY*(coord_siguiente_ORIGEN_Y - coordenadaY_origen)));
}
/*EL SENTIDO POSITIVO (HACIA LA DERECHA) O NEGATIVO (HACIA LA IZQUIERDA) DEL MOTOR EN X DEPENDERÁ DEL SENTIDO DEL MOVIMIENTO DEL TRASLADO:

TRASLADO ES DE IZQUIERDA A DERECHA LOS PASOS DE TRASLADO EN X SERÁN CON EL MOTOR EN SENTIDO POSITIVO, Y EN LOS PASOS DE VUELTA SERÁ NEGATIVO SIEMPRE.
EN ESTE TRASLADO (IZQ A DERECH) EL SENTIDO DE MOVIMIENTO DE Y SERÁ: NEGATIVO (HACIA ABAJO) SI LA COORDENADA Y DE ORIGEN ES DE MENOR VALOR QUE LA DE DESTINO.SERÁ POSITIVO (HACIA ARRIBA) SI ES AL REVÉS. LA VUELTA EN Y SERÁ AL CONTRARIO.
EL PROGRAMA TIENE QUE TENER EN CUENTA EN QUÉ SENTIDO ES EL TRASLADO, Y LA RELACIÓN ENTRE LAS COORDENADAS DE PARTIDA.


*/


    digitalWrite(pul_x,LOW);
    delay(100);
    digitalWrite(pul_y,LOW);
    delay(100);
    digitalWrite(Led,HIGH);
    delay(100);

    digitalWrite(ena_x,LOW);
    delay(100);
    digitalWrite(ena_y,LOW);
    delay(100);
    digitalWrite(ena_z,LOW);
    delay(1000);
    
    //Desplazamiento en x:
//    digitalWrite(ena_x,LOW);
//    delay(1000);

//Desplazamiento a bandeja origen:
    if (numTraslados==0){
    digitalWrite(dir_x,HIGH);
    delay(100);
    movimiento(pul_x,PASOS_COORD_BANDEJAORIGEN_X,espera-50);
    delay(100);
    
    //Desplazamiento en y:
//    digitalWrite(ena_y,LOW);
//    delay(1000);
    digitalWrite(dir_y,HIGH);
    delay(100);
    movimiento(pul_y,PASOS_COORD_BANDEJAORIGEN_Y,espera-50);
    delay(100); 

    digitalWrite(dir_z,LOW); //activa el motor direccion hacia abajo
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10); //envia pulsos al motor para bajar hasta el asic
    delay(100);
    //delay(100);
    digitalWrite(bomba,HIGH); //activa la bomba //COGE ASIC
    delay(2500); //espera 1 segundo con la ventosa en el asic mientras hace el vacio.
    digitalWrite(dir_z,HIGH); //activa el motor para la direccion hacia arriba
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10); 
    delay(100);
    }
    

    delay(200);

    if(numTraslados>0){
    digitalWrite(dir_z,LOW); //activa el motor direccion hacia abajo
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10); //envia pulsos al motor para bajar hasta el asic
    delay(100);
    //delay(100);
    digitalWrite(bomba,HIGH); //activa la bomba //COGE ASIC
    delay(2500); //espera 1 segundo con la ventosa en el asic mientras hace el vacio.
    digitalWrite(dir_z,HIGH); //activa el motor para la direccion hacia arriba
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10); 
    delay(100);

      
    }

    digitalWrite(dir_x,sentido_TrasladoX);
    delay(100);
    movimiento(pul_x,PASOS_TRASLADO_X,espera-50);
    delay(100);
    
    //Desplazamiento en y:
//    digitalWrite(ena_y,LOW);
//    delay(1000);
    digitalWrite(dir_y,sentido_TrasladoY);
    delay(100);
    movimientoCorto(pul_y,PASOS_TRASLADO_Y);//movimiento(pul_y,PASOS_TRASLADO_Y,espera-50);
    delay(100);

    digitalWrite(dir_z,LOW); //activa el motor direccion hacia abajo
    delay(100);
    movimiento(pul_z,pulsos_z_soltar_bandeja,10); //envia pulsos al motor para bajar hasta el asic
    delay(100);
    //delay(100);
    digitalWrite(bomba,LOW); //desactiva la bomba SUELTA ASIC
    delay(1000); //espera 1 segundo con la ventosa en el asic mientras hace el vacio.
    digitalWrite(dir_z,HIGH); //activa el motor para la direccion hacia arriba
    delay(100);
    movimiento(pul_z,pulsos_z_soltar_bandeja,10); //envia pulsos para subir e irse al socket
    delay(100); 

    delay(200);

    digitalWrite(dir_x,sentido_VueltaX);
    delay(100);
    movimiento(pul_x,PASOS_VUELTA_X,espera-50);
    delay(100);

    delay(200);
    
    digitalWrite(dir_y,sentido_VueltaY);
    delay(100);
    movimientoCorto(pul_y,PASOS_VUELTA_Y);//movimiento(pul_y,PASOS_VUELTA_Y,espera-50);
    delay(100);

   /* digitalWrite(dir_z,LOW); //activa el motor direccion hacia abajo
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10); //envia pulsos al motor para bajar hasta el asic
    delay(100);
    //delay(100);
    digitalWrite(bomba,HIGH); //activa la bomba 
    delay(1000); //espera 1 segundo con la ventosa en el asic mientras hace el vacio.
    digitalWrite(dir_z,HIGH); //activa el motor para la direccion hacia arriba
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10); //envia pulsos para subir e irse al socket
    delay(100); */

    //delay(200);
    
    
    coordenadaX_origen++;
    coordenadaX_destino++;

if (coordenadaX_origen==10)  //DETECCION DE FINAL DE FILA E INCREMENTO EN COORDENADA Y.EL VALOR 10 ES PORQUE SE SUPONEN BANDEJAS CON 10 COLUMNAS
  {
    coordenadaX_origen = 0; //SE COLOCA DE NUEVO EN LA COLUMNA 0
    //Serial.println("entro");

    coordenadaY_origen = coordenadaY_origen+1; //PASA A LA SIGUIENTE FILA DE LA BANDEJA
   
  }

if (coordenadaX_destino==10)  //DETECCION DE FINAL DE FILA E INCREMENTO EN COORDENADA Y.EL VALOR 10 ES PORQUE SE SUPONEN BANDEJAS CON 10 COLUMNAS
  {
    coordenadaX_destino = 0; //SE COLOCA DE NUEVO EN LA COLUMNA 0
    //Serial.println("entro");

    coordenadaY_destino = coordenadaY_destino+1; //PASA A LA SIGUIENTE FILA DE LA BANDEJA
   
  }


  // put your main code here, to run repeatedly:
}

////////////////////////////////////////////////////////////////////////////TERMINA BUCLE DE TRASPASO DE CHIPS//////////////////////////////////////////////////////////////////

Home(); //vuelve a posicion inicio Home desde la bandeja

}
/*
// Definir pines
#define STEP_PIN 2  // Pin de pasos
#define DIR_PIN 3   // Pin de dirección

// Configuración de aceleración
#define MAX_SPEED 500     // Velocidad máxima (menor valor = más rápido)
#define MIN_SPEED 3000    // Velocidad mínima (mayor valor = más lento)
#define ACCELERATION 10   // Factor de aceleración (ajustar según necesidad)
#define STEPS 1000        // Número de pasos a mover

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Iniciando movimiento...");
}

void loop() {
  // Mueve el motor hacia adelante
  Serial.println("Moviendo adelante...");
  moverMotor(STEPS, HIGH);
  
  delay(2000); // Espera 2 segundos
  
  // Mueve el motor hacia atrás
  Serial.println("Moviendo atrás...");
  moverMotor(STEPS, LOW);
  
  delay(2000); // Espera 2 segundos
}

// Función para mover el motor con aceleración y deceleración manual
void moverMotor(int pasos, bool direccion) {
  digitalWrite(DIR_PIN, direccion); // Establece la dirección del motor

  int speed = MIN_SPEED;  // Inicialmente, velocidad mínima (movimiento lento)
  
  for (int i = 0; i < pasos; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(speed);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(speed);
    
    // Aceleración: Disminuye el delay (incrementa la velocidad)
    if (i < pasos / 2 && speed > MAX_SPEED) {
      speed -= ACCELERATION;
    }
    
    // Desaceleración: Aumenta el delay (reduce la velocidad)
    else if (i >= pasos / 2 && speed < MIN_SPEED) {
      speed += ACCELERATION;
    }
  }
  
  Serial.println("Movimiento completado.");
} */
