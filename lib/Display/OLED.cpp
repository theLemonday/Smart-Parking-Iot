#include <OLED.h>
#include <Utils.h>
#include <ArduinoJson.h>

SSD1306Wire display(0x3c, SDA, SCL);
QRcodeOled qrcode(&display);
String &&currentText = "";
Mode currentMode = Mode::Text;

void SetupDisplay() {
    display.init();
    display.clear();
    display.display();
}

void DisplaySetText(String &&text) {
    DPRINTF("Display set current text: ");
    DPRINTLN(text);

    currentText = text;
}

void DisplaySetMode(Mode mode) {
    DPRINTF("Display set current mode: ");
    DPRINTLN(mode == QRCode ? "qr" : "text");

    currentMode = mode;
    if (currentMode != mode) display.resetDisplay();

    if (currentMode == QRCode) {
        qrcode.init();
        qrcode.create(currentText);
    }
}

void DisplayShow() {
    if (currentMode == QRCode) {
        return;
    }

    display.clear();

    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 20, currentText);

    display.display();
}

StaticJsonDocument<JSON_OBJECT_SIZE(2)> displayControlMsg;
void DisplayHandler(byte *const payload, const unsigned int length) {
    DeserializationData2Json(displayControlMsg, payload, length);
    const char *msg = displayControlMsg["msg"];
    DisplaySetText(msg);

    const char *contentType = displayControlMsg["type"];
    if (strcmp(contentType, "text")) {
        DisplaySetMode(Mode::QRCode);
    } else {
        DisplaySetMode(Mode::Text);
    }
}