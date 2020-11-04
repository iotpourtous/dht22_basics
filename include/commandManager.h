#ifndef commandManager_h
#define commandManager_h

#include "dht22Def.h"

void commands()
{
  if (Serial.available() > 0)
  {
    char readData[MAX_COMMAND_SIZE];

    size_t bytesReceived = Serial.readBytesUntil('\n', readData, MAX_COMMAND_SIZE);
    if (bytesReceived > 0)
    {
      String retour = "Commande inexistante";
      switch (readData[0])
      {
      case '<':
        if (readData[1] == DHT22_SENSOR_ID)
        {
          char subbuff[8];
          memcpy(subbuff, &readData[2], 8);
          retour = "<" + String(DHT22_SENSOR_ID) + dht->writeCommand(subbuff);
        }
        break;
      case '>':
        if (readData[1] == DHT22_SENSOR_ID)
        {
          char subbuff[8];
          memcpy(subbuff, &readData[2], 8);
          retour = ">" + String(DHT22_SENSOR_ID) + dht->readCommand(subbuff);
        }
        break;
      }
      Serial.println(retour);
    }
  }
}

#endif