#include "dht22Var.h"
#include "writeCommands.h"
#include "readCommands.h"
#include <iostream>
#include <exception>

using namespace std;

void writeTemperatureOffset(float temperatureOffset)
{
  dht->temperatureOffset(temperatureOffset);
  readTemperatureOffset();
}

void writeHumidityOffset(float humidityOffset)
{
  dht->humidityOffset(humidityOffset);
  readHumidityOffset();
}