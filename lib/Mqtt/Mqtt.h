#if !defined(MQTT_H)
#define MQTT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <Constant.h>

struct MqttServerConfig {
    const char* serverName;
    const uint16_t serverPort;
    const char* username;
    const char* password;
    const char* fingerPrint;
    /* data */
};

class MQTTClient : public PubSubClient {
   private:
    static const MqttServerConfig serverConfig;
    const char* const clientId;

   public:
    MQTTClient(WiFiClientSecure& espClient,
               const char* const clientId,
               MQTT_CALLBACK_SIGNATURE);

    void reconnect();

    void publish(const char* topic, const JsonDocument& data);
};

#endif  // MQTT_H
