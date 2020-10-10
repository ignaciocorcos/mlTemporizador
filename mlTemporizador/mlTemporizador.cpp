/*
  mlTemporizador.h - Librería para usar temporizadores de manera sencilla.
  Creada por Miguel Ángel López Harillo, 2020/08/21
  Distribuida bajo licencia GNU General Public License V3 
*/
 
#include "Arduino.h"
#include "mlTemporizador.h"

    mlTemporizador::mlTemporizador( uint32_t pMillisDuracion )
    {
      _millisDuracion   = pMillisDuracion;
      _activado         = false;
      _haPasadoElPlazo  = false;
      _estaEnPausa      = false;
    }

    void mlTemporizador::Activar( void )
    {
      if ( _activado == false )
      {
        _activado     = true;
        _millisInicio = millis();
      }
    }

    void mlTemporizador::Resetear( void )
    {
      _activado         = false;
      _haPasadoElPlazo  = false;
      _estaEnPausa      = false;
    }

    void mlTemporizador::PonerEnPausa( void )
    {
      _estaEnPausa      = true;
    }

    void mlTemporizador::ContinuarDesdePausa( void )
    {
      _estaEnPausa      = false;
    }

    boolean mlTemporizador::EstaActivado( void )
    {
      return _activado;
    }

    boolean mlTemporizador::EstaPausado( void )
    {
      return _estaEnPausa;
    }

    boolean mlTemporizador::ElPlazoHaPasado( void )
    {
      
      uint32_t millisDuracionActuales = CalculaMillisDuracionActuales();

      if ( _activado    == true 
        && _estaEnPausa == false
        && ( ( millis() - _millisInicio ) 
              >= millisDuracionActuales )
         )
      {
        _haPasadoElPlazo  = true;
        _activado         = false;
      }
      return _haPasadoElPlazo;
    }

    uint32_t mlTemporizador::TiempoRestanteEnSeg( void ) 
    {
      uint32_t tiempoRestante         = 0;
      uint32_t millisDuracionActuales = CalculaMillisDuracionActuales();
     
      if ( _activado        == true 
        && _haPasadoElPlazo == false 
         )
      {
        tiempoRestante = (uint32_t)round(
                                (
                                  ( _millisInicio + millisDuracionActuales )
                                  - millis()
                                ) / 1000
                          );
      }
      return tiempoRestante;
    }

    uint32_t mlTemporizador::TiempoDesdeInicioEnSeg( void )
    {
      uint32_t tiempoDesdeInicioTemporizador  = 0;
      uint32_t millisDuracionActuales         = CalculaMillisDuracionActuales();

      if ( _activado == true 
        && _haPasadoElPlazo == false 
         )
        tiempoDesdeInicioTemporizador = (uint32_t)round(
                                          ( millisDuracionActuales - ( TiempoRestanteEnSeg() * 1000 ) )
                                          / 1000
                                        );
      return tiempoDesdeInicioTemporizador;     
    }
    
    uint32_t mlTemporizador::CalculaMillisDuracionActuales( void )
    {
      uint32_t millisDuracionActuales;
      if ( _estaEnPausa == true )
        {
          millisDuracionActuales = _millisRestantesTrasPausa;
        } else 
          {
            millisDuracionActuales = _millisDuracion;
          }
      return millisDuracionActuales;
    }