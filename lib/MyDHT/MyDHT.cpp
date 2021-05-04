#include "MyDHT.h"

MyDHT::MyDHT(
    int pin,
    int type,
    int sensorId) : DHT_Unified(pin, type),
                    _sensorId(sensorId),
                    _temperatureOffset(0),
                    _humidityOffset(0)
{
    DHT_Unified::temperature().getSensor(&_temperatureSensor);
    DHT_Unified::humidity().getSensor(&_humiditySensor);
}

float MyDHT::temperature(void)
{
    sensors_event_t event;
    DHT_Unified::temperature().getEvent(&event);
    return event.temperature + _temperatureOffset;
}

float MyDHT::humidity(void)
{
    sensors_event_t event;
    DHT_Unified::humidity().getEvent(&event);
    return event.relative_humidity + _humidityOffset;
}

int32_t MyDHT::delay()
{
    return _temperatureSensor.min_delay / 1000;
}

String MyDHT::executeCommand(String command)
{
    if (command.equals(READ_INFORMATIONS_COMMAND))
    {
        String retour = "------------------------------------\n";
        retour += "Température : ";
        retour += (isnan(temperature()))
                      ? "lecture de la température impossible"
                      : (String)temperature() + "°C ";
        retour += "(offset :" + (String)temperatureOffset() + ")\n";
        retour += "HUmidité : ";
        retour += (isnan(temperature()))
                      ? "lecture de l'humidité impossible"
                      : (String)humidity() + "% ";
        retour += "(offset :" + (String)humidityOffset() + ")\n";
        retour += "------------------------------------";
        return retour;
    }
    else if (command.equals(READ_TEMPERATURE_SENSOR_INFORMATION_COMMAND))
    {
        String retour = "------------------------------------\n";
        retour += "Capteur de température\n";
        retour += "Nom: " + (String)_temperatureSensor.name + "\n";
        retour += "Version:  " + (String)_temperatureSensor.version + "\n";
        retour += "Identifiant:   " + (String)_temperatureSensor.sensor_id + "\n";
        retour += "Delay minimun:   " + (String)(_temperatureSensor.min_delay / 1000) + "ms\n";
        retour += "Valeur Max:   " + (String)_temperatureSensor.max_value + "°C\n";
        retour += "Valeur Min:   " + (String)_temperatureSensor.min_value + "°C\n";
        retour += "Resolution:  " + (String)_temperatureSensor.resolution + "°C\n";
        retour += "------------------------------------";
        return retour;
    }
    else if (command.equals(READ_HUMIDITY_SENSOR_INFORMATION_COMMAND))
    {
        String retour = "------------------------------------\n";
        retour += "Capteur d'humidité\n";
        retour += "Nom: " + (String)_humiditySensor.name + "\n";
        retour += "Version:  " + (String)_humiditySensor.version + "\n";
        retour += "Identifiant:   " + (String)_humiditySensor.sensor_id + "\n";
        retour += "Delay minimun:   " + (String)(_humiditySensor.min_delay / 1000) + "ms\n";
        retour += "Valeur Max:   " + (String)_humiditySensor.max_value + "%\n";
        retour += "Valeur Min:   " + (String)_humiditySensor.min_value + "%\n";
        retour += "Resolution:  " + (String)_humiditySensor.resolution + "%\n";
        retour += "------------------------------------";
        return retour;
    }
    if (command.startsWith(TEMPERATURE_OFFSET_COMMAND))
    {
        float value = command.substring(TEMPERATURE_OFFSET_COMMAND.length()).toFloat();
        if (value != 0 || (value == 0 && command.substring(2).startsWith("0")))
            temperatureOffset(value);
        return executeCommand(READ_INFORMATIONS_COMMAND);
    }
    else if (command.startsWith(HUMIDITY_OFFSET_COMMAND))
    {
        float value = command.substring(HUMIDITY_OFFSET_COMMAND.length()).toFloat();
        if (value != 0 || (value == 0 && command.substring(2).startsWith("0")))
            humidityOffset(value);
        return executeCommand(READ_INFORMATIONS_COMMAND);
    }
    else
    {
        String retour = "------------------------------------\n";
        retour += "Liste des commandes\n";
        retour += (String)_sensorId + READ_INFORMATIONS_COMMAND + " : Affiche la température et l'humidité\n";
        retour += (String)_sensorId + READ_TEMPERATURE_SENSOR_INFORMATION_COMMAND + " : Affiche les infos du capteur de température\n";
        retour += (String)_sensorId + READ_HUMIDITY_SENSOR_INFORMATION_COMMAND + " : Affiche les infos du capteur d'humidité\n";
        retour += (String)_sensorId + TEMPERATURE_OFFSET_COMMAND + "[XX.XX] : modifie l'offset de température si XX.XX est présent et affiche la température et l'humidité\n";
        retour += (String)_sensorId + HUMIDITY_OFFSET_COMMAND + "[XX.XX] : modifie l'offset d'humidité si XX.XX est présent et affiche la température et l'humidité\n";
        retour += "------------------------------------";
        return retour;
    }
}
