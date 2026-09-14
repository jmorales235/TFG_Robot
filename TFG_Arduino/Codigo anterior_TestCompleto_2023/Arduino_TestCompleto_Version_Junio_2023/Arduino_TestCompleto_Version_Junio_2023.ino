#include <Servo.h>

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

const double  cos_a = 0.999; 
const double  sen_a = 0.00645;
const double  sen_b = 0.0056;
const double  cos_b = 0.999;


Servo myservo;

char fallo_QR;

const long pulsos_rev = 6400; //Numero de pulsos por revolucion del motor

//const byte interrup = 18; //Pin de lectura del sensor. Congela el programa (hay que reiniciar) cuando cambia de estado.

//const long pasos_fincarrera = 4000*(pulsos_rev/200);

char lectura1,lectura2;
long distancia_x;
long distancia_y;
long coord1,coord2;

long entrada_x,entrada_y;
long entrada_x_primera;
long salidaOK_x,salidaOK_y;
long salidaNOK_x,salidaNOK_y;

char lectura_periodo;
int periodo;

long espera;
long pulsos_entrada_x,pulsos_entrada_y;
long pulsos_entrada_x_add;
long pulsos_salidaOK_x,pulsos_salidaOK_y;
long pulsos_salidaNOK_x,pulsos_salidaNOK_y;
long entrada_socket_x,entrada_socket_y;
long socket_salidaOK_x,socket_salidaOK_y;
long socket_salidaNOK_x,socket_salidaNOK_y;

//long pulsos_z_coger_bandeja = (pulsos_rev/200)*3750; //Estaba en *3500
//long pulsos_z_soltar_bandeja = (pulsos_rev/200)*3550;
//Ajustamo spara tener dos bandejas apiladas, Julio 24
long pulsos_z_coger_bandeja = (pulsos_rev/200)*3260; //Estaba en *3500 //El eje Z se mueve 1 mm por cada 3200 pulsos ya que,
long pulsos_z_soltar_bandeja = (pulsos_rev/200)*3000;//con el microstepping de 6400 pulsos por revolucion de motor, el husillo roscado
long pulsos_z_coger_socket = (pulsos_rev/200)*2450;  //que avanza 2mm por revolucion segun espec. necesita 3200 pulsos para desplazarse 1mm.
long pulsos_z_soltar_socket = (pulsos_rev/200)*2150;

char enable;
char resultado;

int fin=0;
int trigger=0;

void parpadeo(int salida)
{
  digitalWrite(salida,HIGH);
  delay(1000);
  digitalWrite(salida,LOW);
  delay(1000);
  digitalWrite(salida,HIGH);
  delay(300);
  digitalWrite(salida,LOW);
  delay(300);
  digitalWrite(salida,HIGH);
  delay(300);
  digitalWrite(salida,LOW);
  delay(300);
  digitalWrite(salida,HIGH);
  delay(1000);
  digitalWrite(salida,LOW);
  delay(1000);
}

void direccion(int salida, int dist) //Función para controlar la dirección en función de la nueva coordenada
{
  if (dist>0)
  {
    digitalWrite(salida,HIGH);
  }
  else
  {
    digitalWrite(salida,LOW);
  }
}

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

//  for (long i=0;i<(its);i++)
//  {
//    t = ((i/its)*tiempo*29)+tiempo;
//    digitalWrite(salida,HIGH);
//    delayMicroseconds(t);
//    digitalWrite(salida,LOW);
//    delayMicroseconds(t);
//  }
}

void setup()
{
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
  //attachInterrupt(digitalPinToInterrupt(interrup),stop,CHANGE); //Congela el programa cuando hay un cambio en la señal del sensor
}

//void stop()
//{
//  digitalWrite(ena_x,HIGH);
//  digitalWrite(ena_y,HIGH);
//  digitalWrite(ena_z,HIGH);
//  digitalWrite(bomba,LOW);
//  while(1==1)
//  {
//  }
//}

