#include <Arduino.h>
#include <MyDHT.h>
#include <MoyenneFlottante.h>
#include "stationMeteoDef.h"

MyDHT dht(DHTPIN, DHTTYPE);

MoyenneFlottante mfT;
MoyenneFlottante mfH;

float readTemperature()
{
  float currentTemperature = dht.temperature();
  if (isnan(currentTemperature))
  {
    Serial.println(F("Error reading temperature!"));
  }
  else
  {

    mfT.populate(currentTemperature);
    Serial.print(F("Temperature: "));
    Serial.print(currentTemperature);
    Serial.println(F("°C"));
  }
  return currentTemperature;
}

float readAverageTemperature()
{
  float averageTemperature = mfT.moyenne();
  if (isnan(averageTemperature))
  {
    Serial.println(F("Error reading averageTemperature!"));
  }
  else
  {
    Serial.print(F("averageTemperature: "));
    Serial.print(averageTemperature);
    Serial.println(F("°C"));
  }
  return averageTemperature;
}

float readHumidity()
{
  float currentHumidity = dht.humidity();
  if (isnan(currentHumidity))
  {
    Serial.println(F("Error reading humidity!"));
  }
  else
  {
    mfH.populate(currentHumidity);
    Serial.print(F("Humidity: "));
    Serial.print(currentHumidity);
    Serial.println(F("%"));
  }
  return currentHumidity;
}

float readAverageHumidity()
{
  float averageHumidity = mfH.moyenne();
  if (isnan(averageHumidity))
  {
    Serial.println(F("Error reading averageHumidity!"));
  }
  else
  {
    Serial.print(F("averageHumidity: "));
    Serial.print(averageHumidity);
    Serial.println(F("%"));
  }
  return averageHumidity;
}

void ParseCmd2()
{
  while (Serial.available())
  {
    if (Serial.available() > 0)
    {
      size_t instructionMaxLength = 10;
      char readData[instructionMaxLength + 1] = {'\0'};
      size_t bytesReceived;

      bytesReceived = Serial.readBytesUntil('\n', readData, instructionMaxLength);
      if (DEBUG)
      {
        Serial.print("message : ");
        Serial.println(readData);
        Serial.print("longueur message : ");
        Serial.println(bytesReceived);
      }
      if (bytesReceived <= instructionMaxLength)
      {
        switch (readData[0])
        {
        case 'S':
          if (readData[1] == '/')
          {
            if (readData[2] == 'T')
            {
              if (readData[3] == '/')
              {
                if (readData[4] == 'F')
                {
                  Serial.println(">>> Bascule en fahrenheit");
                  dht.toFahrenheit();
                }
                else if (readData[4] == 'C')
                {
                  Serial.println(">>> Bascule en celcius");
                  dht.toCelcius();
                }
                else
                {
                  Serial.println("commande inexistante6");
                }
              }
            }
            else
            {
              Serial.println("commande inexistante4");
            }
          }
          else
          {
            Serial.println("commande inexistante5");
          }
          break;
        case 'G':
          if (readData[1] == '/')
          {
            if (readData[2] == 'T')
            {
              //lecture de la température
              Serial.print(">>> Température : ");
              Serial.println(readTemperature());
            }
            else if (readData[2] == 'H')
            {
              //lecture de l'humidité
              Serial.print(F(">>> Humidité : "));
              Serial.println(readHumidity());
            }
            else
            {
              Serial.println("commande inexistante1");
            }
          }
          else
          {
            Serial.println("commande inexistante2");
          }
          break;
        default:
          Serial.println("commande inexistante3");
          break;
        }
      }
      else
      {
        Serial.println("Chaine top longue");
      }
    }
  }
}

void setup()
{
  Serial.begin(115200);
  dht.begin();
}

void loop()
{
  ParseCmd2();
  readTemperature();
  readAverageTemperature();
  readHumidity();
  readAverageHumidity();
  delay(dht.delay());
}