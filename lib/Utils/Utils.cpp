#include <Utils.h>

void DeserializationData2Json(JsonDocument& data,
                              byte* payload,
                              unsigned int length) {
    DeserializationError error = deserializeJson(data, payload, length);
    DPRINTF("Deserized data: ");
#if defined(DEBUG)

    serializeJsonPretty(data, Serial);

#endif  // DEBUG
    DPRINTLN();

    if (error) {
        DPRINTF("deserializeJson() failed: ");
        DPRINTLN(error.f_str());
    }
}