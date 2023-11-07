#include <Arduino.h>
#include <LED.h>
#include <ArduinoJson.h>
#include <Constant.h>
#include <Utils.h>

LED greenLED(D1);
LED redLED(D2);

void controlLED(LED led, const char status[]) {
    if (strcmp(status, "on")) {
        led.on();
        return;
    }

    led.off();
}

void handleMessage(char payload[], size_t payloadLength) {
    StaticJsonDocument<JSON_LENGTH> data;
    bool error = DeserializationData2Json(data, payload, payloadLength);
    if (error) {
        return;
    }

    const char* msgType = data["type"];

    if (strcmp(msgType, "greenLED")) {
        const char* status = data["status"];
        controlLED(greenLED, status);
        return;
    }

    if (strcmp(msgType, "redLED")) {
        const char* status = data["status"];
        controlLED(redLED, status);
        return;
    }
}

void setup() {
}