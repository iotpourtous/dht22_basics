#include <Arduino.h>

#include "dht22Def.h"
#include "dht22Var.h"
#include "commandManager.h"
#include <iostream>
#include <exception>

using namespace std;

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
     //currentTemperature = dht->temperature();
    // cout << "currentTemperature : " << currentTemperature << "°C" << endl;
    // currentHumidity = dht->humidity();
    // cout << "currentHumidity : " << currentHumidity << "%" << endl;
  }
  catch (const char *msg)
  {
    cerr << "Une erreur est survenue : " << msg << endl;
  }
  delay(dht->delay());
}