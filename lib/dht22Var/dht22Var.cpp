#include <MyDHT.h>
#include "dht22Def.h"

MyDHT *dht = new MyDHT(DHTPIN, DHTTYPE);

float currentTemperature;
float currentHumidity;