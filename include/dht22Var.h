#ifndef dht22Var_h
#define dht22Var_h

#include <MyDHT.h>
#include "BluetoothSerial.h"
#include "dht22Def.h"

MyDHT dht(DHTPIN, DHTTYPE, DHT22_SENSOR_ID);

BluetoothSerial SerialBT;

#endif