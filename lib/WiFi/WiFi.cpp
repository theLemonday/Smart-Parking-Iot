#include "wifi.h"
#include "Utils.h"
#include <Secret.h>

IPAddress SetupWifi() {
    delay(10);

    DPRINTF("Connecting to: ");
    DPRINTLN(SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        DPRINT('.');
    }

    randomSeed(micros());

    DPRINTLN();
    DPRINTLNF("WiFi connected");
    DPRINTF("IP address: ");

    IPAddress ipAdress = WiFi.localIP();
    DPRINTLN(ipAdress);

    return ipAdress;
}