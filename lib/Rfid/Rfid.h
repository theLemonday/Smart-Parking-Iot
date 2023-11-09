#if !defined(RFID_H)
#define RFID_H

#define SS_PIN 4   // D2
#define RST_PIN 5  // D1
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

void setupRFID();

// String readRFIDCardIfExisted();

void setNewUID4RFIDCard(byte newUID[4]);

#endif  // RFID_H
