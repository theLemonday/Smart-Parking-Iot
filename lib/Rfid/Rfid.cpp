#include "Rfid.h"
#include <MFRC522.h>
#include <SPI.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

const unsigned int prevMillis = millis();
const unsigned int currentMillis = prevMillis;
const unsigned int READ_INTERVAL = 50;

void setupRFID() {
    SPI.begin();         // Initiate  SPI bus
    mfrc522.PCD_Init();  // Initiate MFRC522

    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }
}

// String readRFIDCardIfExisted() {
//     String content = "";
//     if (currentMillis - prevMillis < READ_INTERVAL ||
//         !mfrc522.PICC_IsNewCardPresent() ||
//         !mfrc522.PICC_ReadCardSerial()) {
//         return content;
//     }

//     byte letter;
//     for (byte i = 0; i < mfrc522.uid.size; i++) {
//         content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//         content.concat(String(mfrc522.uid.uidByte[i], HEX));
//     }
//     content.toUpperCase();

//     return content;
// }

void setNewUID4RFIDCard(byte newUID[4]) {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        delay(50);
        return;
    }

    Serial.print(F("Card UID:"));
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Set new UID
    if (mfrc522.MIFARE_SetUid(newUID, (byte)4, true)) {
        Serial.println(F("Wrote new UID to card."));
    }

    // Halt PICC and re-select it so DumpToSerial doesn't get confused
    mfrc522.PICC_HaltA();
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    // Dump the new memory contents
    Serial.println(F("New UID and contents:"));
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

    delay(2000);
}