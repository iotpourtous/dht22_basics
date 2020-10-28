#ifndef commandManager_h
#define commandManager_h

#include <iostream>
#include <exception>

#include "readCommands.h"
#include "writeCommands.h"

using namespace std;

void writeCommand(char *readData)
{
  if (readData[2] == 'O')
  {
    if (readData[3] == 'T')
    {
      char subbuff[5];
      memcpy(subbuff, &readData[4], 5);
      writeTemperatureOffset(atof(subbuff));
    }
    else if (readData[3] == 'H')
    {
      char subbuff[5];
      memcpy(subbuff, &readData[4], 5);
      writeHumidityOffset(atof(subbuff));
    }
    else
    {
      throw "Commande inexistante";
    }
  }
  else if (readData[2] == 'U')
  {
    if (readData[3] == 'C')
    {
      dht->toCelcius();
      readUnity();
    }
    else if (readData[3] == 'F')
    {
      dht->toFahrenheit();
      readUnity();
    }
    else
    {
      throw "Commande inexistante";
    }
  }
  else
  {
    throw "Commande inexistante";
  }
}

void readCommand(char *readData)
{
  switch (readData[2])
  {
  case 'C':
    readCommandList();
    break;
  case 'T':
    readTemperature();
    break;
  case 'H':
    readHumidity();
    break;
  case 'O':
    if (readData[3] == 'T')
    {
      readTemperatureOffset();
    }
    else if (readData[3] == 'H')
    {
      readHumidityOffset();
    }
    else
    {
      throw "Commande inexistante";
    }
    break;
  case 'U':
    readUnity();
    break;
  case 'I':
    if (readData[3] == 'T')
    {
      readTemperatureSensorInfo();
    }
    else if (readData[3] == 'H')
    {
      readHumiditySensorInfo();
    }
    else
    {
      throw "Commande inexistante";
    }
    break;
  default:
    throw "Commande inexistante";
    break;
  }
}

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
          writeCommand(readData);
        }
        else
        {
          throw "Commande inexistante";
        }
        break;
      case '>':
        if (readData[1] == '1')
        {
          readCommand(readData);
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