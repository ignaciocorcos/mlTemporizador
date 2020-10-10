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
    uint32_t  _millisInicio;              // millis en el momento que iniciamos el temporizador
    uint32_t  _millisDuracion;            // millis que debe durar el temporizador
    uint32_t  _millisRestantesTrasPausa;  // millis que quedan tras poner el el temporizador en pausa
    bool      _activado;                  // para activarlo cuando queramos
    bool      _haPasadoElPlazo;           // indica si se ha cumplido el tiempo estimado
    bool      _estaEnPausa;               // indica si el temporizador esta en pausa  

  public:
    mlTemporizador( uint32_t pMillisDuracion );
    void      Activar( void );
    void      Resetear( void );
    void      PonerEnPausa( void );
    void      ContinuarDesdePausa( void );
    boolean   EstaActivado( void );
    boolean   ElPlazoHaPasado( void );
    boolean   EstaPausado( void );
    uint32_t  TiempoRestanteEnSeg( void );
    uint32_t  TiempoRestanteEnMillis( void );
    uint32_t  TiempoDesdeInicioEnSeg( void );
    uint32_t  CalculaMillisDuracionActuales( void );
};

#endif