void loop()
{
  //Serial.print(fin);

  

  myservo.write(0); //el motor servo que acciona el socket lo libera, para asegurarnos por si acaso se hubiese quedado presionado

  //Lectura de la celda de la bandeja de entrada:
  
  while(Serial.available()==0){} //ESPERAMOS LOS DATOS DE ENTRADA DESDE LABVIEW REFERENTES A LA POSICIÓN X,Y INICIAL DE LA CELDA
                                 //EN LA BANDEJA DE ENTRADA DE ASIC
                                 //CADA COORDENADA UTILIZA DOS STRINGS EJ X=00,01,02... Y=00,01...
                                 //LECTURA 1 GUARDA LA PRIMERA CIFRA DE CADA STRING Y LECTURA 2 GUARDA LA SEGUNDA CIFRA
  lectura1 = Serial.read();
  while(Serial.available()==0){}
  lectura2 = Serial.read();

  //////////////////////////////////////////REFERENCIA A ORIGEN HOME////////////////////////////////////////////
  
  //Desplazamiento a la posición de referencia (origen HOME) utilizando los sensores fin de carrera.
  //Sólo se hace ésta referencia a origen, como se puede ver, cuando la variable "fin" vale cero, es decir que sólo se
  //referencia al principio del test cuando va a coger el primer asic de la bandeja de entrada.
  if (fin==0) 
              
  {
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
      delayMicroseconds(90);
      digitalWrite(pul_z,LOW);
      delayMicroseconds(90);
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
      delayMicroseconds(400);
      digitalWrite(pul_y,LOW);
      delayMicroseconds(400);
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
      delayMicroseconds(400);
      digitalWrite(pul_x,LOW);
      delayMicroseconds(400);
    }
    
    digitalWrite(ena_x,HIGH);
    delay(1000);
    digitalWrite(ena_x,LOW);
    delay(1000);
    digitalWrite(ena_x,HIGH);
    delay(100);

  }

  //////////////////////////////////////FIN REFERENCIA A ORIGEN///////////////////////////////////////

//AHORA COGEREMOS LAS COORDENADAS DE BANDEJA OK/NOK ENVIADAS EN FORMATO STRING POR LABVIEW AL INICIO DEL TEST.
//SABEMOS QUE LABVIEW NOS MANDA LAS 3 COORDENADAS DE BANDEJAS (ENTRADA,OK,NOK) DE FORMA CONSECUTIVA EN ESE ORDEN, Y EN ESE ORDEN SE QUEDAN EN EL BUFFER DEL PUERTO SERIAL.
//la variable "fin" sólo vale cero en la primera iteración del test ,es decir al comienzo del test del primer asic que queramos coger de la bandeja
  if (fin==0) 
  {
    //Conversión de los string leídos a int de la bandeja de entrada y la guardamos en la variable "entrada_x"---¿por qué no se hizo antes en la linea 206?
    coord1 = String(lectura1).toInt();
    coord2 = String(lectura2).toInt();
    entrada_x = coord1*10 + coord2; //no entiendo por qué se multiplica coord1 por 10
    entrada_x_primera = entrada_x;
  }
//ADQUIRIMOS DEL BUFFER SERIAL LA COORDENADA "Y" DE LA BANDEJA DE ENTRADA

  while(Serial.available()==0){} //Uso esto para esperar a que haya un dato disponible en el puerto serie.
  lectura1 = Serial.read();
  while(Serial.available()==0){}
  lectura2 = Serial.read();

//CONVERSIÓN DE LOS STRINGS ADQUIRIDOS DE LA COORDENADA Y A INT Y EL VALOR SE GUARDA EN  VARIABLE ENTRADA_Y
  if (fin==0)
  {
    coord1 = String(lectura1).toInt();
    coord2 = String(lectura2).toInt();
    entrada_y = coord1*10 + coord2;
  }

  ////////////////////////////LECTURA DE LAS COORDENADAS DE BANDEJA SALIDA OK//////////////////////////////////////////////

  while(Serial.available()==0){} //Uso esto para esperar a que haya un dato disponible en el puerto serie.
  lectura1 = Serial.read();
  while(Serial.available()==0){}
  lectura2 = Serial.read();

  if (fin==0)
  {
    //Conversión de los char leídos a int:
    coord1 = String(lectura1).toInt();
    coord2 = String(lectura2).toInt();
    salidaOK_x = coord1*10 + coord2;
  }

  while(Serial.available()==0){} //Uso esto para esperar a que haya un dato disponible en el puerto serie.
  lectura1 = Serial.read();
  while(Serial.available()==0){}
  lectura2 = Serial.read();

  if (fin==0)
  {
    coord1 = String(lectura1).toInt();
    coord2 = String(lectura2).toInt();
    salidaOK_y = coord1*10 + coord2;
  }
  
/////////////////////////////FIN DE LECTURA DE COORDENADAS DE BANDEJA SALIDA OK/////////////////////////////////////


