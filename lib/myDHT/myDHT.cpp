#include <Adafruit_Sensor.h>

#include "myDHT.h"

MyDHT::MyDHT(uint8_t pin, uint8_t type)
{
    dhtUnified = new DHT_Unified(pin, type);
}

void MyDHT::begin(uint8_t temperatureType, float temperatureCelciusOffset, float temperatureFahrenheitOffset, float humidityOffset)
{
    dhtUnified->begin();
    this->temperatureType = temperature_type_t(temperatureType);
    this->temperatureCelciusOffset = temperatureCelciusOffset;
    this->temperatureFahrenheitOffset = temperatureFahrenheitOffset;
    this->humidityOffset = humidityOffset;
}

float MyDHT::getCurrentTemperatureFromSensor()
{
    dhtUnified->temperature().getEvent(&event);
    return event.temperature;
}

uint32_t MyDHT::sensorDelay()
{
    dhtUnified->temperature().getSensor(&sensor);
    return sensor.min_delay / 1000;
}

float MyDHT::getCurrentHumidityFromSensor()
{
    dhtUnified->humidity().getEvent(&event);
    return event.relative_humidity;
}

float MyDHT::temperature()
{
    return (temperatureType == TFAHRENHEIT) ? temperatureFahrenheit() : getCurrentTemperatureFromSensor() + temperatureCelciusOffset;
}

float MyDHT::temperatureFahrenheit()
{
    return 1.8 * getCurrentTemperatureFromSensor() + 32 + temperatureFahrenheitOffset;
}

float MyDHT::humidity()
{
    return getCurrentHumidityFromSensor() + humidityOffset;
}
