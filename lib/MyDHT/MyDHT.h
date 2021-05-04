#ifndef myDHT_h
#define myDHT_h

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>

class MyDHT : public DHT_Unified
{
private:
  int _sensorId;
  float _temperatureOffset;
  float _humidityOffset;

  sensor_t _temperatureSensor;
  sensor_t _humiditySensor;

  String READ_INFORMATIONS_COMMAND = "i";
  String READ_TEMPERATURE_SENSOR_INFORMATION_COMMAND = "it";
  String READ_HUMIDITY_SENSOR_INFORMATION_COMMAND = "ih";
  String TEMPERATURE_OFFSET_COMMAND = "to";
  String HUMIDITY_OFFSET_COMMAND = "ho";
  String LIST_COMMAND = "C";

public:
  MyDHT(
      int pin,
      int type,
      int sensorId);

  float temperatureOffset() { return _temperatureOffset; }
  void temperatureOffset(float temperatureOffset) { _temperatureOffset = temperatureOffset; }
  float humidityOffset() { return _humidityOffset; }
  void humidityOffset(float humidityOffset) { _humidityOffset = humidityOffset; }

  virtual float temperature(void);
  virtual float humidity(void);

  int32_t delay();

  String executeCommand(String command);
};

extern MyDHT myDHT;

#endif
