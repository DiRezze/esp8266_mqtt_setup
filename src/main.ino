#include <ESP8266WiFi.h>
#include <SoftAP_config.h>

// ssid e senha do SoftAP
const char* ssid = "Esp8266SoftAP";
const char* password = "senhaExemplo";

softAP_config AP (ssid, password);

void setup(){
    Serial.begin(115200);
}

void loop(){

}