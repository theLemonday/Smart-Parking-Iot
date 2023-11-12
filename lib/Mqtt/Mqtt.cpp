#include "Mqtt.h"
#include <Secret.h>

#define BUFFER_SIZE 256
char tempbuffer[BUFFER_SIZE];

MQTTClient::MQTTClient(WiFiClientSecure& espClient,
                       const char* const clientId,
                       MQTT_CALLBACK_SIGNATURE)
    : PubSubClient(espClient), clientId(clientId) {
    espClient.setFingerprint(MQTT_SECRET::FINGER_PRINT);
    setServer(MQTT_SECRET::SERVER, MQTT_SECRET::PORT);
    setCallback(callback);
}

void MQTTClient::reconnect() {
    while (!this->connected()) {
        DPRINTLNF("Attempting MQTT connection...");
        String randomClientId = clientId + String(random(0xffff), HEX);

        if (this->connect(randomClientId.c_str(),
                          MQTT_SECRET::USERNAME,
                          MQTT_SECRET::PASSWORD)) {
            DPRINTLNF("connected");
        } else {
            DPRINTF("failed, rc=");
            DPRINT(state());
            DPRINTLNF(" try again in 2 seconds");
            delay(2000);
        }
    }
}

void MQTTClient::publish(const char* topic, const JsonDocument& data) {
#if defined(DEBUG)

    serializeJsonPretty(data, Serial);
    DPRINTLN();

#endif  // DEBUG

    size_t length = serializeJson(data, tempbuffer);
    PubSubClient::publish(topic, tempbuffer, length);
}
