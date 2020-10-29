#include <Arduino.h>

#include "dht22Var.h"
#include "commandManager.h"

void setup()
{
  Serial.begin(115200);
  dht->begin();
}

void loop()
{
  try
  {
    commands();
    cout << "currentTemperature : " << dht->temperature() << "°C" << endl;
    cout << "currentHumidity : " << dht->humidity() << "%" << endl;
  }
  catch (const char *msg)
  {
    cerr << "Une erreur est survenue : " << msg << endl;
  }
  delay(dht->delay());
}