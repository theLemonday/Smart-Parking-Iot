#include <Arduino.h>
#include <OLED.h>

unsigned long prevMillis = 0;
unsigned long currentMillis = 0;
const unsigned long INTERVAL = 5000L;
bool isCurrentQR = false;

void setup() {
    SetupDisplay();
    DisplaySetText("hello world");
}

void loop() {
    currentMillis = millis();
    if (currentMillis - prevMillis > INTERVAL) {
        if (isCurrentQR) {
            isCurrentQR = false;
            DisplaySetMode(Mode::Text);
        } else {
            isCurrentQR = true;
            DisplaySetMode(Mode::QRCode);
        }
        prevMillis = millis();
    }
    DisplayShow();
}