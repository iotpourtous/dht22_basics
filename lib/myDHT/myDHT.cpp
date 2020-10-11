#include <Adafruit_Sensor.h>

#include "myDHT.h"

MyDHT::MyDHT(uint8_t pin, uint8_t type)
{
    dhtUnified = new DHT_Unified(pin, type);
}

MyDHT::MyDHT(uint8_t pin, uint8_t type, float temperatureOffset, float humidityOffset)
{
    dhtUnified = new DHT_Unified(pin, type);
    this->temperatureOffset = temperatureOffset;
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
    currentTemperature = event.temperature + temperatureOffset;
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
