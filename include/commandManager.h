#ifndef commandManager_h
#define commandManager_h

#include "dht22Def.h"

void commands()
{
  if (Serial.available() > 0)
  {
    size_t instructionMaxLength = 10;
    char readData[instructionMaxLength + 1];

    size_t bytesReceived = Serial.readBytesUntil('\n', readData, instructionMaxLength);
    if (bytesReceived > 0)
    {
      switch (readData[0])
      {
      case '<':
        if (readData[1] == '1')
        {
          char subbuff[8];
          memcpy(subbuff, &readData[2], 8);
          dht->writeCommand(1, subbuff);
        }
        else
        {
          throw "Commande inexistante";
        }
        break;
      case '>':
        if (readData[1] == '1')
        {

          char subbuff[8];
          memcpy(subbuff, &readData[2], 8);
          dht->readCommand(1, subbuff);
        }
        else
        {
          throw "Commande inexistante";
        }
        break;
      default:
        throw "Commande inexistante";
      }
    }
  }
}

#endif