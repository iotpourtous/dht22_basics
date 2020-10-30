#include <Arduino.h>
#include <unity.h>
#include "dht22Var.h"

void test_define(void)
{
    TEST_ASSERT_EQUAL(0, DEBUG);
    TEST_ASSERT_EQUAL(DHTPIN, DHTPIN);
    TEST_ASSERT_EQUAL(DHT22, DHTTYPE);
}

void test_dht_default_values(void)
{
    TEST_ASSERT_EQUAL(0.0, dht->temperatureOffset());
    TEST_ASSERT_EQUAL(0.0, dht->humidityOffset());
    TEST_ASSERT_EQUAL(TCELCIUS, dht->temperatureType());
}

void test_dht_change_temperatureOffset()
{
    dht->temperatureOffset(12.34);
    TEST_ASSERT_EQUAL(12.34, dht->temperatureOffset());
}

void test_dht_change_humidityOffset()
{
    dht->humidityOffset(12.34);
    TEST_ASSERT_EQUAL(12.34, dht->humidityOffset());
}

void test_dht_change_temperatureType()
{
    dht->toFahrenheit();
    TEST_ASSERT_EQUAL(TFAHRENHEIT, dht->temperatureType());
}

void setup()
{
    delay(2000);

    UNITY_BEGIN();
    //Valeur au démarrage
    RUN_TEST(test_define);
    RUN_TEST(test_dht_default_values);
    //Changer valeur par défaut
    RUN_TEST(test_dht_change_temperatureOffset);
    RUN_TEST(test_dht_change_humidityOffset);
    RUN_TEST(test_dht_change_temperatureType);
}

void loop()
{
    UNITY_END();
}