#ifndef MyDHT_h
#define MyDHT_h

#include <Adafruit_Sensor.h>
#include <DHT_U.h>

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

    temperature_type_t temperatureType;

    float temperatureCelciusOffset;
    float temperatureFahrenheitOffset;
    float humidityOffset;

    float getCurrentTemperatureFromSensor();
    float getCurrentHumidityFromSensor();
    float temperatureFahrenheit();

public:
    MyDHT(uint8_t pin, uint8_t type);
    void begin(uint8_t = TCELCIUS, float = 0, float = 0, float = 0);
    float temperature();
    float humidity();
    uint32_t sensorDelay();
};

extern MyDHT myDHT;

#endif
