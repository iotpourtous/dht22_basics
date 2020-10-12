#include <Adafruit_Sensor.h>

#include "myDHT.h"

MyDHT::MyDHT(uint8_t pin, uint8_t type)
{
    dhtUnified = new DHT_Unified(pin, type);
}

MyDHT::MyDHT(uint8_t pin, uint8_t type, uint8_t temperatureType)
{
    dhtUnified = new DHT_Unified(pin, type);
    this->temperatureType = temperature_type_t(temperatureType);
}

MyDHT::MyDHT(uint8_t pin, uint8_t type, float temperatureCelciusOffset, float temperatureFahrenheitOffset, float humidityOffset)
{
    dhtUnified = new DHT_Unified(pin, type);
    this->temperatureCelciusOffset = temperatureCelciusOffset;
    this->temperatureFahrenheitOffset = temperatureFahrenheitOffset;
    this->humidityOffset = humidityOffset;
}

void MyDHT::InitDHT()
{
    dhtUnified->begin();
    dhtUnified->temperature().getSensor(&sensor);
    sensorDelay = sensor.min_delay / 1000;
}

float MyDHT::ReadTemperature()
{
    dhtUnified->temperature().getEvent(&event);
    currentTemperature = event.temperature;
    if (temperatureType == TFAHRENHEIT)
    {
        currentTemperature = 1.8 * currentTemperature + 32 + temperatureFahrenheitOffset;
    }
    else
    {
        currentTemperature = event.temperature + temperatureCelciusOffset;
    }
    return currentTemperature;
}

float MyDHT::ReadHumidity()
{
    dhtUnified->humidity().getEvent(&event);
    currentHumidity = event.relative_humidity + humidityOffset;
    return currentHumidity;
}

uint32_t MyDHT::SensorDelay()
{
    return sensorDelay;
}
