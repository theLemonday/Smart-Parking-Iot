#if !defined(MESSAGE_HANDLER_H)
#define MESSAGE_HANDLER_H
#include <ArduinoJson.h>
#include <Arduino.h>
#include <Constant.h>
#include <OLED.h>
#include <CommonComponents.h>

void OLEDHandler(StaticJsonDocument<JSON_LENGTH> data);

void gateServoHandler(StaticJsonDocument<JSON_LENGTH> data);

#endif  // MESSAGE_HANDLER_H
