#include <Arduino.h>

#include "dht22Var.h"
#include "commandManager.h"

void setup()
{
  Serial.begin(SERIAL_BAUD);
  dht->begin();
}

String formatFloat(float value)
{
  char retour[] = "--";
  if (!isnan(value))
  {
    sprintf(retour, "%.1f", value);
  }
  return String(retour);
}

void loop()
{
  commands();
  Serial.println("currentTemperature : " + formatFloat(dht->temperature()) + "°C");
  Serial.println("currentHumidity : " + formatFloat(dht->humidity()) + "%");
  delay(dht->delay());
}