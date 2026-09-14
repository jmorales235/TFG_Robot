#ifndef LIBRERIA_FUNCIONES_TAREAS_H

#define LIBRERIA_FUNCIONES_TAREAS_H

#include <Arduino.h>




////////////////////////////////////////////////////////////////////////////////DEFINICIONES TIPOS///////////////////////////////////////////////////

struct Posicion //POSICION ABSOLUTA CUALQUIERA EN PASOS DENTRO DEL TABLERO
{
    long x; //PASOS
    long y;
    long z;
    
};

extern Posicion posActual;

struct Bandeja   //Variable tipo estructura. Representa los datos característicos de una bandeja tipo JEDEC
{
    Posicion origen;      // Coordenadas absolutas de la celda (0,0)
    long pasoX; //numero de pasos que hay entre celdas consecutivas de la bandeja.
    long pasoY;
    int filas; //numero total de filas en bandeja
    int columnas; //numero otal de columnas en bandeja
};

struct Celda //Variable tipo estructura. Representa una coordenada en formato (x,y) de una bandeja,tanto de origen como destino
{
    int fila;
    int columna;
};

/////////////////////////////////////////////////////////////////////////////////FUNCIONES///////////////////////////////////////////////////////////////////////////////

Posicion coordenadaFisica(Bandeja *b, Celda c);

/*void test(
    Bandeja *bandejaIN,
    Bandeja *bandejaOK,
    Bandeja *bandejaNOK,
    Celda inicioIN,
    Celda inicioOK,
    Celda inicioNOK,
    int cantidad
);*/

void siguienteCelda(Bandeja *b, Celda *c);

void moverXY(Posicion destino);

void moverMotorX(long dx);

void moverMotorY(long dy);

void moverZ(long zDestino);

void cogerDeBandeja(Bandeja *b, Celda c);

void dejarEnBandeja(Bandeja *b, Celda c);

void cogerDelSocket(Posicion socket);

void dejarEnSocket(Posicion socket);

/////////////////////////////////////////////////////FUNCIONES ESPECIFICAS DE TEST ASICS//////////////////////////////////////////////////////////////

void recibirDatosEstacion(
    Bandeja *b1,
    Bandeja *b2,
    Bandeja *b3,
    Posicion *socket
);

void recibirDatosTest(
    Celda *c1,
    Celda *c2,
    Celda *c3
);

void esperarResultado(String *resultado);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////FUNCIONES ESPECIFICAS DE LEER QR////////////////////////////////////////////////////////////////

void recibirDatosEstacion_QR(Bandeja *b1 , Posicion *socket );

void recibirDatos_LecturaQR(Celda *c1);

void esperar_LecturaQR (String *resultado);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////FUNCIONES ESPECIFICAS DE TRASPASO ASICS//////////////////////////////////////////////////////////////

void recibirDatosEstacion_TRASPASO(Bandeja *b1 , Bandeja *b2);
void recibirDatosTest_TRASPASO(Celda *c1 , Celda *c2);




#endif