#include <Arduino.h>
#include <myDHT.h>

#include "stationMeteoDef.h"

MyDHT myDHT(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  myDHT.InitDHT();
}

void loop()
{
  delay(myDHT.SensorDelay());

  float currentTemperature = myDHT.ReadTemperature();
  if (isnan(currentTemperature))
  {
    Serial.println(F("Error reading temperature!"));
  }
  else
  {
    Serial.print(F("Temperature: "));
    Serial.print(currentTemperature);
    Serial.println(F("°C"));
  }

  float currentHumidity = myDHT.ReadHumidity();
  if (isnan(currentHumidity))
  {
    Serial.println(F("Error reading humidity!"));
  }
  else
  {
    Serial.print(F("Humidity: "));
    Serial.print(currentHumidity);
    Serial.println(F("%"));
  }
}