#ifndef dht22Var_h
#define dht22Var_h

#include <MyDHT.h>
#include "BluetoothSerial.h"
#include "dht22Def.h"

temperature_type_t temperatureType  = TCELCIUS;
float temperatureOffset = 0;  
float humidityOffset = 0;

MyDHT dht(DHTPIN, DHTTYPE, temperatureType, temperatureOffset, humidityOffset);

BluetoothSerial SerialBT;

#endif