#include <Arduino.h>
#include <Constant.h>
#include <avr/pgmspace.h>
#include <CommonComponents.h>
#include <Sensor.h>
// #include <WiFi.h>

const char IRGoInDirection[] = "smart-parking/gate/IR/in";
CarDetectionSensor carGoesInDetectionSensor(D4);

const char IRGoOutDirection[] = "smart-parking/gate/IR/out";
CarDetectionSensor carGoesOutDetectionSensor(D5);

unsigned long prevMillis = 0;
unsigned long currentMillis = 0;
const unsigned long INTERVAL = 100L;

void setup() {
    SetupBaudRate();
    // SetupCommonComponents();
    // SetupWifi();
}

void loop() {
    currentMillis = millis();
    if (currentMillis - prevMillis > 1000) {
        auto carDetectionState = carGoesInDetectionSensor.NewCarDetected();

        switch (carDetectionState) {
            case CarDetectionSensor::State::NO_CAR:
                Serial.println("no car");
                break;

            case CarDetectionSensor::State::NEW_CAR:
                Serial.println("new car");
                break;
        }
        prevMillis = millis();
    }
}