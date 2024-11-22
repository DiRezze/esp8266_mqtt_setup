#include "softAP_config.h"

static IPAddress local_IP(192, 168, 100, 1);
static IPAddress gateway(192, 168, 100, 1);
static IPAddress subnet(255, 255, 255, 0);
static IPAddress primaryDNS(8, 8, 8, 8); 

#define apStatus_output 5

softAP_config::softAP_config(const char* ssid, const char* password) : _ssid(ssid), _password(password) {}

void softAP_config::startAP() {

    pinMode(apStatus_output, OUTPUT);

    WiFi.softAPConfig(local_IP, gateway, subnet);

    WiFi.softAP(_ssid,_password);

    digitalWrite(apStatus_output, HIGH);

}

void softAP_config::listenForCredentials() {

}

void softAP_config::stopAP() {
    WiFi.softAPdisconnect(true);
    digitalWrite(apStatus_output, LOW);
}