////////////////////////////LECTURA DE LAS COORDENADAS DE BANDEJA SALIDA NOK//////////////////////////////////////////////
 
  while(Serial.available()==0){} //Uso esto para esperar a que haya un dato disponible en el puerto serie.
  lectura1 = Serial.read();
  while(Serial.available()==0){}
  lectura2 = Serial.read();

  if (fin==0)
  {
    //Conversión de los char leídos a int:
    coord1 = String(lectura1).toInt();
    coord2 = String(lectura2).toInt();
    salidaNOK_x = coord1*10 + coord2;
  }

  while(Serial.available()==0){}
  lectura1 = Serial.read();
  while(Serial.available()==0){}
  lectura2 = Serial.read();

  if (fin==0)
  {
    coord1 = String(lectura1).toInt();
    coord2 = String(lectura2).toInt();
    salidaNOK_y = coord1*10 + coord2;
  }
////////////////////////////////////FIN DE LECTURA DE COORDENADA DE BANDEJA DE SALIDA NOK///////////////////////////////////////////////
  
///LECTURA DE LA SEÑAL DE ENABLE QUE NOS ENVÍA LABVIEW. SI VALE "1" COMENZARÁ EL TEST 
  
  while(Serial.available()==0){}
  lectura_periodo = Serial.read();

  while(Serial.available()==0){}
  enable = Serial.read();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  //CHEQUEOS DE SI HA LLEGADO AL FINAL DE LA COLUMNA 10 (COORDENADA X) DE LAS BANDEJAS DE ASICS MODELO PEAK Ó ASE,PARA PASAR A LA FILA SIGUIENTE:

  if (entrada_x==10)  //EL VALOR 10 ES PORQUE SE SUPONEN BANDEJAS CON 10 COLUMNAS
  {
    entrada_x = 0; //SE COLOCA DE NUEVO EN LA COLUMNA 0
    entrada_y = entrada_y+1; //PASA A LA SIGUIENTE FILA DE LA BANDEJA
  }

  if (salidaOK_x==10)
  {
    salidaOK_x = 0; //SE COLOCA DE NUEVO EN LA COLUMNA 0
    salidaOK_y = salidaOK_y+1; //PASA A LA SIGUIENTE FILA DE LA BANDEJA
  }

  if (salidaNOK_x==10)
  {
    salidaNOK_x = 0; //SE COLOCA DE NUEVO EN LA COLUMNA 0
    salidaNOK_y = salidaNOK_y+1; //PASA A LA SIGUIENTE FILA DE LA BANDEJA
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************CÁLCULO DEL NUMERO DE PULSOS/PASOS ENTRE SOCKET Y CELDAS *********************************/

//Pulsos necesarios para el eje x e y de la bandeja de entrada:

// (550,725) aprox son coeficientes para la primera celda de la bandeja de entrada y hay 37 y 34 pulsos de separación entre cada una en los ejes X e Y, respectivamente EN LAS BANDEJAS ACTUALES!.
//Ésto es para una posición conocida de las bandejas marcada en el tablero. Si se mueven las bandejas, éstos coeficientes de calibración habría que cambiarlos.

  //pulsos_entrada_x = (571.7+entrada_x*36.41)*(pulsos_rev/200); //36.28 es para el paso entre celdas calculado para 70 mm por rev de motor.1161,14 pulsos
  //pulsos_entrada_x_add= (36.625)*(pulsos_rev/200);
  //pulsos_entrada_y = (1074.2-entrada_y*33.71)*(pulsos_rev/200); //Antes el paso era de 33.75// 1078,75
  //pulsos_entrada_y = (228.5-entrada_y*33.71)*(pulsos_rev/200); //Antes el paso era de 33.75// 1078,75


//(0,0)
  //pulsos_entrada_x=18294;
  //pulsos_entrada_y=34374;

//(0,25)
  //pulsos_entrada_x=18430;//18385;//18294;
  //pulsos_entrada_y=7448;//7403;//7312;

//(9,0)


  //pulsos_entrada_x=18294 + entrada_x*1166*cos_a + entrada_y*1077*sen_b;//28695;
  //pulsos_entrada_y=34374 - entrada_x*1166*sen_a - entrada_y*1077*cos_b;//34374;

  //OK para bandeja de entrada:
  //pulsos_entrada_x=18294 + entrada_x*1166*cos((3.14159/180)*(0.496-0.244*(entrada_y/25))) + entrada_y*1077*sin(3.14159/180*(0.289+0.08*(entrada_x/9)));
  //pulsos_entrada_y=34374 + entrada_x*1166*sin((3.14159/180)*(0.496-0.244*(entrada_y/25))) - entrada_y*1077*cos(3.14159/180*(0.289+0.08*(entrada_x/9)));

//(9,25)
  //pulsos_entrada_x=28960;//28695;
  //pulsos_entrada_y=7493;//34374;

//Prueba bandeja de salida:
//(0,0)
//pulsos_entrada_x=30700;
//pulsos_entrada_y=34400;
//(9,0)
//pulsos_entrada_x=30700 + entrada_x*1166*cos((3.14159/180)*(0.496-0.244*(entrada_y/25))) + entrada_y*1077*sin(3.14159/180*(0.289+0.08*(entrada_x/9)));
//pulsos_entrada_y=34400 + entrada_x*1166*sin((3.14159/180)*(0.496-0.244*(entrada_y/25))) - entrada_y*1077*cos(3.14159/180*(0.289+0.08*(entrada_x/9)));

pulsos_entrada_x=18320 + entrada_x*1166*cos((3.14159/180)*(0.496-0.244*(entrada_y/25))) + entrada_y*1077*sin(3.14159/180*(0.289+0.08*(entrada_x/9)));
pulsos_entrada_y=34364 + entrada_x*1166*sin((3.14159/180)*(0.496-0.244*(entrada_y/25))) - entrada_y*1077*cos(3.14159/180*(0.289+0.08*(entrada_x/9)));

//Pulsos necesarios para el eje x e y de la bandeja de salida OK:  

  pulsos_salidaOK_x = 30780 + salidaOK_x*1166*cos((3.14159/180)*(0.496-0.244*(entrada_y/25))) + salidaOK_y*1077*sin(3.14159/180*(0.289+0.08*(entrada_x/9))); //Pulsos desde el origen a la celda de salida de la bandeja OK (con bandejas juntas es 537)
  pulsos_salidaOK_y = 34400 + salidaOK_x*1166*sin((3.14159/180)*(0.496-0.244*(entrada_y/25))) - salidaOK_y*1077*cos(3.14159/180*(0.289+0.08*(entrada_x/9)));

//Pulsos necesarios para el eje x e y de la bandeja de salida NOK:

  pulsos_salidaNOK_x = 43151 + salidaNOK_x*1166*cos((3.14159/180)*(0.496-0.244*(entrada_y/25))) + salidaNOK_y*1077*sin(3.14159/180*(0.289+0.08*(entrada_x/9))); //Pulsos desde el origen a la celda de salida de la bandeja NOK (con bandejas juntas es 925)
  pulsos_salidaNOK_y = 34476 + salidaNOK_x*1166*sin((3.14159/180)*(0.496-0.244*(entrada_y/25))) - salidaNOK_y*1077*cos(3.14159/180*(0.289+0.08*(entrada_x/9)));

  entrada_socket_x = pulsos_entrada_x; //pulsos entre la posicion del Asic y el socket en el eje X (el socket está en el origen)
  entrada_socket_y = pulsos_entrada_y; //pulsos entre la posición del Asic y el socket en el eje Y.

  socket_salidaOK_x = pulsos_salidaOK_x; //pulsos entre el socket y la celda de la bandeja de salida OK
  socket_salidaOK_y = pulsos_salidaOK_y;

  socket_salidaNOK_x = pulsos_salidaNOK_x; //pulsos entre el socket y la celda de la bandeja de salida NOK
  socket_salidaNOK_y = pulsos_salidaNOK_y;

/************************************************************************************************************************************************************/  
  
  periodo = String(lectura_periodo).toInt();
  espera = periodo*100;

  if(enable=='1')
  {
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
    digitalWrite(dir_x,HIGH);
    delay(100);
    movimiento(pul_x,pulsos_entrada_x,espera-50);
    delay(100);
    
    //Desplazamiento en y:
//    digitalWrite(ena_y,LOW);
//    delay(1000);
    digitalWrite(dir_y,HIGH);
    delay(100);
    movimiento(pul_y,pulsos_entrada_y,espera-50);
    delay(100);

    //Desplazamiento en Z
    digitalWrite(dir_z,LOW); //activa el motor direccion hacia abajo
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10); //envia pulsos al motor para bajar hasta el asic
    delay(100);
    digitalWrite(bomba,HIGH); //activa la bomba 
    delay(1000); //espera 1 segundo con la ventosa en el asic mientras hace el vacio.
    digitalWrite(dir_z,HIGH); //activa el motor para la direccion hacia arriba
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10); //envia pulsos para subir e irse al socket
    delay(100);
