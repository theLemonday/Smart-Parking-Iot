#if !defined(SENSOR_H)
#define SENSOR_H

#include <Mqtt.h>

class Sensor {
   protected:
    const uint8_t _analogPin;
    const uint8_t* _digitalPin;
    const uint8_t* _powerPin;

    Sensor(const uint8_t _analogPin,
           const uint8_t* _digitalPin,
           const uint8_t* _powerPin);

   public:
    Sensor(const uint8_t analogPin);
    Sensor(const uint8_t analogPin, const uint8_t& digitalPin);
    Sensor(const uint8_t analogPin,
           const uint8_t& digitalPin,
           const uint8_t& powerPin);

    void on();
    void off();
    int read();
    bool isAboveThreshold();
};

class CarDetectionSensor {
   public:
    enum State {
        NO_CAR,
        SAME_NO_CAR,
        NEW_CAR,
        SAME_NEW_CAR,
    };

    CarDetectionSensor(const uint8_t digitalPin);

    State IsNewCarDetected();

   private:
    const uint8_t _digitalPin;
    State prevState;
};

void CarDetectionSensorCallbackHandler(MQTTClient& client,
                                       const char* const topic,
                                       CarDetectionSensor& carSensor);

#endif  // SENSOR_H
