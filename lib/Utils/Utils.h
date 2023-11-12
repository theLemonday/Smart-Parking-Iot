#if !defined(UTILS_H)
#define UTILS_H

#include <ArduinoJson.h>

// Define debug environment
#define DEBUG

#ifdef DEBUG

// DPRINT is a macro, debug print
#define DPRINT(...) Serial.print(__VA_ARGS__)

// DPRINTLN is a macro, debug print with new line
#define DPRINTLN(...) Serial.println(__VA_ARGS__)

// DPRINT is a macro, debug print with content store in flash
#define DPRINTF(...) Serial.print(F(__VA_ARGS__))

// DPRINTLN is a macro, debug print with new line and content store in flash
#define DPRINTLNF(...) Serial.println(F(__VA_ARGS__))

const int BAUD_RATE = 115200;

// Setup Serial with predefined BAUD_RATE
void SetupBaudRate();

#else

#define DPRINT(...)    // now defines a blank line
#define DPRINTLN(...)  // now defines a blank line

#endif

void DeserializationData2Json(JsonDocument& data,
                              byte* payload,
                              unsigned int length);

#endif  // UTILS_H
