#if !defined(RFID_H)
#define RFID_H

#include <SPI.h>
#include <Arduino.h>
#include <MFRC522.h>

#define SS_PIN D4   // D2
#define RST_PIN D3  // D1

void SetupRFID();

String readRFIDCardIfExisted();

#endif  // RFID_H
