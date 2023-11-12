#include <CommonComponents.h>
#include <Servo.h>
#include <Utils.h>
#include <ArduinoJson.h>

Servo gateServo;

void closeGate() {
    DPRINTLNF("Close gate");
    gateServo.write(0);
}

void openGate() {
    DPRINTLNF("Open gate");
    gateServo.write(90);
}

void SetupCommonComponents() {
    gateServo.attach(D3);
    closeGate();
}

void barrierHandler(byte* payload, unsigned int length) {
    StaticJsonDocument<JSON_OBJECT_SIZE(1)> data;
    DeserializationData2Json(data, payload, length);

    const char* status = data["status"];
    if (strcmp(status, "open") == 0) {
        openGate();
        return;
    }

    closeGate();
}