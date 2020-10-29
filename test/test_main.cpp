#include <Arduino.h>
#include <unity.h>
#include "dht22Var.h"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_define(void) {
    TEST_ASSERT_EQUAL(0, DEBUG);
    TEST_ASSERT_EQUAL(DHTPIN, DHTPIN);
    TEST_ASSERT_EQUAL(DHT22, DHTTYPE);
}


void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
    RUN_TEST(test_define);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
      UNITY_END(); // stop unit testing
}