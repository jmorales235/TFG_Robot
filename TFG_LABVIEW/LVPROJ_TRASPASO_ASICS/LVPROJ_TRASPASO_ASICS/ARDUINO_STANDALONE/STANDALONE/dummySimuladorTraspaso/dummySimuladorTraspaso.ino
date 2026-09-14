#include <Math.h>


int coordenadaX_origen=8;
int coordenadaY_origen=0;
int coordenadaX_destino=1;
int coordenadaY_destino=0;

int coord_siguiente_ORIGEN_X=0;
int coord_siguiente_ORIGEN_Y=0;
int coord_siguiente_DESTINO_X=0;
int coord_siguiente_DESTINO_Y=0;

long pasoCeldaX=1350;
long pasoCeldaY=1077;
long numAsics_amover=10;
int correcion=1;

boolean flag=false;

long PASOS_X_A_PRIMERA_ORIGEN=18400;
long PASOS_Y_A_PRIMERA_ORIGEN=32400;
long PASOS_X_A_PRIMERA_DESTINO=36000;
long PASOS_Y_A_PRIMERA_DESTINO=32400;

long PASOS_COORD_BANDEJAORIGEN_X;
long PASOS_COORD_BANDEJAORIGEN_Y;
long PASOS_COORD_BANDEJADESTINO_X;
long PASOS_COORD_BANDEJADESTINO_Y;

long PASOS_TRASLADO_X;
long PASOS_TRASLADO_Y;
long PASOS_VUELTA_X;
long PASOS_VUELTA_Y;

int sentido_TrasladoY ;
int sentido_VueltaY ;




void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  coord_siguiente_ORIGEN_Y=coordenadaY_origen;
  coord_siguiente_DESTINO_Y=coordenadaY_destino;

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
    Serial.print('\n');
    Serial.print("Sentido Traslado Y:");
    Serial.println(sentido_TrasladoY);
    
    Serial.print("Sentido Vuelta Y:");
    Serial.println(sentido_VueltaY);



while (flag==true){

}

  for (int numTraslados=0; numTraslados<numAsics_amover; numTraslados++){

    Serial.print('\n');
    Serial.print("Sentido Traslado Y:");
    Serial.println(sentido_TrasladoY);
    
    Serial.print("Sentido Vuelta Y:");
    Serial.println(sentido_VueltaY);
       
    Serial.print("Numero traslados:");
    Serial.println(numTraslados);
    
    Serial.print("CoordenadaXorigen:");
    Serial.println(coordenadaX_origen);
    Serial.print("CoordenadaYorigen:");
    Serial.println(coordenadaY_origen);
    Serial.print("CoordenadaXdestino:");
    Serial.println(coordenadaX_destino);
    Serial.print("CoordenadaYdestino:");
    Serial.println(coordenadaY_destino);

    

    
  coord_siguiente_ORIGEN_X= coordenadaX_origen + 1;
  coord_siguiente_DESTINO_X= coordenadaX_destino + 1;

  
  
  
  if(coordenadaX_origen==9){

    coord_siguiente_ORIGEN_X=0;
    coord_siguiente_ORIGEN_Y=coord_siguiente_ORIGEN_Y + 1;

  }

   if(coordenadaX_destino==9){

    coord_siguiente_DESTINO_X=0;
    coord_siguiente_DESTINO_Y=coord_siguiente_DESTINO_Y + 1;

  }
Serial.print("CoordenadaSiguiente_ORIGEN_X:");
Serial.println(coord_siguiente_ORIGEN_X);

Serial.print("CoordenadaSiguiente_ORIGEN_Y:");
Serial.println(coord_siguiente_ORIGEN_Y);

Serial.print("CoordenadaSiguiente_DESTINO_X:");
Serial.println(coord_siguiente_DESTINO_X);

Serial.print("CoordenadaSiguiente_DESTINO_Y:");
Serial.println(coord_siguiente_DESTINO_Y);



//calculo de pasos a coordenada bandeja de origen respecto de la posicion HOME
PASOS_COORD_BANDEJAORIGEN_X = (PASOS_X_A_PRIMERA_ORIGEN +pasoCeldaX*coordenadaX_origen*correcion);

Serial.print("pasos a bandeja origen_X:");
Serial.println(PASOS_COORD_BANDEJAORIGEN_X);

PASOS_COORD_BANDEJAORIGEN_Y = (PASOS_Y_A_PRIMERA_ORIGEN -pasoCeldaY*coordenadaY_origen*correcion);

Serial.print("pasos a bandeja origen_Y:");
Serial.println(PASOS_COORD_BANDEJAORIGEN_Y);
//calculos de pasos a coordenada bandeja destino respecto de la posicion HOME
PASOS_COORD_BANDEJADESTINO_X = ((PASOS_X_A_PRIMERA_DESTINO)+(pasoCeldaX*coordenadaX_destino*correcion));

Serial.print("pasos a bandeja destino_X:");
Serial.println(PASOS_COORD_BANDEJADESTINO_X);

PASOS_COORD_BANDEJADESTINO_Y = ((PASOS_Y_A_PRIMERA_DESTINO)-(pasoCeldaY*coordenadaY_destino*correcion));
Serial.print("pasos a bandeja destino_Y:");
Serial.println(PASOS_COORD_BANDEJADESTINO_Y);


//calculo de pasos movimiento de traslado,y el sentido es en funcion del sentido del traslado, izquierda a derecha ó derecha a izquierda
PASOS_TRASLADO_X= abs(PASOS_COORD_BANDEJADESTINO_X - PASOS_COORD_BANDEJAORIGEN_X);
Serial.print("pasos TRASLADO_X:");
Serial.println(PASOS_TRASLADO_X); //SERÁ VALOR POSITIVO SI EL TRASLADO ES DE IZQ A DERECH //SERÁ NEGATIVO EN CASO CONTRARIO

PASOS_TRASLADO_Y= abs((PASOS_COORD_BANDEJADESTINO_Y - PASOS_COORD_BANDEJAORIGEN_Y)); //SERÁ VALOR POSITIVO SI LA COORDENADA "Y" DESTINO ES MAYOR QUE LA DE ORIGEN. SERÁ NEGATIVO EN CASO CONTRARIO

Serial.print("pasos TRASLADO_Y:");
Serial.println(PASOS_TRASLADO_Y); 

//calculo de pasos vuelta para coger siguiente Asic

PASOS_VUELTA_X = abs((PASOS_TRASLADO_X)-(pasoCeldaX*(coord_siguiente_ORIGEN_X - coordenadaX_origen)));

Serial.print("pasos VUELTA_X:");
Serial.println(PASOS_VUELTA_X);

PASOS_VUELTA_Y = abs((PASOS_TRASLADO_Y)-(pasoCeldaY*(coord_siguiente_ORIGEN_Y - coordenadaY_origen)));

Serial.print("pasos VUELTA_Y:");
Serial.println(PASOS_VUELTA_Y);
Serial.println('\n');

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

if(numTraslados ==9){
  flag=true;
}
  // put your main code here, to run repeatedly:

}
}

