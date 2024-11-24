#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "softAP_config/softAP_config.h"

#define WiFistatus_output 4 //define o pino GPIO4(D2) como output de status do WiFi

#define relay_pin 14 //define o pino GPIO14(D5) como chave para o rele

// ssid e senha do SoftAP
const char* ssid = "Esp8266SoftAP";
const char* password = "senhaExemplo";

// ssid e senha de uma suposta rede WiFi armazenada ou recebida pelo ESP8266
const char* WiFi_ssid = "RedeWiFi";
const char* WiFi_password = "senhaWiFi";

const char* mqtt_server="test.mosquitto.org";
const char* topic = "topicoteste/rele";
WiFiClient espClient;
PubSubClient client(espClient);

softAP_config AP (ssid, password);

void callback(char* topic, byte* payload, unsigned int length){

    Serial.print("[INFO] Mensagem recebida no tópico:");
    Serial.println(topic);

    String message = "";

    for (int i = 0; i < length; i++) {
        message += (char) payload[i];
    }

    Serial.print(" - Mensagem: ");
    Serial.println(message);

    if (message == "ON") {
        digitalWrite(relay_pin, HIGH);
        Serial.println("[INFO] Relé ligado.");
    } else if (message == "OFF") {
        digitalWrite(relay_pin, LOW);
        Serial.println("[INFO] Relé desligado.");
    } else {
        Serial.println("[INFO] Mensagem desconhecida.");
    }
}

void tryWiFiConnection(const char* _ssid, const char* _password, int status_output){
    if(!_ssid || !_password){

        Serial.println("[WARNING] Não há dados de ssid ou de senha.");

        digitalWrite(status_output, LOW);

        AP.startAP();

        return;
    } 

    Serial.print("[INFO] Conectando ao Wi-Fi...");

    WiFi.begin(_ssid, _password);

    byte tentativa = 0;

    while(WiFi.status() != WL_CONNECTED && tentativa < 10){  // Aumentei para 10 tentativas
        digitalWrite(status_output, HIGH);
        delay(500);
        digitalWrite(status_output, LOW);
        Serial.print(".");
        tentativa++;
    }

    if(WiFi.status() != WL_CONNECTED){
        Serial.print("[ERROR] Falha na conexão Wi-Fi. Status: ");
        Serial.println(WiFi.status());
        AP.startAP();
    } else {
        digitalWrite(status_output, HIGH);
        Serial.println("[SUCCESS] Conexão bem-sucedida!");
        Serial.print("[INFO] Endereço IP local:");
        Serial.println(WiFi.localIP());
    }

}

void reconnect() {
    while (!client.connected()) {
            Serial.print("[INFO] Conectando ao broker MQTT...");
        if (client.connect("ESP8266Client")) {
            Serial.println("[SUCCESS]Conectado!");
            client.subscribe(topic);
        } else {
            Serial.print("[ERROR] Falha, estado: ");
            Serial.println(client.state());
            delay(5000);
        }
    }
}

void setup(){
    Serial.begin(115200);

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
    if( !client.connected() ){
        Serial.println("[INFO] Cliente desconectado. Reconectando...");
        reconnect();
    }

    client.loop();

    delay(10);
}
