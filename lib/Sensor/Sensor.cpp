#include <Sensor.h>

Sensor::Sensor(const uint8_t analogPin,
               const uint8_t* digitalPin,
               const uint8_t* powerPin)
    : _analogPin(analogPin), _digitalPin(digitalPin), _powerPin(powerPin) {
    pinMode(analogPin, INPUT);

    if (_digitalPin != nullptr) {
        pinMode(*_digitalPin, INPUT);
    }

    if (_powerPin != nullptr) {
        pinMode(*_powerPin, OUTPUT);
        off();
    }
}

Sensor::Sensor(const uint8_t analogPin) : Sensor(analogPin, nullptr, nullptr) {}

Sensor::Sensor(const uint8_t analogPin, const uint8_t& digitalPin)
    : Sensor(analogPin, &digitalPin, nullptr) {}

Sensor::Sensor(const uint8_t analogPin,
               const uint8_t& digitalPin,
               const uint8_t& powerPin)
    : Sensor(analogPin, &digitalPin, &powerPin) {}

void Sensor::on() {
    if (_powerPin == nullptr) {
        Serial.println("Power pin is not defined");
        return;
    }

    digitalWrite(*_powerPin, HIGH);
}

void Sensor::off() {
    if (_powerPin == nullptr) {
        Serial.println("Power pin is not defined");
        return;
    }

    digitalWrite(*_powerPin, LOW);
}

int Sensor::read() { return analogRead(_analogPin); }

bool Sensor::isAboveThreshold() {
    if (_digitalPin == nullptr) {
        Serial.println("Digital pin is not defined");
        return false;
    }

    return digitalRead(*_digitalPin) == HIGH;
}

CarDetectionSensor::CarDetectionSensor(const uint8_t digitalPin)
    : _digitalPin(digitalPin) {
    prevState = SAME_NO_CAR;
    pinMode(_digitalPin, INPUT);
}

// LOW -> car detected
CarDetectionSensor::State CarDetectionSensor::IsNewCarDetected() {
    if (digitalRead(_digitalPin) == HIGH) {
        if (prevState != SAME_NO_CAR) {
            prevState = SAME_NO_CAR;
            return NO_CAR;
        }

        return SAME_NO_CAR;
    }

    if (prevState != SAME_NEW_CAR) {
        prevState = SAME_NEW_CAR;
        return NEW_CAR;
    }

    return SAME_NEW_CAR;
}

StaticJsonDocument<JSON_OBJECT_SIZE(1)> carDectionData;
void CarDetectionSensorCallbackHandler(MQTTClient& client,
                                       const char* const topic,
                                       CarDetectionSensor& carSensor) {
    auto carDetectionState = carSensor.IsNewCarDetected();

    switch (carDetectionState) {
        case CarDetectionSensor::State::NO_CAR:
            carDectionData["detected"] = false;
            client.publish(topic, carDectionData);
            break;

        case CarDetectionSensor::State::NEW_CAR:
            carDectionData["detected"] = true;
            client.publish(topic, carDectionData);
            break;
    }
}
