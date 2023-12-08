#include <Servo.h>

Servo s;
void setup() {
    s.attach(D0);
    pinMode(D1, OUTPUT);
    pinMode(D3, OUTPUT);
    digitalWrite(D1, HIGH);
    digitalWrite(D3, LOW);
}

bool clockWise = true;

void loop() {
    s.write(0);
    delay(1000);

    s.write(90);
    delay(1000);

    s.write(0);
    delay(1000);
}