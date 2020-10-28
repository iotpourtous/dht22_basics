#include "dht22Var.h"
#include "readCommands.h"
#include <iostream>
#include <exception>

using namespace std;

void readCommandList()
{
  cout << "------------------------------------" << endl;
  cout << "Liste des commandes" << endl;
  cout << "'>1C' : Liste des commandes" << endl;
  cout << "'>1T' : Lit la température" << endl;
  cout << "'>1OT' : Lit l'offset de température" << endl;
  cout << "'>1OH' : Lit l'offset d'humidité" << endl;
  cout << "'>1U' : Lit l'unité de température" << endl;
  cout << "'>1IT' : Lit les infos du capteur de température" << endl;
  cout << "'>1IH' : Lit les infos du capteur d'humidité" << endl;
  cout << "'<1OTXX.XX' : modifie l'offset de température" << endl;
  cout << "'<1OHXX.XX' : modifie l'offset d'humidité" << endl;
  cout << "'<1UC' : Change l'unité de température en Celcius" << endl;
  cout << "'<1UF' : Change l'unité de température en Fahrenheit" << endl;
  cout << "------------------------------------" << endl;
}

void readTemperature()
{
  cout << ">1T:" << dht->temperature() << "°C" << endl;
}

void readHumidity()
{
  cout << ">1H:" << dht->humidity() << "%" << endl;
}

void readTemperatureOffset()
{
  cout << ">1OT:" << dht->temperatureOffset() << "°C" << endl;
}

void readHumidityOffset()
{
  cout << ">1OT:" << dht->humidityOffset() << "%" << endl;
}

void readUnity()
{
  cout << ">1U:" << ((dht->temperatureType() == TCELCIUS) ? "CELCIUS" : "FAHRENHEIT") << endl;
}

void readTemperatureSensorInfo()
{
  sensor_t sensor = dht->temperatureSensor();
  cout << "------------------------------------" << endl;
  cout << "Capteur de température" << endl;
  cout << "Nom: " << sensor.name << endl;
  cout << "Version:  " << sensor.version << endl;
  cout << "Identifiant:   " << sensor.sensor_id << endl;
  cout << "Min Delay:   " << sensor.min_delay / 1000 << "Ms" << endl;
  cout << "Max Value:   " << sensor.max_value << "°C" << endl;
  cout << "Min Value:   " << sensor.min_value << "°C" << endl;
  cout << "Resolution:  " << sensor.resolution << "°C" << endl;
  cout << "------------------------------------" << endl;
}

void readHumiditySensorInfo()
{
  sensor_t sensor = dht->humiditySensor();
  cout << "------------------------------------" << endl;
  cout << "Humidity Sensor" << endl;
  cout << "Sensor Name: " << sensor.name << endl;
  cout << "Sensor Type: " << sensor.type << endl;
  cout << "Driver Ver:  " << sensor.version << endl;
  cout << "Unique ID:   " << sensor.sensor_id << endl;
  cout << "Min Delay:   " << sensor.min_delay / 1000 << "Ms" << endl;
  cout << "Max Value:   " << sensor.max_value << "%" << endl;
  cout << "Min Value:   " << sensor.min_value << "%" << endl;
  cout << "Resolution:  " << sensor.resolution << "%" << endl;
  cout << "------------------------------------" << endl;
}