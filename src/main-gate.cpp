#include <Sensor.h>
#include <Arduino.h>
#include <Constant.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <OLED.h>
#include <MessageHandler.h>
#include <WsClient.h>
#include <Utils.h>

CarDetectionSensor carGoesInDetectionSensor(D4);
CarDetectionSensor carGoesOutDetectionSensor(D5);

unsigned long prevMillis = 0;
unsigned long currentMillis = 0;
const unsigned long INTERVAL = 100L;

void handleMessage(char payload[], size_t payloadLength) {
    StaticJsonDocument<JSON_LENGTH> data;
    bool error = DeserializationData2Json(data, payload, payloadLength);
    if (error) {
        return;
    }

    const char *msgType = data["type"];

    if (strcmp(msgType, "gateServo")) {
        gateServoHandler(data);
        return;
    }

    if (strcmp(msgType, "oled")) {
        OLEDHandler(data);
        return;
    }
}

void setup() {
    setupBaudRate();

    setupCommonComponents();
    setupDisplay();

    setupWifi();
    setupWebSocket(HOST_IP, HOST_PORT, handleMessage);
}

void loop() {
    if (currentMillis - prevMillis > INTERVAL) {
        if (carGoesInDetectionSensor.isCarDetected()) {
            StaticJsonDocument<JSON_OBJECT_SIZE(2)> data;
            data["type"] = "goInCarPark";
            data["status"] = "detected";
            sendJsonDataToServer(data);
        }

        if (carGoesOutDetectionSensor.isCarDetected()) {
            StaticJsonDocument<JSON_OBJECT_SIZE(2)> data;
            data["type"] = "goOutCarPark";
            data["status"] = "detected";
            sendJsonDataToServer(data);
        }
    }
}