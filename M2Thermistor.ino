/******************************************************************************/
/***************** MÓDULO DE TEMPERATURA Y HUMEDAD TERMISTOR ******************/
/******************************************************************************/
/* Este módulo se conecta a el sensor de temperatura y humedad
  /******************************************************************************/

/******************************************************************************/
/******************** TERMINALES USADAS POR EL MÓDULO DHT *********************/
/******************************************************************************/
const int PIN_NTC1 = A1;
const int PIN_NTC2 = A2;
const int PIN_NTC3 = A3;

// Variable global que indica cuantos sensores se van a utilizar
int totalTermistores;

THERMISTOR thermistor1(PIN_NTC1,        // Analog pin
                       10000,          // Nominal resistance at 25 ºC
                       3950,           // thermistor's beta coefficient
                       10000);         // Value of the series resistor

THERMISTOR thermistor2(PIN_NTC2,        // Analog pin
                       10000,          // Nominal resistance at 25 ºC
                       3950,           // thermistor's beta coefficient
                       10000);         // Value of the series resistor

THERMISTOR thermistor3(PIN_NTC3,        // Analog pin
                       10000,          // Nominal resistance at 25 ºC
                       3950,           // thermistor's beta coefficient
                       10000);         // Value of the series resistor


/******************************************************************************/
/*********************** CONFIGURACIÓN INICIAL DEL MÓDULO *********************/
/******************************************************************************/
void M1TermistorConf() {
  // Configuramos los sensores usados
  log(F("(Thermistor)Configurando"), logInfo);
  totalTermistores=3;
}

int LecturaTermistor(int numeroTermistor) {
  uint16_t temp;
  switch (numeroTermistor)
  {
    case 1:
      temp = thermistor1.read();  // Read temperature
      break;
    case 2:
      temp = thermistor2.read();
      break;
    case 3:
      temp = thermistor3.read();
      break;
    default:
      temp = 0;
  }
  return temp;
}
