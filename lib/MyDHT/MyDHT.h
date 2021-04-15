#ifndef myDHT_h
#define myDHT_h

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>

typedef enum
{
  TCELCIUS = (0),
  TFAHRENHEIT = (1)
} temperature_type_t;

class MyDHT : public DHT_Unified
{
private:
  temperature_type_t _temperatureType;

  float _temperatureOffset;
  float _humidityOffset;

  float _temperatureFromEvent();
  float _humidityFromEvent();
  sensor_t _temperatureSensor();
  sensor_t _humiditySensor();

  String TEMPERATURE_OFFSET_COMMAND = "OT";
  String HUMIDITY_OFFSET_COMMAND = "OH";
  String CELCIUS_TEMPERATURE_COMMAND = "UC";
  String FAHRENHEIT_TEMPERATURE_COMMAND = "UF";
  String LIST_COMMAND = "C";

  boolean isNotIntValue(String data);

public:
  MyDHT(
      uint8_t pin,
      uint8_t type,
      temperature_type_t temperatureType = TCELCIUS,
      float temperatureOffset = 0.0,
      float humidityOffset = 0.0);

  float temperatureOffset() { return _temperatureOffset; }
  void temperatureOffset(float temperatureOffset) { _temperatureOffset = temperatureOffset; }
  float humidityOffset() { return _humidityOffset; }
  void humidityOffset(float humidityOffset) { _humidityOffset = humidityOffset; }

  temperature_type_t temperatureType() { return _temperatureType; }
  void toFahrenheit() { _temperatureType = TFAHRENHEIT; }
  void toCelcius() { _temperatureType = TCELCIUS; }

  virtual float temperature(void);
  virtual float humidity(void);

  int32_t delay();
  
  String readCommand(String command, int8_t sensorId);
  String writeCommand(String command);
};

extern MyDHT myDHT;

#endif
