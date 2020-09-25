/*****************************************************************************/
/****** FUNCIÓN PARA CAMBIAR DE ESTADO Y EJECUTAR FUNCIONES DE EVENTO ********/
/*****************************************************************************/
void CambiarEstado(int sigEstado) {
  switch (sigEstado) {
    case estadoPrueba:
      log(F("EdoPrueba"), logNoticia);
      break;
    case estadoError:
      log(F("EdoError"), logNoticia);
      break;
    case estadoInicio:
      // Arranque inicial del microcontrolador
      // Inicialización básica del sistema
      break;
    case estadoConfiguracion:
      log(F("EdoConfiguracion"), logNoticia);
      break;
    case estadoEspera:
      log(F("EdoEspera"), logNoticia);
      break;
    case estadoMedicion:
      numSensorActual = 1;
      log(F("EdoMedicion"), logNoticia);
      break;
    default:
      log(F("Estado no valido"), logError);
      break;
  }
  Estado = sigEstado;
}


/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoPrueba() {
  // Esperar 5 segundos mostrando la pantalla de inicio
  if (millis() - tiempoAnt > 2000) {
    tiempoAnt = millis();
    //TODO: CambiarEstado(estadoEspera);
  }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoError() {
  // Se mantiene en este estado
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoDesconectado() {
  // Esperar 5 segundos mostrando la pantalla de inicio
  if (millis() - tiempoAnt > 5000) {
    tiempoAnt = millis();
    // TODO: CambiarEstado(estadoPrueba);
  }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoInicio() {
  Serie.begin(Serial_bps);
  /****SI ES DIFERENTE EL PUERTO DEL LOG***/
  /* Serial_bps.begin(SerialLog_bps);*/
  A1Informacion();
  A1ConfGeneral();
  A2ConfLog();
  CambiarEstado(estadoConfiguracion);
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoConfiguracion() {
  M1DHTConf();
  // Leer Datos de EEPROM
  CambiarEstado(estadoMedicion);
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoEspera() {
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoMedicion() {
  // Realiza esta tarea cada 10 segundos
  if (millis() - tiempoAnt > 10000) {
    log(F("(DHT)Tomando datos sensor"), numSensorActual, logDebug);
    float t = M1LeerTemperatura(numSensorActual);
    float h = M1LeerHumedad(numSensorActual);
    // Verifica si se hizo la lectura correcta
    if (isnan(h) || isnan(t))
      log(F("(DHT)Error en Lectura de Sensor DHT "), numSensorActual, logError);
    else
    {
      if (h != -1 || t != -1)
      {
        // Se imprime el resultado de los valores
        Serie.print("#S");
        Serie.print(numSensorActual);
        Serie.print(",");
        Serie.print(t);
        Serie.print(",");
        Serie.println(h);
      }
    }
    numSensorActual++;
    if(numSensorActual>totalSensoresDHT){
      numSensorActual=1;
      tiempoAnt = millis();
    }      
  }
}
