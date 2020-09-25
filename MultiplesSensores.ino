/******************************************************************************/
/**************************** NOMBRE DEL PROYECTO *****************************/
/******************************************************************************/
/** Adquisición de hasta 5 sensores de temperatura y Humedad, se conecta     **/
/** con el módulo Bluetooth en las terminales de Puerto Serial de Arduino Rx,**/
/** Tx. Y se visualizan los datos en la aplicación en Android programada en  **/
/** AppInventor: http://ai2.appinventor.mit.edu/?galleryId=4537088305004544  **/
/**   Placa Hardware:      Arduino UNO                                       **/
/**   Versión IDE Arduino: 1.8.13                                            **/
/******************************************************************************/
/** Version 0.1.20200924                                                     **/
/**                                                                          **/
/** Última revisión:                                                         **/
/** 2020/09/24 Augusto - Se establece el programa principal                  **/
/******************************************************************************/

/***************************INFORMACIÓN DEL AUTÓMATA***************************/
const String modelo="MultDHTV0.1.1";
const String firmware="0.20.0924";
const String numSerie="000001";

/******************************************************************************/
/******************* DECLARACIÓN DE LIBRERÍAS DEL AUTOMATA ********************/
/******************************************************************************/
/** Estas son las librerias que se usan, los módulos que la utilizan y las   **/
/** versiones de cada una ordenadas por prioridad y utilización              **/
/**************************************||**************************************/
// Librería con el módulo Temperatura y Humedad DHT
// https://github.com/adafruit/DHT-sensor-library
#include "DHT.h"          // 1.3.10 - M1DHT
// Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

/******************************************************************************/
// Definimos puerto serial para Comunicación
#define Serie Serial
#define Serial_bps 9600

// Definimos puerto serial para LOG
#define SerialLog Serial
#define SerialLog_bps 9600

/*****************************DEFINICIÓN DE ESTADOS****************************/
const int estadoPrueba=-3;        // Estado usado para pruebas
const int estadoError=-2;         // Estado usado para pruebas
const int estadoDesconectado = -1;// Estado de puerto serial desconectad
// Módulo Adquisición de temperatura - Humedad
const int estadoInicio = 0;// Estado inicial
const int estadoConfiguracion = 1;// Estado de configuración de módulos
const int estadoEspera = 2;// Estado inicial
const int estadoMedicion = 3;// Estado inicial
/******************************************************************************/
int Estado;

void setup() {
  CambiarEstado(estadoInicio);
}

void loop() {
  LeerIndicaciones();  
  switch (Estado) {
    case estadoPrueba:
      EstadoPrueba();
      break;
    case estadoError:
      EstadoError();
      break;
    case estadoDesconectado:
      EstadoDesconectado();
      break;
    case estadoInicio:
      EstadoInicio();
      break;
    case estadoConfiguracion:
      EstadoConfiguracion();
      break;
    case estadoEspera:
      EstadoEspera();
      break;
    case estadoMedicion:
      EstadoMedicion();
      break;
    default:
      EstadoError();
      break;
  }
}
