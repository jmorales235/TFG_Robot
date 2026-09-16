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

long pulsos_z_coger_bandeja = (pulsos_rev/200)*3750; //Estaba en *3500
long pulsos_z_soltar_bandeja = (pulsos_rev/200)*3550;
long pulsos_z_coger_socket = (pulsos_rev/200)*2350;
long pulsos_z_soltar_socket = (pulsos_rev/200)*2100;

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
  
//  for (long i=0;i<(its);i++)
//  {
//    //t = (((its-i)/its)*tiempo*29)+tiempo;
//
//    digitalWrite(salida,HIGH);
//    delayMicroseconds(t);
//    digitalWrite(salida,LOW);
//    delayMicroseconds(t);
//  }

  for (long i=0;i<(pulsos);i++)
  {

    if((i<pulsos/64)or(i>63*pulsos/64))
    {
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
    
    digitalWrite(salida,HIGH);
    delayMicroseconds(t);
    digitalWrite(salida,LOW);
    delayMicroseconds(t);
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

  //Lectura de la celda de la bandeja de entrada

  myservo.write(0);
  
  while(Serial.available()==0){} //Uso esto para esperar a que haya un dato disponible en el puerto serie.
  lectura1 = Serial.read();
  while(Serial.available()==0){}
  lectura2 = Serial.read();

  //////////////////////////////////////////REFERENCIA A ORIGEN////////////////////////////////////////////
  
  if (fin==0) //Desplazamiento a la posición de referencia (origen) utilizando los sensores fin de carrera
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

  if (fin==0)
  {
    //Conversión de los char leídos a int:
    coord1 = String(lectura1).toInt();
    coord2 = String(lectura2).toInt();
    entrada_x = coord1*10 + coord2;
    entrada_x_primera = entrada_x;
  }

  while(Serial.available()==0){}
  lectura1 = Serial.read();
  while(Serial.available()==0){}
  lectura2 = Serial.read();

  if (fin==0)
  {
    coord1 = String(lectura1).toInt();
    coord2 = String(lectura2).toInt();
    entrada_y = coord1*10 + coord2;
  }

  //Lectura de la celda de la bandeja de salida OK

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

  while(Serial.available()==0){}
  lectura1 = Serial.read();
  while(Serial.available()==0){}
  lectura2 = Serial.read();

  if (fin==0)
  {
    coord1 = String(lectura1).toInt();
    coord2 = String(lectura2).toInt();
    salidaOK_y = coord1*10 + coord2;
  }

  //Lectura de la celda de la bandeja de salida NOK
 
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

  while(Serial.available()==0){}
  lectura_periodo = Serial.read();

  while(Serial.available()==0){}
  enable = Serial.read();

  if (entrada_x==10)
  {
    entrada_x = 0;
    entrada_y = entrada_y+1;
  }

  if (salidaOK_x==10)
  {
    salidaOK_x = 0;
    salidaOK_y = salidaOK_y+1;
  }

  if (salidaNOK_x==10)
  {
    salidaNOK_x = 0;
    salidaNOK_y = salidaNOK_y+1;
  }
  

  pulsos_entrada_x = (546+entrada_x*36.5)*(pulsos_rev/200); // (550,725) es la primera celda y hay 37 y 34 pulsos de separación entre cada una en los ejes X e Y, respectivamente.
  pulsos_entrada_x_add= (36.625)*(pulsos_rev/200);
  pulsos_entrada_y = (658-entrada_y*33.625)*(pulsos_rev/200); //Antes el paso era de 33.75

  pulsos_salidaOK_x = (935+salidaOK_x*36.5)*(pulsos_rev/200); //Pulsos desde el origen a la celda de salida de la bandeja OK (con bandejas juntas es 537)
  pulsos_salidaOK_y = (658-salidaOK_y*33.625)*(pulsos_rev/200);

  pulsos_salidaNOK_x = (1323+salidaNOK_x*36.5)*(pulsos_rev/200); //Pulsos desde el origen a la celda de salida de la bandeja NOK (con bandejas juntas es 925)
  pulsos_salidaNOK_y = (658-salidaNOK_y*33.625)*(pulsos_rev/200);

  entrada_socket_x = pulsos_entrada_x; //pulsos entre la posicion del Asic y el socket en el eje X (el socket está en el origen)
  entrada_socket_y = pulsos_entrada_y; //pulsos entre la posición del Asic y el socket en el eje Y.

  socket_salidaOK_x = pulsos_salidaOK_x; //pulsos entre el socket y la celda de la bandeja de salida OK
  socket_salidaOK_y = pulsos_salidaOK_y;

  socket_salidaNOK_x = pulsos_salidaNOK_x; //pulsos entre el socket y la celda de la bandeja de salida NOK
  socket_salidaNOK_y = pulsos_salidaNOK_y;
  
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
    if(entrada_x==0 || ((entrada_x==entrada_x_primera)&&(fin==0)))
    {
      movimiento(pul_x,pulsos_entrada_x,espera-50);
//    Desplazamiento en y:
//    digitalWrite(ena_y,LOW);
//    delay(1000);
      digitalWrite(dir_y,HIGH);
      delay(100);
      movimiento(pul_y,pulsos_entrada_y,espera-50);
      delay(100);
    }
    else
    {
      movimiento(pul_x,pulsos_entrada_x_add,espera+100);
    }
    delay(100);

    //Desplazamiento en Z
    digitalWrite(dir_z,LOW);
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10);
    delay(100);
    digitalWrite(bomba,HIGH);
    delay(1000);
    digitalWrite(dir_z,HIGH);
    delay(100);
    movimiento(pul_z,pulsos_z_coger_bandeja,10);
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
    delay(100);
    digitalWrite(bomba,LOW);
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
    delay(1000);
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

    if (resultado=='0' or resultado=='1')
    {
      //Desplazamiento a la celda de salida OK en X
//      digitalWrite(ena_x,LOW);
//      delay(1000);
      digitalWrite(dir_x,HIGH);
      delay(100);
      movimiento(pul_x,pulsos_entrada_x,espera-50);
      delay(100);
  
      //Desplazamiento a la celda de salida OK en Y
//      digitalWrite(ena_y,LOW);
//      delay(1000);
      digitalWrite(dir_y,HIGH);
      delay(100);
      movimiento(pul_y,pulsos_entrada_y,espera-50);
      delay(100);

      //Desplazamiento en Z
//      digitalWrite(ena_z,LOW);
//      delay(1000);
      digitalWrite(dir_z,LOW);
      delay(100);
      movimiento(pul_z,pulsos_z_soltar_bandeja,10);
      delay(1000);
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

      if(entrada_x==9)
      {
        //Vuelta al origen en Y
        digitalWrite(dir_y,LOW);
        delay(100);
        movimiento(pul_y,pulsos_entrada_y,espera-50);
        delay(100);
    
        //Vuelta al origen en X
        digitalWrite(dir_x,LOW);
        delay(100);
        movimiento(pul_x,pulsos_entrada_x,espera-50);
        delay(100);
      }

      entrada_x++;
      digitalWrite(Led,LOW);
    }  
  }
  
  else
  {
    digitalWrite(Led,LOW);
    delay(1000);
  }

  if(entrada_x==10)
  {
  
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
  }
  
  fin++; //Incremento en el número de iteraciones que lee Labview (manda 1 byte por dígito)

  
  Serial.print(fin);
}
