
//AUTOR : JAVIER MORALES
#include "libreria_robot.h"
#include <Arduino.h>
#include <config_pines_arduino.h>
#include <Servo.h>

// IMPORTANTE:
// En C++ no se pueden ejecutar instrucciones sueltas en el ámbito global del .cpp.
// Solo se permiten declaraciones/definiciones globales.
// Llamadas a métodos como servo.attach(), digitalWrite(), etc.
// deben ejecutarse dentro de funciones, métodos o constructores.
//
// Correcto:
//   Servo servoSocket;   // declaración global
//
// Incorrecto:
//   servoSocket.attach(pin_servo); // llamada ejecutable fuera de función , debe meterse dentro de una función


Servo servoSocket; //variable global para que servosocket pueda ser utilizado en las funciones "accionamiento socket" y "relajacion socket"

/////////////////////////////////////////////////////////////////////////////////FUNCIONES ROBOT///////////////////////////////////////////////////////////////////////////////////////
void Home(){
  
             

    digitalWrite(pul_x,LOW);
    delay(100);
    digitalWrite(pul_y,LOW);
    delay(100);
    digitalWrite(pul_z,LOW);
    
    
    digitalWrite(ena_z,LOW); //ACTIVACION DE MOTOR
    delay(1000);
    digitalWrite(dir_z,HIGH);
    delay(100);
    

    while(digitalRead(sensor_z)==LOW) //LECTURA DE FINAL DE CARRERA
  
    
    {
      digitalWrite(pul_z,HIGH);
      delayMicroseconds(50); //90
      digitalWrite(pul_z,LOW);
      delayMicroseconds(50); //90
    }
    
    
    
    digitalWrite(ena_y,LOW); //ACTIVACION DE MOTOR
    delay(1000);
    digitalWrite(dir_y,LOW);
    delay(100);

    while(digitalRead(sensor_y)==LOW) //LECTURA DE FINAL DE CARRERA
    {
      digitalWrite(pul_y,HIGH);
      delayMicroseconds(300);//400
      digitalWrite(pul_y,LOW);
      delayMicroseconds(300);
    }

    
    
    
    digitalWrite(ena_x,LOW); //ACTIVACION DE MOTOR
    delay(1000);
    digitalWrite(dir_x,LOW);
    delay(100);


    while(digitalRead(sensor_x)==LOW) //LECTURA DE FINAL DE CARRERA
    {
      digitalWrite(pul_x,HIGH);
      delayMicroseconds(300);//400
      digitalWrite(pul_x,LOW);
      delayMicroseconds(300);
    }
    
   
}


