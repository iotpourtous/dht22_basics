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

float MyDHT::humidity()
{
    return _humidityFromEvent() + _humidityOffset;
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
            retour = "U:" + (temperatureType() == TCELCIUS) ? "U:CELCIUS" : "U:FAHRENHEIT";
        }
        else if (readData[1] == 'F')
        {
            toFahrenheit();
            retour = "U:" + (temperatureType() == TCELCIUS) ? "U:CELCIUS" : "U:FAHRENHEIT";
        }
        break;
    }
    return retour;
}

String MyDHT::readCommand(char *readData, int8_t sensorId)
{
    String retour = "Commande inexistante";
    switch (readData[0])
    {
    case 'C':
        retour = "------------------------------------\n";
        retour += "Liste des commandes\n";
        retour += "'>" + String(sensorId) + "C' : Liste des commandes\n";
        retour += "'>" + String(sensorId) + "T' : Lit la température\n";
        retour += "'>" + String(sensorId) + "H' : Lit l'humidité\n";
        retour += "'>" + String(sensorId) + "OT' : Lit l'offset de température\n";
        retour += "'>" + String(sensorId) + "OH' : Lit l'offset d'humidité\n";
        retour += "'>" + String(sensorId) + "U' : Lit l'unité de température\n";
        retour += "'>" + String(sensorId) + "IT' : Lit les infos du capteur de température\n";
        retour += "'>" + String(sensorId) + "IH' : Lit les infos du capteur d'humidité\n";
        retour += "'<" + String(sensorId) + "OTXX.XX' : modifie l'offset de température\n";
        retour += "'<" + String(sensorId) + "OHXX.XX' : modifie l'offset d'humidité\n";
        retour += "'<" + String(sensorId) + "UC' : Change l'unité de température en Celcius\n";
        retour += "'<" + String(sensorId) + "UF' : Change l'unité de température en Fahrenheit\n";
        retour += "------------------------------------";
        break;
    case 'T':
        if (isnan(temperature()))
        {
            retour = "T:lecture de la température impossible";
        }
        else
        {
            char temperatureFormated[5];
            sprintf(temperatureFormated, "%.1f", temperature());
            retour = "T:" + String(temperatureFormated) + "°C";
        }
        break;
    case 'H':
        if (isnan(humidity()))
        {
            retour = "H:lecture de l'humidité impossible";
        }
        else
        {
            char humidityFormated[5];
            sprintf(humidityFormated, "%.1f", temperature());
            retour = "H:" + String(humidityFormated) + "%";
        }
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
        retour = "U:" + (temperatureType() == TCELCIUS) ? "U:CELCIUS" : "U:FAHRENHEIT";
        break;
    case 'I':
        if (readData[1] == 'T')
        {
            sensor_t sensor = _temperatureSensor();
            retour = "IT\n";
            retour += "------------------------------------\n";
            retour += "Capteur de température\n";
            retour += "Nom: " + String(sensor.name) + "\n";
            retour += "Version:  " + String(sensor.version) + "\n";
            retour += "Identifiant:   " + String(sensor.sensor_id) + "\n";
            retour += "Delay minimun:   " + String(sensor.min_delay / 1000) + "Ms\n";
            retour += "Valeur Max:   " + String(sensor.max_value) + "°C\n";
            retour += "Valeur Min:   " + String(sensor.min_value) + "°C\n";
            retour += "Resolution:  " + String(sensor.resolution) + "°C\n";
            retour += "------------------------------------";
        }
        else if (readData[1] == 'H')
        {
            sensor_t sensor = _humiditySensor();
            retour = "IH\n";
            retour += "------------------------------------\n";
            retour += "Capteur d'humidité\n";
            retour += "Nom: " + String(sensor.name) + "\n";
            retour += "Version:  " + String(sensor.version) + "\n";
            retour += "Identifiant:   " + String(sensor.sensor_id) + "\n";
            retour += "Delay minimun:   " + String(sensor.min_delay / 1000) + "Ms\n";
            retour += "Valeur Max:   " + String(sensor.max_value) + "%\n";
            retour += "Valeur Min:   " + String(sensor.min_value) + "%\n";
            retour += "Resolution:  " + String(sensor.resolution) + "%\n";
            retour += "------------------------------------";
        }
        break;
    }
    return retour;
}
