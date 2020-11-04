#include <Arduino.h>

#include "dht22Var.h"
#include "commandManager.h"

void setup()
{
  Serial.begin(115200);
  dht->begin();
}

void loop()
{
  commands();
  Serial.print("currentTemperature : ");
  Serial.print(dht->temperatureFormatted());
  Serial.println("°C");
  Serial.print("currentHumidity : ");
  Serial.print(dht->humidityFormatted());
  Serial.println("%");
  delay(dht->delay());
}