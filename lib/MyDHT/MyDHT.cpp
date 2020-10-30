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
    float t = event.temperature;
    if (isnan(t))
    {
        throw "Erreur lecture température";
    }
    return t;
}

float MyDHT::_humidityFromEvent()
{
    sensors_event_t event;
    DHT_Unified::humidity().getEvent(&event);
    float h = event.relative_humidity;
    if (isnan(h))
    {
        throw "Erreur lecture humidité";
    }
    return h;
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

float MyDHT::humidity()
{
    return _humidityFromEvent() + _humidityOffset;
}

void MyDHT::writeCommand(int sensorId, char *readData)
{
    switch (readData[0])
    {
    case 'O':
        if (readData[1] == 'T')
        {
            char subbuff[6];
            memcpy(subbuff, &readData[2], 6);
            temperatureOffset(atof(subbuff));
            cout << ">" << sensorId << "OT:" << temperatureOffset() << "°C" << endl;
        }
        else if (readData[1] == 'H')
        {
            char subbuff[6];
            memcpy(subbuff, &readData[2], 6);
            humidityOffset(atof(subbuff));
            cout << ">" << sensorId << "OT:" << humidityOffset() << "%" << endl;
        }
        else
        {
            throw "Commande inexistante";
        }
        break;
    case 'U':
        if (readData[1] == 'C')
        {
            toCelcius();
            cout << ">" << sensorId << "U:" << ((temperatureType() == TCELCIUS) ? "CELCIUS" : "FAHRENHEIT") << endl;
        }
        else if (readData[1] == 'F')
        {
            toFahrenheit();
            cout << ">" << sensorId << "U:" << ((temperatureType() == TCELCIUS) ? "CELCIUS" : "FAHRENHEIT") << endl;
        }
        else
        {
            throw "Commande inexistante";
        }
        break;
    default:
        throw "Commande inexistante";
        break;
    }
}

void MyDHT::readCommand(int sensorId, char *readData)
{
    switch (readData[0])
    {
    case 'C':
        cout << "------------------------------------" << endl
             << "Liste des commandes" << endl
             << "'>" << sensorId << "C' : Liste des commandes" << endl
             << "'>" << sensorId << "OT' : Lit l'offset de température" << endl
             << "'>" << sensorId << "OH' : Lit l'offset d'humidité" << endl
             << "'>" << sensorId << "U' : Lit l'unité de température" << endl
             << "'>" << sensorId << "IT' : Lit les infos du capteur de température" << endl
             << "'>" << sensorId << "IH' : Lit les infos du capteur d'humidité" << endl
             << "'<" << sensorId << "OTXX.XX' : modifie l'offset de température" << endl
             << "'<" << sensorId << "OHXX.XX' : modifie l'offset d'humidité" << endl
             << "'<" << sensorId << "UC' : Change l'unité de température en Celcius" << endl
             << "'<" << sensorId << "UF' : Change l'unité de température en Fahrenheit" << endl
             << "------------------------------------" << endl;
        break;
    case 'T':
        cout << ">" << sensorId << "T:" << temperature() << "°C" << endl;
        break;
    case 'H':
        cout << ">" << sensorId << "H:" << humidity() << "%" << endl;
        break;
    case 'O':
        if (readData[1] == 'T')
        {
            cout << ">" << sensorId << "OT:" << temperatureOffset() << "°C" << endl;
        }
        else if (readData[1] == 'H')
        {
            cout << ">" << sensorId << "OT:" << humidityOffset() << "%" << endl;
        }
        else
        {
            throw "Commande inexistante";
        }
        break;
    case 'U':
        cout << ">" << sensorId << "U:" << ((temperatureType() == TCELCIUS) ? "CELCIUS" : "FAHRENHEIT") << endl;
        break;
    case 'I':
        if (readData[1] == 'T')
        {
            sensor_t sensor = temperatureSensor();
            cout << "------------------------------------" << endl
                 << "Capteur de température" << endl
                 << "Nom: " << sensor.name << endl
                 << "Version:  " << sensor.version << endl
                 << "Identifiant:   " << sensor.sensor_id << endl
                 << "Delay minimun:   " << sensor.min_delay / 1000 << "Ms" << endl
                 << "Valeur Max:   " << sensor.max_value << "°C" << endl
                 << "Valeur Min:   " << sensor.min_value << "°C" << endl
                 << "Resolution:  " << sensor.resolution << "°C" << endl
                 << "------------------------------------" << endl;
        }
        else if (readData[1] == 'H')
        {
            sensor_t sensor = humiditySensor();
            cout << "------------------------------------" << endl
                 << "Humidity Sensor" << endl
                 << "Nom: " << sensor.name << endl
                 << "Version:  " << sensor.version << endl
                 << "Identifiant:   " << sensor.sensor_id << endl
                 << "Delay minimun:   " << sensor.min_delay / 1000 << "Ms" << endl
                 << "Valeur Max:   " << sensor.max_value << "%" << endl
                 << "Valeur Min:   " << sensor.min_value << "%" << endl
                 << "Resolution:  " << sensor.resolution << "%" << endl
                 << "------------------------------------" << endl;
        }
        else
        {
            throw "Commande inexistante";
        }
        break;
    default:
        throw "Commande inexistante";
        break;
    }
}
