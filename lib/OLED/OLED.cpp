#include <OLED.h>
#include <qrcode.h>

SSD1306Wire display(0x3c, SDA, SCL);
QRcode qrcode(&display);
bool currentQrcode = false;

void setupDisplay() {
    display.init();
    display.clear();
    display.display();

    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
}

void drawText(const char text[]) {
    if (currentQrcode) {
        currentQrcode = false;
        display.resetDisplay();
    }

    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 22, text);
    display.display();
}

void drawQrCode(const char text[]) {
    currentQrcode = true;
    qrcode.init();
    qrcode.create(text);
}