//    digitalWrite(ena_z,HIGH);
//    delay(1000);
//    digitalWrite(ena_z,LOW);
//    delay(1000);
//    digitalWrite(ena_z,HIGH);
//    delay(100);
    //Fin desplazamiento en Z

    
    //Desplazamiento al socket en Y
    digitalWrite(dir_y,LOW);
    delay(100);
    movimiento(pul_y,entrada_socket_y,espera-50);
    delay(100);

    //Desplazamiento al socket en X
    digitalWrite(dir_x,LOW);
    delay(100);
    movimiento(pul_x,entrada_socket_x,espera-50);
    delay(100);

    //Accionamiento del socket
    myservo.write(150); 
    delay(1000);

    //Desplazamiento en Z
//    digitalWrite(ena_z,LOW);
//    delay(1000);
    digitalWrite(dir_z,LOW);
    delay(100);
    movimiento(pul_z,pulsos_z_soltar_socket,10);
    delay(1000);//estaba a 1000, se prueba con 5000, 08/07/2024,pero no da resultado porque el problema es que roza un poco en el scket y pierde vacio
    digitalWrite(bomba,LOW);

 //Delay para ajustar tarjeta:
  
  //delay(600000);

    delay(1000);
    digitalWrite(dir_z,HIGH);
    delay(100);
    movimiento(pul_z,pulsos_z_soltar_socket,10);
    delay(100);
    //Fin desplazamiento en Z

   

    //Relajación del socket
    myservo.write(0);
    delay(1000);
    
    trigger=2;
    Serial.print(trigger);
    trigger=0;

    delay(2000);

    trigger=3;
    Serial.print(trigger);
    trigger=0;

    digitalWrite(ena_x,HIGH);   //En este caso desactivamos el Enable de X cuando el efector está sobre el socket porque el robot espera en esa posición a que se ejecute el test.
    delay(1000);                //Como el socket está en la posición (0,0), la desactivación del Enable no debería causar problemas (el robot da los mismos pasos para coger el
    digitalWrite(ena_x,LOW);    //asic que para dejarlo en el socket, por lo que los pasos netos entre desactivaciones del enable son siempre 0).
    delay(1000);
    digitalWrite(ena_x,HIGH);
    delay(100);

    digitalWrite(ena_y,HIGH);
    delay(1000);
    digitalWrite(ena_y,LOW);
    delay(1000);
    digitalWrite(ena_y,HIGH);
    delay(100);

    digitalWrite(ena_z,HIGH);
    delay(1000);
    digitalWrite(ena_z,LOW);
    delay(1000);
    digitalWrite(ena_z,HIGH);
    delay(100);
    
    //Aquí esperaríamos a que se ejecutase el test

    while(Serial.available()==0){}
    
    while(Serial.read()!='1')
    {
      while(Serial.read()!='2'){}
      myservo.write(150);
      delay(1000);
      while(Serial.read()!='3'){}
      myservo.write(0);
      delay(1000);
      while(Serial.available()==0){}
    }
    
    while(Serial.available()==0){}
    resultado = Serial.read();

