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

float MyDHT::temperature(void)
{
    float t = _temperatureFromEvent();
    return ((_temperatureType == TFAHRENHEIT) ? 1.8 * t + 32 : t) + _temperatureOffset;
}

float MyDHT::humidity(void)
{
    return _humidityFromEvent() + _humidityOffset;
}

int32_t MyDHT::delay()
{
    return _temperatureSensor().min_delay / 1000;
}

String MyDHT::writeCommand(String command)
{
    if (command.startsWith(TEMPERATURE_OFFSET_COMMAND))
    {
        String data = command.substring(2);
        if (isNotIntValue(data))
        {
            return "Commande incorrecte";
        }
        temperatureOffset(data.toInt());
        return "OK";
    }
    else if (command.startsWith(HUMIDITY_OFFSET_COMMAND))
    {
        String data = command.substring(2);
        if (isNotIntValue(data))
        {
            return "Commande incorrecte";
        }
        humidityOffset(data.toInt());
        return "OK";
    }
    else if (command.equals(CELCIUS_TEMPERATURE_COMMAND))
    {
        toCelcius();
        return "OK";
    }
    else if (command.equals(FAHRENHEIT_TEMPERATURE_COMMAND))
    {
        toFahrenheit();
        return "OK";
    }
    return "Commande inexistante";
}

boolean MyDHT::isNotIntValue(String data)
{
    return data.toInt() == 0 && data.charAt(0) != '0';
}

String MyDHT::readCommand(String command, int8_t sensorId)
{
    if (command.equals(LIST_COMMAND))
    {
        String retour = "------------------------------------\n";
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
        return retour;
    }
    else if (command.equals("T"))
    {
        return (isnan(temperature()))
                   ? "T:lecture de la température impossible"
                   : "T:" + String(temperature()) + "°C";
    }
    else if (command.equals("H"))
    {
        return (isnan(temperature()))
                   ? "H:lecture de l'humidité impossible"
                   : "H:" + String(humidity()) + "%";
    }
    else if (command.equals("OT"))
    {
        return "OT:" + String(temperatureOffset()) + "°C";
    }
    else if (command.equals("OH"))
    {
        return "OH:" + String(humidityOffset()) + "%";
    }
    else if (command.equals("U"))
    {
        return "U:" + (temperatureType() == TCELCIUS) ? "U:CELCIUS" : "U:FAHRENHEIT";
    }
    else if (command.equals("IT"))
    {
        sensor_t sensor = _temperatureSensor();
        String retour = "------------------------------------\n";
        retour += "Capteur de température\n";
        retour += "Nom: " + String(sensor.name) + "\n";
        retour += "Version:  " + String(sensor.version) + "\n";
        retour += "Identifiant:   " + String(sensor.sensor_id) + "\n";
        retour += "Delay minimun:   " + String(sensor.min_delay / 1000) + "Ms\n";
        retour += "Valeur Max:   " + String(sensor.max_value) + "°C\n";
        retour += "Valeur Min:   " + String(sensor.min_value) + "°C\n";
        retour += "Resolution:  " + String(sensor.resolution) + "°C\n";
        retour += "------------------------------------";
        return retour;
    }
    else if (command.equals("IH"))
    {
        sensor_t sensor = _humiditySensor();
        String retour = "------------------------------------\n";
        retour += "Capteur d'humidité\n";
        retour += "Nom: " + String(sensor.name) + "\n";
        retour += "Version:  " + String(sensor.version) + "\n";
        retour += "Identifiant:   " + String(sensor.sensor_id) + "\n";
        retour += "Delay minimun:   " + String(sensor.min_delay / 1000) + "Ms\n";
        retour += "Valeur Max:   " + String(sensor.max_value) + "%\n";
        retour += "Valeur Min:   " + String(sensor.min_value) + "%\n";
        retour += "Resolution:  " + String(sensor.resolution) + "%\n";
        retour += "------------------------------------";
        return retour;
    }
    else
    {
        return "Commande inexistante";
    }
}
