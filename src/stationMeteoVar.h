#ifndef stationMeteoVar_h
#define stationMeteoVar_h

#include <Adafruit_Sensor.h>
#include <DHT_U.h>

extern DHT_Unified *dhtUnified;

extern sensor_t sensor;
extern sensors_event_t event;

extern uint32_t sensorDelay;

extern int temperatureMode;

extern float temperatureFahrenheitOffset;
extern float temperatureCelciusOffset;
extern float humidityOffset;

extern float currentTemperature;
extern float currentHumidity;

#endif
