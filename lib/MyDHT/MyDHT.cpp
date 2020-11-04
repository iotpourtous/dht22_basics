#include "MyDHT.h"

MyDHT::MyDHT(
    uint8_t pin,
    uint8_t type,
    temperature_type_t temperatureType,
    float temperatureOffset,
    float humidityOffset) : DHT_Unified(pin, type),
                            _temperatureType(temperatureType),
                            _temperatureOffset(temperatureOffset),
                            _humidityOffset(humidityOffset) {}

float MyDHT::_temperatureFromEvent()
{
    sensors_event_t event;
    DHT_Unified::temperature().getEvent(&event);
    return event.temperature;
}

float MyDHT::_humidityFromEvent()
{
    sensors_event_t event;
    DHT_Unified::humidity().getEvent(&event);
    return event.relative_humidity;
}

sensor_t MyDHT::_temperatureSensor()
{
    sensor_t sensor;
    DHT_Unified::temperature().getSensor(&sensor);
    return sensor;
}

sensor_t MyDHT::_humiditySensor()
{
    sensor_t sensor;
    DHT_Unified::humidity().getSensor(&sensor);
    return sensor;
}

float MyDHT::temperature()
{
    float t = _temperatureFromEvent();
    return ((_temperatureType == TFAHRENHEIT) ? 1.8 * t + 32 : t) + _temperatureOffset;
}

String MyDHT::temperatureFormatted()
{
    if (isnan(temperature()))
    {
        return "--";
    }
    char temperatureFormatted[10];
    dtostrf(temperature(), 4, 2, temperatureFormatted);
    return temperatureFormatted;
}

float MyDHT::humidity()
{
    return _humidityFromEvent() + _humidityOffset;
}
String MyDHT::humidityFormatted()
{
    if (isnan(humidity()))
    {
        return "--";
    }
    char humidityFormatted[10];
    dtostrf(humidity(), 4, 2, humidityFormatted);
    return humidityFormatted;
}

int32_t MyDHT::delay()
{
    return _temperatureSensor().min_delay / 1000;
}

String MyDHT::writeCommand(char *readData)
{
    String retour = "Commande inexistante";
    switch (readData[0])
    {
    case 'O':
        if (readData[1] == 'T')
        {
            char subbuff[6];
            memcpy(subbuff, &readData[2], 6);
            if (atof(subbuff) == 0 && readData[2] != '0')
            {
                retour = "OT:Mauvaise valeur";
            }
            else
            {
                temperatureOffset(atof(subbuff));
                retour = "OT:" + String(temperatureOffset()) + "°C";
            }
        }
        else if (readData[1] == 'H')
        {
            char subbuff[6];
            memcpy(subbuff, &readData[2], 6);
            if (atof(subbuff) == 0 && readData[2] != '0')
            {
                retour = "OH:Mauvaise valeur";
            }
            else
            {
                humidityOffset(atof(subbuff));
                retour = "OH:" + String(humidityOffset()) + "%";
            }
        }
        break;
    case 'U':
        if (readData[1] == 'C')
        {
            toCelcius();
            retour = "U:CELCIUS";
        }
        else if (readData[1] == 'F')
        {
            toFahrenheit();
            retour = "u:FAHRENHEIT";
        }
        break;
    }
    return retour;
}

String MyDHT::readCommand(char *readData)
{
    String retour = "Commande inexistante";
    switch (readData[0])
    {
    case 'T':
        retour = "T:" + temperatureFormatted() + "°C";
        break;
    case 'H':
        retour = "H:" + humidityFormatted() + "°C";
        break;
    case 'O':
        if (readData[1] == 'T')
        {
            retour = "OT:" + String(temperatureOffset()) + "°C";
        }
        else if (readData[1] == 'H')
        {
            retour = "OH:" + String(humidityOffset()) + "%";
        }
        break;
    case 'U':
        if (temperatureType() == TCELCIUS)
        {
            retour = "U:CELCIUS";
        }
        else
        {
            retour = "U:FAHRENHEIT";
        }
        break;
    }
    return retour;
}
