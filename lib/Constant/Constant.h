#ifndef CONSTANT_H
#define CONSTANT_H

#include <Arduino.h>
#include <avr/pgmspace.h>
#define DEBUG  // If you comment this line, the DPRINT & DPRINTLN lines are
               // defined as blank.
#ifdef DEBUG   // Macros are usually in all capital letters.

// DPRINT is a macro, debug print
#define DPRINT(...) Serial.print(__VA_ARGS__)

// DPRINTLN is a macro, debug print with new line
#define DPRINTLN(...) Serial.println(__VA_ARGS__)

// DPRINT is a macro, debug print
#define DPRINTF(...) Serial.print(F(__VA_ARGS__))

// DPRINTLN is a macro, debug print with new line
#define DPRINTLNF(...) Serial.println(F(__VA_ARGS__))

// #define DPRINT_JSON(...) serializeJsonPretty(doc, Serial);
#else
#define DPRINT(...)    // now defines a blank line
#define DPRINTLN(...)  // now defines a blank line
#endif

#if defined(DEBUG)

const int BAUD_RATE PROGMEM = 115200;
void SetupBaudRate();

#endif  // DEBUG

#endif