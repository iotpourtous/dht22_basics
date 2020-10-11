#include <Adafruit_Sensor.h>
#include <DHT_U.h>

#include "stationMeteoDef.h"

DHT_Unified *dhtUnified = new DHT_Unified(DHTPIN, DHTTYPE);

sensor_t sensor;
sensors_event_t event;

uint32_t sensorDelay;

int temperatureMode = TCELCIUS;

float temperatureFahrenheitOffset = 0.0;
float temperatureCelciusOffset = 0.0;
float humidityOffset = 0.0;

float currentTemperature;
float currentHumidity;