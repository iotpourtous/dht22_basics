#ifndef commandManager_h
#define commandManager_h

#include "dht22Var.h"

String commands(String command)
{
  if(command.substring(0,2).equals("<" + String(DHT22_SENSOR_ID))){
    return dht.writeCommand(command.substring(2));
  } else if(command.substring(0,2).equals(">" + String(DHT22_SENSOR_ID))){
    return dht.readCommand(command.substring(2));
  }
  return "Commande inexistante";
}

void commandsFromSerial()
{
    if(Serial.available()){
      String command = Serial.readStringUntil('\n');
      Serial.println(commands(command));
    }
}

void commandsFromBT()
{
  if (SerialBT.available() > 0)
  {
    char readData[MAX_COMMAND_SIZE];

    size_t bytesReceived = SerialBT.readBytesUntil('\n', readData, MAX_COMMAND_SIZE);
    if (bytesReceived > 0)
    {
      SerialBT.println(commands(readData));
    }
  }
}

#endif