void Home_inicial(){
	
	digitalWrite(ena_z,LOW); //ACTIVACION DE MOTOR Z
    delay(100);
    digitalWrite(dir_z,LOW); //hacia abajo
    delay(100);

    digitalWrite(ena_x,LOW); //ACTIVACION DE MOTOR X
    delay(100);
    digitalWrite(dir_x,HIGH); // A DERECHA
    delay(100);

    digitalWrite(ena_y,LOW); //ACTIVACION DE MOTOR X
    delay(100);
    digitalWrite(dir_y,HIGH); // hacia delante
    delay(100);

    movimiento(pul_z,3500,50); //1CM HACIA ABAJO
    movimiento(pul_x,2000,200); //derecha
    movimiento(pul_y,2000,200);//avance
  
    Home(); //VUELTA A FINALES DE CARRERA
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char LeerComando_1byte(){

    while (!Serial.available()){}// POLLING HASTA QUE HAYA DATO
    delay(50);
    

    char comando= Serial.read(); //LEO EL COMANDO DE 1 BYTE DE STRING
    return comando;


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void movimiento(int salida, long pulsos, long tiempo) //FUNCION HEREDADA DEL SISTEMA PRIMARIO QUE HIZO RUBÉN MARCO
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void movimientoCorto(int salida, long pulsos) 
{
  
  //EL MOVIMIENTO EN LOS EJES SE EJECUTA A TRAVÉS DE UN BUCLE FOR QUE REALIZA UNA ITERACIÓN POR CADA PULSO(PASO)
  for (long i=0;i<(pulsos);i++)
  {

                                         
    if (i<pulsos){
    digitalWrite(salida,HIGH); //Salida a nivel alto
    delayMicroseconds(400);      //espera
    digitalWrite(salida,LOW);  //Salida a nivel bajo
    delayMicroseconds(400);      //espera
  }
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void enableMotores() //energiza los motores , no se pueden mover con la mano
{
digitalWrite(ena_x,LOW); //Enable activo a nivel bajo
delay(100);
digitalWrite(ena_y,LOW);
delay(100);
digitalWrite(ena_z,LOW);
delay(100);
}

void disableMotor_Z()
{
digitalWrite(ena_z,HIGH);
delay(100);
}

void disableMotor_X()
{
digitalWrite(ena_x,HIGH);
delay(100);
}

void disableMotor_Y()
{
digitalWrite(ena_y,HIGH);
delay(100);
}

void enableMotor_Z()
{
digitalWrite(ena_z,LOW);
delay(100);
}

void enableMotor_X()
{
digitalWrite(ena_x,LOW);
delay(100);
}

void enableMotor_Y()
{
digitalWrite(ena_y,LOW);
delay(100);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initServo(){

servoSocket.attach(pin_servo);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void accionamientoSocket() //acciona socket para introducir asic
{
 servoSocket.write(163); 
 delay(1000);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void relajacionSocket() //relaja socket para sujetar asic
{
 servoSocket.write(0); 
 delay(1000);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void activarBomba(){
digitalWrite(bomba,HIGH); //activa succión
delay(2500); //espera 2.5 segundo con la ventosa en el asic mientras hace el vacio.  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void desactivarBomba() //desactiva succión
{
digitalWrite(bomba,LOW);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void derecha_X()
{
digitalWrite(dir_x,HIGH);
delay(10);
}

void izquierda_X()
{
digitalWrite(dir_x,LOW);
 delay(10);
}

void avance_Y()
{
 digitalWrite(dir_y,HIGH);
 delay(10);
}

void retroceso_Y()
{
digitalWrite(dir_y,LOW);
delay(10);
}

void bajar_Z()
{
digitalWrite(dir_z,LOW); //activa el motor direccion hacia abajo
delay(100);
}

void subir_Z()
{
digitalWrite(dir_z,HIGH); //activa el motor direccion hacia arriba
delay(100);
}

void disableMotores()
{
    digitalWrite(ena_x,HIGH);
    delay(100);
    digitalWrite(ena_y,HIGH);
    delay(100);
    digitalWrite(ena_z,HIGH);
    delay(100);
}

////////////////////////////////////////////////////////////////////////////////////////FUNCIONES DUMMY PARA PRUEBAS//////////////////////////////////////////////////////////////////////

void tareaA(){ 
int i = 0;
while (true){
    
    
    if(Serial.available()>0){
    char salir = Serial.read();
    
    if(salir=='9'){
      Serial.print(salir);
      return;}
    } 
    i++;
  }
  
}

void tareaB(){
int i = 0;
while (true){
    
    
    if(Serial.available()>0){
    char salir = Serial.read();
    
    if(salir=='9'){
      Serial.print(salir);
      return;}
    } 
    i++;
  }
  
}

void tareaC(){
int i = 0;
while (true){
    
    
    if(Serial.available()>0){
    char salir = Serial.read();
    
    if(salir=='9'){
      Serial.print(salir);
      return;}
    } 
    i++;
  }
  
}

void tareaD(){
int i = 0;
while (true){
    
    
    if(Serial.available()>0){
    char salir = Serial.read();
    
    if(salir=='9'){
      Serial.print(salir);
      return;}
    } 
    i++;
  }
  
}

