#include <Utils.h>

bool DeserializationData2Json(StaticJsonDocument<JSON_LENGTH> data, char payload[], size_t payloadLength) {
    DeserializationError error = deserializeJson(data, payload, payloadLength);

    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return true;
    }

    return false;
}

String SerializeJSONData2String(StaticJsonDocument<JSON_LENGTH> data) {
    String payload;
    serializeJson(data, payload);

    return payload;
}