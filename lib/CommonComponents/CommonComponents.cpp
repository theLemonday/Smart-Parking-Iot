#include <CommonComponents.h>
#include <Servo.h>

Servo gateServo;

void setupCommonComponents() {
    gateServo.attach(D3);
}

void openGate() {
    gateServo.write(90);
}

void closeGate() {
    gateServo.write(0);
}