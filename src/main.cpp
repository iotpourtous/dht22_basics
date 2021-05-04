#include <Arduino.h>

#include "dht22Var.h"
#include "commandManager.h"

void setup()
{
  Serial.begin(SERIAL_BAUD);
  dht.begin();
  SerialBT.begin(BT_ACCESS_POINT);
}

void loop()
{
  commandsFromSerial();
  commandsFromBT();
  if (DEBUG)
  {
    Serial.println("currentTemperature : " + String(dht.temperature()) + "°C");
    Serial.println("currentHumidity : " + String(dht.humidity()) + "%");
  }
  delay(dht.delay());
}