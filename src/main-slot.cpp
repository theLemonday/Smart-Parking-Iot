#include <Arduino.h>
#include <Utils.h>
#include <Sensor.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Utils.h>
#include <Mqtt.h>
#include <Secret.h>
#include <WiFiClientSecureBearSSL.h>
#include <CommonComponents.h>

const char clientId[] = "Smart-parking-IoT-slot";

const char Slot1SensorPubTop[] = "smart-parking/gate/IR/slot/1";
CarDetectionSensor slot1Sensor(D1);

const char Slot2SensorPubTop[] = "smart-parking/gate/IR/slot/2";
CarDetectionSensor slot2Sensor(D2);

const char Slot3SensorPubTop[] = "smart-parking/gate/IR/slot/3";
CarDetectionSensor slot3Sensor(D3);

unsigned long prevMillis = 0;
unsigned long currentMillis = 0;
const unsigned long INTERVAL = 100L;

void callback(char* topic, byte* payload, unsigned int length) {
    DPRINTF("Message arrived [");
    DPRINT(topic);
    DPRINTF("] ");
    DPRINTLN((char*)payload);
}

WiFiClientSecure espClient;

void setup() {
#if defined(DEBUG)

    SetupBaudRate();

#endif  // DEBUG

    SetupWifi();
}

MQTTClient mqttClient(espClient, clientId, callback);

StaticJsonDocument<JSON_OBJECT_SIZE(1)> data;

void loop() {
    if (!mqttClient.connected()) {
        mqttClient.reconnect();
        // mqttClient.subscribe(GateBarrierSubTop);
        // mqttClient.subscribe(OLEDSubTop);
    }
    mqttClient.loop();

    currentMillis = millis();
    if (currentMillis - prevMillis > INTERVAL) {
        CarDetectionSensorCallbackHandler(
            mqttClient, Slot1SensorPubTop, slot1Sensor);

        CarDetectionSensorCallbackHandler(
            mqttClient, Slot2SensorPubTop, slot2Sensor);

        CarDetectionSensorCallbackHandler(
            mqttClient, Slot3SensorPubTop, slot3Sensor);
        prevMillis = millis();
    }

    // DisplayShow();
}
