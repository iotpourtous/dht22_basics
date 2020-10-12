#ifndef myDHT_h
#define myDHT_h

#include <Adafruit_Sensor.h>
#include <DHT_U.h>

/** Sensor types */
typedef enum
{
    TCELCIUS = (0),
    TFAHRENHEIT = (1)
} temperature_type_t;

class MyDHT
{
private:
    DHT_Unified *dhtUnified;

    sensor_t sensor;
    sensors_event_t event;

    temperature_type_t temperatureType = TCELCIUS;

    float currentTemperature;
    float currentHumidity;

    uint32_t sensorDelay;

    float temperatureCelciusOffset = 0.0;
    float temperatureFahrenheitOffset = 0.0;
    float humidityOffset = 0.0;

public:
    MyDHT(uint8_t pin, uint8_t type);
    MyDHT(uint8_t pin, uint8_t type, uint8_t temperatureType);
    MyDHT(uint8_t pin, uint8_t type, float temperatureCelciusOffset, float temperatureFahrenheitOffset, float humidityOffset);
    void InitDHT();
    float ReadTemperature();
    float ReadHumidity();
    uint32_t SensorDelay();
};

extern MyDHT myDHT;

#endif
