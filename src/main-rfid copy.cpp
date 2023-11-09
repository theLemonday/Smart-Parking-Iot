#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <Constant.h>
#include <Rfid.h>

AsyncWebServer server(80);

const char UID_INPUT[] = "uid";
const char PASSWORD_INPUT[] = "password";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <title>ESP Input Form For RFID Card & Tag</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
  <body>
    <form action="/get">
      uid: <input type="text" name="uid">
      <input type="submit" value="Submit">
    </form>
    <br>
    <form action="/get">
      password: <input type="text" name="password">
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
)rawliteral";

void notFound(AsyncWebServerRequest* request) {
    request->send(404, "text/plain", "Not found");
}

int char2int(char input) {
    if (input >= '0' && input <= '9')
        return input - '0';
    if (input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if (input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    else
        return 0;
}

// This function assumes src to be a zero terminated sanitized string with
// an even number of [0-9a-f] characters, and target to be sufficiently large
void hex2bin(const char* src, char* target) {
    while (*src && src[1]) {
        *(target++) = char2int(*src) * 16 + char2int(src[1]);
        src += 2;
    }
}

byte newUID[4];

void setup() {
    setupBaudRate();

    auto address = setupWifi();
    Serial.println(address);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send_P(200, "text/html", index_html);
    });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest* req) {
        String inputMessage;
        String inputParam;

        if (req->hasParam(UID_INPUT)) {
            inputMessage = req->getParam(UID_INPUT)->value();
            // char target[4];
            hex2bin(inputMessage.c_str(), (char*)newUID);
            // newUID = (byte*)target;
        }
    });

    server.onNotFound(notFound);
    server.begin();
}

void loop() {
    setNewUID4RFIDCard(newUID);
}