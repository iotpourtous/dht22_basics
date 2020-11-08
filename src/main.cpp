#include <Arduino.h>

#include "dht22Var.h"
#include "format.h"
#include "commandManager.h"

void setup()
{
  Serial.begin(SERIAL_BAUD);
  dht->begin();
  SerialBT.begin("ESP32"); //Bluetooth device name

}

void loop()
{
  commandsFromSerial();
  commandsFromBT();
  Serial.println("currentTemperature : " + formatFloat(dht->temperature()) + "°C");
  Serial.println("currentHumidity : " + formatFloat(dht->humidity()) + "%");
  delay(dht->delay());
}