#include <Arduino.h>
#include <MyDHT.h>

#include "stationMeteoDef.h"

MyDHT myDHT(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  myDHT.begin();
}

void loop()
{
  delay(myDHT.sensorDelay());

  float currentTemperature = myDHT.temperature();
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

  float currentHumidity = myDHT.humidity();
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