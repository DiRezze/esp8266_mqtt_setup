#include <ESP8266WiFi.h>
#include <SoftAP_config.h>

#define WiFistatus_output 4 //define o pino GPIO4(D2) como output de status do WiFi

// ssid e senha do SoftAP
const char* ssid = "Esp8266SoftAP";
const char* password = "senhaExemplo";

// ssid e senha de uma suposta rede WiFi armazenada ou recebida pelo ESP8266
const char* WiFi_ssid = "RedeWiFi";
const char* WiFi_password = "senhaWiFi";

softAP_config AP (ssid, password);

void setup(){
    pinMode(WiFistatus_output, OUTPUT); 

    tryWiFiConnection(WiFi_ssid, WiFi_password, WiFistatus_output);

}

void loop(){
    // código principal do sistema
    // TODO: ouvinte de conexão com o WiFi
}

void tryWiFiConnection(const char* _ssid, const char* _password, int status_output){

    if(!_ssid || !_password){
        digitalWrite(status_output, LOW);
        AP.startAP();
        return;
    } 

    WiFi.begin(_ssid, _password);

    delay(500);

    int tentativas = 0;

    while(WiFi.status() != WL_CONNECTED && tentativas < 10){
        digitalWrite(status_output, HIGH);

        delay(500);

        digitalWrite(status_output, LOW);

        tentativas++;

    }

    if(WiFi.status() != WL_CONNECTED){
        AP.startAP();
    } else {
        digitalWrite(status_output, HIGH);
    }

}
