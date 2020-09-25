/******************************************************************************/
/******************** MÓDULO DE TEMPERATURA Y HUMEDAD DHT *********************/
/******************************************************************************/
/* Este módulo se conecta a el sensor de temperatura y humedad
  /******************************************************************************/

/******************************************************************************/
/******************** TERMINALES USADAS POR EL MÓDULO DHT *********************/
/******************************************************************************/
const int DHTPIN1 = 2;
const int DHTPIN2 = 3;
const int DHTPIN3 = 4;
const int DHTPIN4 = 5;
const int DHTPIN5 = 6;

/******************************************************************************/
/************** VARIABLES GLOBALES PARA LA CONEXIÓN POR DEFECTO ***************/
/******************************************************************************/
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);
DHT dht4(DHTPIN4, DHTTYPE);
DHT dht5(DHTPIN5, DHTTYPE);
// Variable global que indica que sensor se esta usando actualmente
int numSensorActual;
// Variable global que indica cuantos sensores se van a utilizar
int totalSensoresDHT;

/******************************************************************************/
/*********************** CONFIGURACIÓN INICIAL DEL MÓDULO *********************/
/******************************************************************************/
void M1DHTConf() {
  // Configuramos los sensores usados
  log(F("(DHT)Configurando"), logInfo);
  totalSensoresDHT=3;
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
  dht5.begin();
}

void M1Info() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht1.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht1.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    log(F("(DHT)Failed to read from DHT sensor!"), logError);
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht1.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht1.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

float M1LeerTemperatura(int NumeroSensor) {
  switch (NumeroSensor)
  {
    case 1:
      return dht1.readHumidity();
    case 2:
      return dht2.readHumidity();
    case 3:
      return dht3.readHumidity();
    case 4:
      return dht4.readHumidity();
    case 5:
      return dht5.readHumidity();
      break;
    default:
      log(F("(DHT)Sensor no definido!"), logError);
      return -1;
  }
}

float M1LeerHumedad(int NumeroSensor) {
  switch (NumeroSensor)
  {
    case 1:
      return dht1.readTemperature();
    case 2:
      return dht2.readTemperature();
    case 3:
      return dht3.readTemperature();
    case 4:
      return dht4.readTemperature();
    case 5:
      return dht5.readTemperature();
      break;
    default:
      log(F("(DHT)Sensor no definido!"), logError);
      return -1;
  }
}
