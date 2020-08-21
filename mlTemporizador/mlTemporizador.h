/*
  mlTemporizador.h - Librería para usar temporizadores de manera sencilla.
  Creada por Miguel Ángel López Harillo, 2020/08/21 
  Distribuida bajo licencia GNU General Public License V3
*/
#ifndef mlTemporizador_h
#define mlTemporizador_h

#include "Arduino.h"

class mlTemporizador
{
   private:
    uint32_t _millisInicio;      // millis en el momento que iniciamos el temporizador
    uint32_t _millisDuracion;    // millis que debe durar el temporizador
    bool _activado;              // para activarlo cuando queramos
    bool _haPasadoElPlazo;       // indica si se ha cumplido el tiempo estimado

  public:
    mlTemporizador( uint32_t pMillisDuracion );
    void Activar();
    void Resetear();
    boolean EstaActivado();
    boolean ElPlazoHaPasado();
    uint32_t TiempoRestanteEnSeg();
    uint32_t TiempoDesdeInicioEnSeg();
};

#endif