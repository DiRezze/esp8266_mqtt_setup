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
    Serial.begin(115200);

    pinMode(WiFistatus_output, OUTPUT); 

    tryWiFiConnection(WiFi_ssid, WiFi_password, WiFistatus_output);

}

void loop(){
    // código principal do sistema
    // TODO: ouvinte de conexão com o WiFi
}

void tryWiFiConnection(const char* _ssid, const char* _password, int status_output){

    if(!_ssid || !_password){
        Serial.println("Erro: não há dados de ssid ou de senha.");
        digitalWrite(status_output, LOW);
        AP.startAP();
        return; // interrompe a função que tenta conexão com o WiFi
    } 

    Serial.print("Conectando ao Wi-Fi...");

    WiFi.begin(_ssid, _password);

    delay(500);

    int tentativas = 0;

    while(WiFi.status() != WL_CONNECTED && tentativas < 10){
        digitalWrite(status_output, HIGH);

        delay(500);

        digitalWrite(status_output, LOW);

        Serial.print(".");

        tentativas++;

    }

    if(WiFi.status() != WL_CONNECTED){
        Serial.println("A conexão falhou.");

        // lógica do ESP8266 como SoftAP
        AP.startAP();

    } else {
        digitalWrite(status_output, HIGH);

        Serial.println("Conexão bem-sucedida!");
        Serial.print("Endereço IP local:");
        Serial.println(WiFi.localIP());

    }

}
