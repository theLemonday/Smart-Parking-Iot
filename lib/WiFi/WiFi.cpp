#include "wifi.h"
#include "Constant.h"
#include <Secret.h>

IPAddress SetupWifi() {
    delay(10);
    // We start by connecting to a WiFi network
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