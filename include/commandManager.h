#ifndef commandManager_h
#define commandManager_h

#include "dht22Var.h"

String commands(String command)
{
  if (command.startsWith((String)DHT22_SENSOR_ID))
  {
    return dht.executeCommand(command.substring(1));
  }
  return "Commande inexistante";
}

void commandsFromSerial()
{
  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    Serial.println(commands(command));
  }
}

void commandsFromBT()
{
  if (SerialBT.available() > 0)
  {
    String command = SerialBT.readStringUntil('\n');
    SerialBT.println(commands(command));
  }
}

#endif