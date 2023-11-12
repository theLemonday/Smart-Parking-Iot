#if !defined(UTILS_H)
#define UTILS_H

#include <Constant.h>
#include <ArduinoJson.h>

void DeserializationData2Json(JsonDocument& data,
                              byte* payload,
                              unsigned int length);

#endif  // UTILS_H
