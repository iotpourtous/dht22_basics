#include <Arduino.h>

#include "dht22Var.h"
#include "commandManager.h"

void setup()
{
  Serial.begin(SERIAL_BAUD);
  dht.begin();
  SerialBT.begin("789789789798");

}

void loop()
{
  commandsFromSerial();
  commandsFromBT();
  
  Serial.println("currentTemperature : " + String(dht.temperature()) + "°C");
  Serial.println("currentHumidity : " + String(dht.humidity()) + "%");
  
  delay(dht.delay());
}