#include "Rfid.h"
#include <Constant.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);

void SetupRFID() {
    SPI.begin();
    mfrc522.PCD_Init();
}

String readRFIDCardIfExisted() {
    String content = "";
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return content;
    }

    for (byte i = 0; i < mfrc522.uid.size; i++) {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    // DPRINTF("UID tag : ");
    // DPRINTLN(content);

    return content;
}