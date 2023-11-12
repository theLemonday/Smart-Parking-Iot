#include <Arduino.h>
#include <Constant.h>
#include <Sensor.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Utils.h>
#include <Mqtt.h>
#include <Secret.h>
#include <WiFiClientSecureBearSSL.h>
#include <CommonComponents.h>
#include <OLED.h>

const char OLEDSubTop[] = "smart-parking/gate/OLED";
const char GateBarrierSubTop[] = "smart-parking/gate/barrier";
const char clientId[] = "Smart-parking-IoT-maingate";

const char IRGoInDirection[] = "smart-parking/gate/IR/in";
CarDetectionSensor carGoesInDetectionSensor(D4);

const char IRGoOutDirection[] = "smart-parking/gate/IR/out";
CarDetectionSensor carGoesOutDetectionSensor(D5);

unsigned long prevMillis = 0;
unsigned long currentMillis = 0;
const unsigned long INTERVAL = 100L;

void callback(char* topic, byte* payload, unsigned int length) {
    DPRINTF("Message arrived [");
    DPRINT(topic);
    DPRINTF("] ");
    DPRINTLN((char*)payload);

    if (strcmp(topic, OLEDSubTop) == 0) {
        DPRINTLNF("Run OLED handler");
        DisplayHandler(payload, length);
        return;
    }

    if (strcmp(topic, GateBarrierSubTop) == 0) {
        DPRINTLNF("Run barrier handler");
        barrierHandler(payload, length);
        return;
    }
}

WiFiClientSecure espClient;

void setup() {
#if defined(DEBUG)

    SetupBaudRate();

#endif  // DEBUG

    SetupCommonComponents();
    SetupDisplay();

    SetupWifi();
}

MQTTClient mqttClient(espClient, clientId, callback);

StaticJsonDocument<JSON_OBJECT_SIZE(1)> data;

void loop() {
    if (!mqttClient.connected()) {
        mqttClient.reconnect();
        mqttClient.subscribe(GateBarrierSubTop);
        mqttClient.subscribe(OLEDSubTop);
    }
    mqttClient.loop();

    currentMillis = millis();
    if (currentMillis - prevMillis > INTERVAL) {
        CarDetectionSensorCallbackHandler(
            mqttClient, IRGoInDirection, carGoesInDetectionSensor);

        CarDetectionSensorCallbackHandler(
            mqttClient, IRGoOutDirection, carGoesOutDetectionSensor);

        prevMillis = millis();
    }

    DisplayShow();
}