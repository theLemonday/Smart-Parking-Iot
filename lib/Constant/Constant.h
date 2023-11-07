#ifndef CONSTANT_H
#define CONSTANT_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Secret.h>

const IPAddress HOST_IP(192, 168, 0, 101);
const uint16_t HOST_PORT = 8080;

const int BAUD_RATE = 115200;
void setupBaudRate();

const auto JSON_LENGTH = JSON_STRING_SIZE(3);

#endif