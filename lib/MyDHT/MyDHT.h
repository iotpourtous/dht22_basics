#ifndef myDHT_h
#define myDHT_h

#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <MoyenneFlottante.h>

class MyDHT : public DHT_Unified
{
private:
  typedef enum
  {
    TCELCIUS = (0),
    TFAHRENHEIT = (1)
  } temperature_type_t;

  float _celciusOffset = 0.0;
  float _fahrenheitOffset = 0.0;
  float _humidityOffset = 0.0;

  temperature_type_t _temperatureType = TCELCIUS;

  float _temperatureFromEvent();
  float _humidityFromEvent();

  MoyenneFlottante _mfT;
  MoyenneFlottante _mfH;

public:
  MyDHT(uint8_t pin, uint8_t type, uint8_t count = 6,
         int32_t tempSensorId = -1, int32_t humiditySensorId = -1);
  float celciusOffset() { return _celciusOffset; }
  void celciusOffset(float celciusOffset) { _celciusOffset = celciusOffset; }
  float fahrenheitOffset() { return _fahrenheitOffset; }
  void fahrenheitOffset(float fahrenheitOffset) { _fahrenheitOffset = fahrenheitOffset; }
  float humidityOffset() { return _humidityOffset; }
  void humidityOffset(float humidityOffset) { _humidityOffset = humidityOffset; }
  void toFahrenheit() { _temperatureType = TFAHRENHEIT; }
  void toCelcius() { _temperatureType = TCELCIUS; }
  virtual float temperature();
  float averageTemperature() { return _mfT.moyenne(); }
  virtual float humidity();
  float averageHumidity() { return _mfH.moyenne(); }
  int32_t delay();
};

extern MyDHT myDHT;

#endif