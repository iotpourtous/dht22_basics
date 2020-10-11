#include <Arduino.h>

#include "stationMeteoDef.h"
#include "stationMeteoVar.h"
#include "myDHT.h"

void setup()
{
  Serial.begin(115200);
  myDHT.InitDHT();
}

void loop()
{

  delay(sensorDelay);

  currentTemperature = myDHT.ReadTemperature();
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

  currentHumidity = myDHT.ReadHumidity();
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