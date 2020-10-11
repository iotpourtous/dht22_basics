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

    float temperatureOffset = 0.0;
    float humidityOffset = 0.0;

public:
    MyDHT(uint8_t pin, uint8_t type);
    MyDHT(uint8_t pin, uint8_t type, float temperatureOffset, float humidityOffset);
    void InitDHT();
    float ReadTemperature();
    float ReadHumidity();
    uint32_t SensorDelay();
};

extern MyDHT myDHT;

#endif
