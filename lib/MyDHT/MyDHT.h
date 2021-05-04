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

  String READ_INFORMATIONS_COMMAND = "I";
  String READ_TEMPERATURE_SENSOR_INFORMATION_COMMAND = "TI";
  String READ_HUMIDITY_SENSOR_INFORMATION_COMMAND = "HI";
  String TEMPERATURE_OFFSET_COMMAND = "OT";
  String HUMIDITY_OFFSET_COMMAND = "OH";
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

  String readCommand(String command);
  String writeCommand(String command);
};

extern MyDHT myDHT;

#endif
