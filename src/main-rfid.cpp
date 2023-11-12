#include <Utils.h>
#include <LED.h>
#include <Utils.h>
#include <WiFi.h>
#include <Mqtt.h>
#include <Rfid.h>

const char greenLEDSubTop[] = "smart-parking/gate/greenLED";
LED greenLED(D2);

const char redLEDSubTop[] = "smart-parking/gate/redLED";
LED redLED(D1);

const char RFIDOutputSubTop[] = "smart-parking/gate/RFID/output";
const char RFIDInputSubTop[] = "smart-parking/gate/RFID/input";

const char clientId[] = "Smart-parking-IoT-RFID";

unsigned long prevMillis = 0;
unsigned long currentMillis = 0;
const unsigned long INTERVAL = 100L;

void callback(char* topic, byte* payload, unsigned int length) {
    DPRINT(F("Message arrived ["));
    DPRINT(topic);
    DPRINT(F("] "));
    DPRINTLN((char*)payload);

    if (strcmp(topic, greenLEDSubTop) == 0) {
        DPRINTLNF("Run green LED handler");
        LEDCallbackHandler(greenLED, payload, length);
        return;
    }

    if (strcmp(topic, redLEDSubTop) == 0) {
        DPRINTLNF("Run red LED handler");
        LEDCallbackHandler(redLED, payload, length);
        return;
    }
}

WiFiClientSecure espClient;

void setup() {
#if defined(DEBUG)

    SetupBaudRate();

#endif  // DEBUG

    SetupWifi();
    SetupRFID();
}

MQTTClient mqttClient(espClient, clientId, callback);

void loop() {
    if (!mqttClient.connected()) {
        mqttClient.reconnect();
        mqttClient.subscribe(greenLEDSubTop);
        mqttClient.subscribe(redLEDSubTop);
    }
    mqttClient.loop();

    currentMillis = millis();

    if (currentMillis - prevMillis > INTERVAL) {
        auto uid = readRFIDCardIfExisted();
        if (uid == "") {
            return;
        }

        StaticJsonDocument<JSON_OBJECT_SIZE(1)> data;
        data["uid"] = uid.c_str();
        mqttClient.publish(RFIDOutputSubTop, data);
    }
}