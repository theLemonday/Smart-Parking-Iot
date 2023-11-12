#if !defined(OLED_H)
#define OLED_H

#include <Arduino.h>
#include <qrcodeoled.h>
#include <SSD1306Wire.h>

// D1 -> SCL
// D2 -> SDA
void SetupDisplay();

enum Mode { Text, QRCode };

void DisplaySetText(String&& text);

void DisplaySetMode(Mode);

void DisplayShow();

void DisplayHandler(byte* const payload, const unsigned int length);

#endif  // OLED_H
