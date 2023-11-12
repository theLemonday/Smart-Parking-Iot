#include "LED.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Utils.h>

LED::LED(uint8_t pin) : _pin(pin) {
    pinMode(_pin, OUTPUT);
    off();
}

void LED::on() {
#if defined(ESP8266)
    if (_pin == LED_BUILTIN) {
        digitalWrite(_pin, LOW);
        return;
    }
#endif
    digitalWrite(_pin, HIGH);
}

void LED::off() {
#if defined(ESP8266)
    if (_pin == LED_BUILTIN) {
        digitalWrite(_pin, HIGH);
        return;
    }
#endif
    digitalWrite(_pin, LOW);
}

LED::State LED::getCurrentState() {
#if defined(ESP8266)
    if (_pin == LED_BUILTIN) {
        return digitalRead(_pin) == HIGH ? LED::State::OFF : LED::State::ON;
    }
#endif
    return digitalRead(_pin) == HIGH ? LED::State::ON : LED::State::OFF;
}

void LEDCallbackHandler(LED led, byte* payload, unsigned int length) {
    StaticJsonDocument<JSON_OBJECT_SIZE(1)> data;
    DeserializationData2Json(data, payload, length);

    const char* status = data["status"];
    if (strcmp(status, "on") == 0) {
        DPRINTLNF("Turn LED on");
        led.on();
    } else {
        DPRINTLNF("Turn LED off");
        led.off();
    }
}