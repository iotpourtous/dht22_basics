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
    /*float t = event.temperature;
    if (isnan(t))
    {
        throw "Erreur lecture température";
    }
    return t;*/
    return event.temperature;
}

float MyDHT::_humidityFromEvent()
{
    sensors_event_t event;
    DHT_Unified::humidity().getEvent(&event);
    /*float h = event.relative_humidity;
    if (isnan(h))
    {
        throw "Erreur lecture humidité";
    }
    return h;*/
    return event.relative_humidity;
}

sensor_t MyDHT::temperatureSensor()
{
    sensor_t sensor;
    DHT_Unified::temperature().getSensor(&sensor);
    return sensor;
}

sensor_t MyDHT::humiditySensor()
{
    sensor_t sensor;
    DHT_Unified::humidity().getSensor(&sensor);
    return sensor;
}

int32_t MyDHT::delay()
{
    return temperatureSensor().min_delay / 1000;
}

float MyDHT::temperature()
{
    float t = _temperatureFromEvent();
    return ((_temperatureType == TFAHRENHEIT) ? 1.8 * t + 32 : t) + _temperatureOffset;
}

String MyDHT::temperatureFormatted()
{
    if(isnan(temperature())) {
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
    if(isnan(humidity())) {
        return "--";
    }
    char humidityFormatted[10];
    dtostrf(humidity(), 4, 2, humidityFormatted);
    return humidityFormatted;
}

String MyDHT::writeCommand(int sensorId, char *readData)
{
    String retour = "Commande inexistante";
    switch (readData[0])
    {
    case 'O':
        if (readData[1] == 'T')
        {
            char subbuff[6];
            memcpy(subbuff, &readData[2], 6);
            temperatureOffset(atof(subbuff));
            retour = ">" + String(sensorId) + "OT:" + temperatureOffset() + "°C";
        }
        else if (readData[1] == 'H')
        {
            char subbuff[6];
            memcpy(subbuff, &readData[2], 6);
            humidityOffset(atof(subbuff));
            retour = ">" + String(sensorId) + "OT:" + humidityOffset() + "%";
        }
        break;
    case 'U':
        if (readData[1] == 'C')
        {
            toCelcius();
            retour = ">" + String(sensorId) + "U:CELCIUS";
        }
        else if (readData[1] == 'F')
        {
            toFahrenheit();
            retour = ">" + String(sensorId) + "u:FAHRENHEIT";
        }
        break;
    }
    return retour;
}

String MyDHT::readCommand(int sensorId, char *readData)
{
    String retour = "Commande inexistante";

    switch (readData[0])
    {
    case 'T':
        retour = ">" + String(sensorId) + "T:" + temperatureFormatted() + "°C";
        break;
    case 'H':
        retour = ">" + String(sensorId) + "H:" + humidityFormatted() + "°C";
        break;
    case 'O':
        if (readData[1] == 'T')
        {
            retour = ">" + String(sensorId) + "OT:" + temperatureOffset() + "°C";
        }
        else if (readData[1] == 'H')
        {
            retour = ">" + String(sensorId) + "OH:" + humidityOffset() + "%";
        }
        break;
    case 'U':
        if (temperatureType() == TCELCIUS)
        {
            retour = ">" + String(sensorId) + "U:CELCIUS";
        }
        else
        {
            retour = ">" + String(sensorId) + "U:FAHRENHEIT";
        }
        break;
    }
    return retour;
}
