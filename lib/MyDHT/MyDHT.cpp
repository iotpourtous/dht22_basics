#include "MyDHT.h"

MyDHT::MyDHT(uint8_t pin, uint8_t type, uint8_t count,
               int32_t tempSensorId, int32_t humiditySensorId) : DHT_Unified(pin, type, count, tempSensorId, humiditySensorId) {}

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

    if (_temperatureType == TFAHRENHEIT)
    {
        t = 1.8 * t + 32 + _fahrenheitOffset;
    }
    else
    {
        t += _celciusOffset;
    }
   _mfT.populate(t);
    return t;
}

float MyDHT::humidity()
{
    float h = _humidityFromEvent() + _humidityOffset;
    _mfH.populate(h);
    return h;
}