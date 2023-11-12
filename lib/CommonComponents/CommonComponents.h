#if !defined(COMMON_COMPONENTS_H)
#define COMMON_COMPONENTS_H

#include <Constant.h>
#include <ArduinoJson.h>

void SetupCommonComponents();

void barrierHandler(byte* payload, unsigned int length);

#endif  // COMMON_COMPONENTS_H
