#if !defined(OLED_H)
#define OLED_H

#include <SSD1306Wire.h>

void setupDisplay();

void drawText(const char text[]);

void drawQrCode(const char text[]);

#endif  // OLED_H
