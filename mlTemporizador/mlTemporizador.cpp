/*
  mlTemporizador.h - Librería para usar temporizadores de manera sencilla.
  Creada por Miguel Ángel López Harillo, 2020/08/21
  Distribuida bajo licencia GNU General Public License V3 
*/
 
#include "Arduino.h"
#include "mlTemporizador.h"

    mlTemporizador::mlTemporizador( uint32_t pMillisDuracion )
    {
      _millisDuracion  =   pMillisDuracion;
      _haPasadoElPlazo =   false;
      _activado        =   false;
    }

    void mlTemporizador::Activar()
    {
      if ( _activado == false )
      {
        _activado  = true;
        _millisInicio = millis();
      }
    }

    void mlTemporizador::Resetear()
    {
      _activado  = false;
      _haPasadoElPlazo = false;
    }

    boolean mlTemporizador::EstaActivado()
    {
      return _activado;
    }

    boolean mlTemporizador::ElPlazoHaPasado()
    {
      if ( _activado  == true 
        && ( millis() - _millisInicio  >= _millisDuracion )
         )
      {
        _haPasadoElPlazo = true;
        _activado = false;
      }
      return _haPasadoElPlazo;
    }

    uint32_t mlTemporizador::TiempoRestanteEnSeg()
    {
      uint32_t tiempoRestante = 0;
      if ( _activado == true 
        && _haPasadoElPlazo == false 
         )
        tiempoRestante = (uint32_t)round(
                                (
                                  ( _millisInicio + _millisDuracion )
                                  - millis()
                                ) / 1000
                              );
      return tiempoRestante;
    }

    uint32_t mlTemporizador::TiempoDesdeInicioEnSeg()
    {
      uint32_t tiempoDesdeInicioTemporizador = 0;
      if ( _activado == true 
        && _haPasadoElPlazo == false 
         )
        tiempoDesdeInicioTemporizador = (uint32_t)round(
                                          ( _millisDuracion - ( TiempoRestanteEnSeg() * 1000 ) )
                                          / 1000
                                        );
      return tiempoDesdeInicioTemporizador;     
    }