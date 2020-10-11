#include "stationMeteoDef.h"
#include "stationMeteoVar.h"
#include "myDHT.h"

dhtclass::dhtclass()
{
}

void dhtclass::InitDHT()
{
    Serial.println(F("------------------------------"));
    Serial.println(F("- Début initialisation DHT22 -"));
    dhtUnified->begin();
    dhtUnified->temperature().getSensor(&sensor);
    sensorDelay = sensor.min_delay / 1000;
    Serial.print(F("- Délai calculé : "));
    Serial.print(sensorDelay);
    Serial.println(F("ms     -"));
    Serial.println(F("- DHT22 Initialisé           -"));
    Serial.println(F("------------------------------"));
}

float dhtclass::ReadTemperature()
{
    dhtUnified->temperature().getEvent(&event);
    float temperature = event.temperature;
    temperature += (temperatureMode == TCELCIUS) ? temperatureCelciusOffset : temperatureFahrenheitOffset;
    return temperature;
}

float dhtclass::ReadHumidity()
{
    dhtUnified->humidity().getEvent(&event);
    return event.relative_humidity + humidityOffset;
}

dhtclass myDHT = dhtclass();
