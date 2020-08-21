/*
	Ejemplo que crea dos temporizadores. 
	Del primero muestra la cuenta atrás. Cuando termina el primero, inicia el segundo.
	Del siguiente temporizador muestra los segundos que han pasado desde que se ha iniciado.
 
*/

#include <Arduino.h>
#include <string.h>
#include "mlTemporizador.h"

#define USAR_PANTALLA_LCD 1
#if USAR_PANTALLA_LCD
#include <LiquidCrystal_I2C.h>
const uint8_t lcdColumns  = 16;
const uint8_t lcdRows     = 2;
LiquidCrystal_I2C pantallaLCD( 0x27 , lcdColumns , lcdRows );
#endif

// imprime el texto en el LCD y lo muestra por el puerto serie. El texto no cambia hasta que se vuelve a llamar a la función
void imprimeTexto( const char* linea1 , const char* linea2 )
{
#if USAR_PANTALLA_LCD
  pantallaLCD.clear();

  pantallaLCD.setCursor( 0 , 0 );
  pantallaLCD.print( linea1 );

  pantallaLCD.setCursor( 0 , 1 );
  pantallaLCD.print( linea2 );
#endif

  Serial.println( linea1 );
  Serial.println( linea2 );
}

const uint32_t tiempo1 = 10000;
const uint32_t tiempo2 = 5000;

mlTemporizador temp1( tiempo1 );
mlTemporizador temp2( tiempo2 );

void setup() {
  Serial.begin( 115200 );

#if USAR_PANTALLA_LCD
  pantallaLCD.init();
  pantallaLCD.backlight();
#endif

  temp1.Activar();
  imprimeTexto( "Temporizador 1" , "Activado" );
}

void loop() {

  // Si el Temporizador está desactivado pero el plazo no ha pasado
  if ( temp1.EstaActivado() == false 
    && temp1.ElPlazoHaPasado() == true 
     )
  {
    imprimeTexto( "Temporizador 1" , "Desactivado" );
    temp1.Resetear();

    delay( 1000 );
    temp2.Activar();
    imprimeTexto( "Temporizador 2" , "Activado" );
  }
  // Si el Temporizador está activado pero el plazo no ha pasado, mostramos el tiempo que falta
  else if ( temp1.EstaActivado() == true 
         && temp1.ElPlazoHaPasado() == false 
         )
  {
    char segRestantesTxt1[16];
    snprintf(segRestantesTxt1,
             16,
             "%u",
             temp1.TiempoRestanteEnSeg()
            );
    imprimeTexto( "Temp1. Seg rest" , segRestantesTxt1 );
    delay(100);
  }

  // Si el Temporizador está desactivado pero el plazo no ha pasado
  if ( temp2.EstaActivado() == false 
    && temp2.ElPlazoHaPasado() == true 
     )
  {
    // lo que queramos hacer
    imprimeTexto( "Temporizador 2" , "Desactivado" );
    temp2.Resetear();
  } else if ( temp2.EstaActivado() == true 
           && temp2.ElPlazoHaPasado() == false 
            )
  {
    char segDesdeInicioTxt[16];
    snprintf(segDesdeInicioTxt,
             16,
             "%u",
             temp2.TiempoDesdeInicioEnSeg()
            );
    imprimeTexto( "Temp2. Seg total" , segDesdeInicioTxt );
    delay(100);
  }

}