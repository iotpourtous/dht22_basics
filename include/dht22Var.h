#ifndef dht22Var_h
#define dht22Var_h

#include "dht22Def.h"
#include <MyDHT.h>

temperature_type_t temperatureType  = TCELCIUS;
float temperatureOffset = 0;  
float humidityOffset = 0;

MyDHT *dht = new MyDHT(DHTPIN, DHTTYPE, temperatureType, temperatureOffset, humidityOffset);

#endif