///AQUI PODRIAMOS METER EL CÓDIGO QUE HACE UNA REFERENCIA A ORIGEN CON LOS FINALES DE CARRERA,ANTES DE IRSE A COLOCAR EL ASIC EN BANDEJA 
//PARA QUE PARTA DE SU ZERO (0,0,0) EXACTO SIEMPRE.
    //Accionamiento del socket
    myservo.write(150);
    delay(1000);

    //Desplazamiento en Z
    digitalWrite(ena_x,LOW);
    delay(100);
    digitalWrite(ena_y,LOW);
    delay(100);
    digitalWrite(ena_z,LOW);
    delay(1000);
    digitalWrite(dir_z,LOW);
    delay(100);
    movimiento(pul_z,pulsos_z_coger_socket,10);
    delay(100);
    digitalWrite(bomba,HIGH);
    delay(2000); //aumentamos a 2000 para asegurar mejor el vacío al cogerlo
    digitalWrite(dir_z,HIGH);
    delay(100);
    movimiento(pul_z,pulsos_z_coger_socket,10);
    delay(100);
//    digitalWrite(ena_z,HIGH);
//    delay(1000);
//    digitalWrite(ena_z,LOW);
//    delay(1000);
//    digitalWrite(ena_z,HIGH);
//    delay(100);
    //Fin desplazamiento en Z

    //Relajación del socket
    myservo.write(0);
    delay(1000);

    if (resultado=='1')
    {
      //Desplazamiento a la celda de salida OK en X
//      digitalWrite(ena_x,LOW);
//      delay(1000);
      digitalWrite(dir_x,HIGH);
      delay(100);
      movimiento(pul_x,socket_salidaOK_x,espera-50);
      delay(100);
  
      //Desplazamiento a la celda de salida OK en Y
//      digitalWrite(ena_y,LOW);
//      delay(1000);
      digitalWrite(dir_y,HIGH);
      delay(100);
      movimiento(pul_y,socket_salidaOK_y,espera-50);
      delay(100);

      //Desplazamiento en Z
//      digitalWrite(ena_z,LOW);
//      delay(1000);
      digitalWrite(dir_z,LOW);
      delay(100);
      movimiento(pul_z,pulsos_z_soltar_bandeja,10);
      delay(1000); //probamos con 5000 08/07/2024
      digitalWrite(bomba,LOW);
      delay(1000);
      digitalWrite(dir_z,HIGH);
      delay(100);
      movimiento(pul_z,pulsos_z_soltar_bandeja,10);
      delay(100);
//      digitalWrite(ena_z,HIGH);
//      delay(1000);
//      digitalWrite(ena_z,LOW);
//      delay(1000);
//      digitalWrite(ena_z,HIGH);
//      delay(100);
      //Fin desplazamiento en Z

      digitalWrite(dir_y,LOW);
      delay(100);
      movimiento(pul_y,pulsos_salidaOK_y,espera-50);
      delay(100);
  
      //Vuelta al origen en X
      digitalWrite(dir_x,LOW);
      delay(100);
      movimiento(pul_x,pulsos_salidaOK_x,espera-50);
      delay(100);

      salidaOK_x++;
      
      digitalWrite(Led,LOW);
    }  
     
  else
    {
      //Desplazamiento a la celda de salida NOK en X
      //digitalWrite(ena_x,LOW);
      //delay(1000);
      digitalWrite(dir_x,HIGH);
      delay(100);
      movimiento(pul_x,socket_salidaNOK_x,espera-50);
      delay(100);
  
      //Desplazamiento a la celda de salida NOK en Y
      //digitalWrite(ena_y,LOW);
      //delay(1000);
      digitalWrite(dir_y,HIGH);
      delay(100);
      movimiento(pul_y,socket_salidaNOK_y,espera-50);
      delay(100);

      //Desplazamiento en Z
      //digitalWrite(ena_z,LOW);
      //delay(1000);
      digitalWrite(dir_z,LOW);
      delay(100);
      movimiento(pul_z,pulsos_z_soltar_bandeja,10);
      delay(1000);//probamos con 5000,08/07/2024 estaba en 1000
      digitalWrite(bomba,LOW);
      delay(1000);
      digitalWrite(dir_z,HIGH);
      delay(100);
      movimiento(pul_z,pulsos_z_soltar_bandeja,10);
      delay(100);
//      digitalWrite(ena_z,HIGH);
//      delay(1000);
//      digitalWrite(ena_z,LOW);
//      delay(1000);
//      digitalWrite(ena_z,HIGH);
//      delay(100);
      //Fin desplazamiento en Z
      
      //Vuelta al origen en Y
      digitalWrite(dir_y,LOW);
      delay(100);
      movimiento(pul_y,pulsos_salidaNOK_y,espera-50);
      delay(100);
  
      //Vuelta al origen en X
      digitalWrite(dir_x,LOW);
      delay(100);
      movimiento(pul_x,pulsos_salidaNOK_x,espera-50);
      delay(100);
      
      salidaNOK_x++;

      digitalWrite(Led,LOW);
    }
    entrada_x++;
  }
  else
  {
    digitalWrite(Led,LOW);
    delay(1000);
  }

  digitalWrite(ena_x,HIGH);
  delay(1000);
  digitalWrite(ena_x,LOW);
  delay(1000);
  digitalWrite(ena_x,HIGH);
  delay(1000);

  digitalWrite(ena_y,HIGH);
  delay(1000);
  digitalWrite(ena_y,LOW);
  delay(1000);
  digitalWrite(ena_y,HIGH);
  delay(100);

  digitalWrite(ena_z,HIGH);
  delay(1000);
  digitalWrite(ena_z,LOW);
  delay(1000);
  digitalWrite(ena_z,HIGH);
  delay(100);
  
  fin++; //Incremento en el número de iteraciones que lee Labview (manda 1 byte por dígito)

  
  Serial.print(fin);
}
