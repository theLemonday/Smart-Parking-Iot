#if !defined(UTILS_H)
#define UTILS_H

#include <Constant.h>
#include <ArduinoJson.h>

bool DeserializationData2Json(StaticJsonDocument<JSON_LENGTH> data, char payload[], size_t payloadLength);
String SerializeJSONData2String(StaticJsonDocument<JSON_LENGTH> data);

#endif  // UTILS_H
