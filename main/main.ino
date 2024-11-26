#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "softAP_config/softAP_config.h"

#define WiFistatus_output 4 //define o pino GPIO4(D2) como output de status do WiFi

#define relay_pin 14 //define o pino GPIO14(D5) como chave para o rele

// ssid e senha do SoftAP
const char* ssid = "Esp8266SoftAP";
const char* password = "senhaExemplo";

// ssid e senha de uma suposta rede WiFi
const char* WiFi_ssid = "RedeWiFi";
const char* WiFi_password = "senhaWiFi";

// parâmetros do mqtt
const char* mqtt_server="test.mosquitto.org";
const char* topic = "topicoteste/rele";
WiFiClient espClient;
PubSubClient client(espClient);

softAP_config AP (ssid, password);

void callback(char* topic, byte* payload, unsigned int length){

    String message = "";

    for (int i = 0; i < length; i++) {
        message += (char) payload[i];
    }

    if (message == "ON") {
        digitalWrite(relay_pin, HIGH);
        return;
    }
    if (message == "OFF"){
        digitalWrite(relay_pin, LOW);
        return
    }

}

void tryWiFiConnection(const char* _ssid, const char* _password, int status_output){
    if(!_ssid || !_password){

        digitalWrite(status_output, LOW);

        AP.startAP();

        return;
    } 

    WiFi.begin(_ssid, _password);

    byte tentativa = 0;

    while(WiFi.status() != WL_CONNECTED && tentativa < 10){
        digitalWrite(status_output, HIGH);
        delay(500);
        digitalWrite(status_output, LOW);
        tentativa++;
    }

    if(WiFi.status() != WL_CONNECTED){
        AP.startAP();
    } else {
        digitalWrite(status_output, HIGH);
    }

}

void reconnect() {
    while (!client.connected()) {
        if (client.connect("ESP8266Client")) {
            client.subscribe(topic);
        } else {
            delay(5000);
        }
    }
}

void setup(){
    // digital pins setup
    pinMode(WiFistatus_output, OUTPUT);
    pinMode(relay_pin, OUTPUT);

    tryWiFiConnection(WiFi_ssid, WiFi_password, WiFistatus_output);

    // mqtt broker client setup
    client.setServer(mqtt_server, 1883);
    client.subscribe(topic);
    client.setCallback(callback);
}

void loop(){
    if(!client.connected()) reconnect();

    client.loop();

    delay(10); // atrasa 10 milissegundos para evitar sobrecarga do hardware
}
