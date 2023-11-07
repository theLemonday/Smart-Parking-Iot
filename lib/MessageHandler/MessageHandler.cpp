#include <MessageHandler.h>

void OLEDHandler(StaticJsonDocument<JSON_LENGTH> data) {
    const char *contentType = data["contentType"];
    const char *msg = data["msg"];

    if (strcmp(contentType, "text")) {
        drawText(msg);
        return;
    }

    drawQrCode(msg);
}

void gateServoHandler(StaticJsonDocument<JSON_LENGTH> data) {
    const char *status = data["status"];
    if (strcmp(status, "open")) {
        openGate();
        return;
    }

    closeGate();
}