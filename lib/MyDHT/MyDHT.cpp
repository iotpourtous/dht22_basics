#include "MyDHT.h"

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
    return event.temperature;
}

float MyDHT::_humidityFromEvent()
{
    sensors_event_t event;
    DHT_Unified::humidity().getEvent(&event);
    return event.relative_humidity;
}

int32_t MyDHT::delay()
{
    sensor_t sensor;
    DHT_Unified::temperature().getSensor(&sensor);
    return sensor.min_delay / 1000;
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