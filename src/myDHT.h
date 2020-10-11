#ifndef myDHT_h
#define myDHT_h

class dhtclass
{
public:
    dhtclass();
    void InitDHT();
    float ReadTemperature();
    float ReadHumidity();
};

extern dhtclass myDHT;

#endif
