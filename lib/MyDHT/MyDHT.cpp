#include "MyDHT.h"
#include <iostream>
#include <exception>

using namespace std;

MyDHT::MyDHT(
    uint8_t pin,
    uint8_t type,
    temperature_type_t temperatureType,
    float temperatureOffset,
    float humidityOffset) : DHT_Unified(pin, type),
                            _temperatureType(temperatureType),
                            _temperatureOffset(temperatureOffset),
                            _humidityOffset(humidityOffset) {}

float MyDHT::_temperatureFromEvent()
{
    sensors_event_t event;
    DHT_Unified::temperature().getEvent(&event);
    float t = event.temperature;
    if (isnan(t))
    {
        throw "Erreur lecture température";
    }
    return t;
}

float MyDHT::_humidityFromEvent()
{
    sensors_event_t event;
    DHT_Unified::humidity().getEvent(&event);
    float h = event.relative_humidity;
    if (isnan(h))
    {
        throw "Erreur lecture humidité";
    }
    return h;
}

sensor_t MyDHT::temperatureSensor()
{
    sensor_t sensor;
    DHT_Unified::temperature().getSensor(&sensor);
    return sensor;
}

sensor_t MyDHT::humiditySensor()
{
    sensor_t sensor;
    DHT_Unified::humidity().getSensor(&sensor);
    return sensor;
}


int32_t MyDHT::delay()
{
    return temperatureSensor().min_delay / 1000;
}

float MyDHT::temperature()
{
    float t = _temperatureFromEvent();
    return ((_temperatureType == TFAHRENHEIT) ? 1.8 * t + 32 : t) + _temperatureOffset;
}

float MyDHT::humidity()
{
    return _humidityFromEvent() + _humidityOffset;
}