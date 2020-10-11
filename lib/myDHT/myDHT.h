#ifndef myDHT_h
#define myDHT_h

#include <Adafruit_Sensor.h>
#include <DHT_U.h>

class MyDHT
{
private:
    DHT_Unified *dhtUnified;

    sensor_t sensor;
    sensors_event_t event;

    float currentTemperature;
    float currentHumidity;

    uint32_t sensorDelay;

    float temperatureFahrenheitOffset = 0.0;
    float temperatureCelciusOffset = 0.0;
    float humidityOffset = 0.0;

public:
    MyDHT(uint8_t pin, uint8_t type);
    void InitDHT();
    float ReadTemperature();
    float ReadHumidity();
    uint32_t SensorDelay();
};

extern MyDHT myDHT;

#endif
