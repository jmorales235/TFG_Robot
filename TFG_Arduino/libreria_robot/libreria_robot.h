
//AUTOR : JAVIER MORALES

#ifndef LIBRERIA_ROBOT_H

#define LIBRERIA_ROBOT_H

#include <Arduino.h>

///////////////////////////////////////////funciones dummy de prueba////////////////////////////////////

void tareaA();
void tareaB();
void tareaC();
void tareaD();



///////////////////////////////////////////funciones robot////////////////////////////////////

void Home();

void Home_inicial();

char LeerComando_1byte();

void movimiento(int salida, long pulsos, long tiempo); //aplica un numero de pasos ("pulsos") en "salida", con un tiempo entre pulsos de "tiempo"

void movimientoCorto(int salida, long pulsos);

void initServo();

void enableMotores(); //energiza los motores , no se pueden mover con la mano

void disableMotores(); //quita la corriente a los motores permitiendo movimiento libre del cabezal

void disableMotor_Z();

void disableMotor_X();

void disableMotor_Y();

void enableMotor_Z();

void enableMotor_X();

void enableMotor_Y();

void derecha_X();

void izquierda_X();

void avance_Y();

void retroceso_Y();

void bajar_Z();

void subir_Z();

void accionamientoSocket(); //acciona socket para introducir asic

void relajacionSocket(); //relaja socket para sujetar asic

void activarBomba(); //activa succión 

void desactivarBomba(); //desactiva succión


#endif