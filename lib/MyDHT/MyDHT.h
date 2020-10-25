#ifndef myDHT_h
#define myDHT_h

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
  void toFahrenheit() { _temperatureType = TFAHRENHEIT; }
  void toCelcius() { _temperatureType = TCELCIUS; }
  virtual float temperature();
  virtual float humidity();
  int32_t delay();
};

extern MyDHT myDHT;

#endif