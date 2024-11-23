#include "softAP_config.h"

static IPAddress local_IP(192, 168, 100, 1);
static IPAddress gateway(192, 168, 100, 1);
static IPAddress subnet(255, 255, 255, 0);
static IPAddress primaryDNS(8, 8, 8, 8); 

#define apStatus_output 5 // define GPIO5(D1) como saída para o status do SoftAP

softAP_config::softAP_config(const char* ssid, const char* password) : _ssid(ssid), _password(password) {}

void softAP_config::startAP() {

    Serial.println("Ativando o SoftAP...");

    pinMode(apStatus_output, OUTPUT);

    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(_ssid,_password);

    Serial.println("SoftAP ativado!");
    digitalWrite(apStatus_output, HIGH);

    Serial.print("Nome da rede: ");
    Serial.println(_ssid);

    Serial.print("Senha:");
    Serial.println(_password);

    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());
}

void softAP_config::listenForCredentials() {

    // recebe as credenciais

    // tenta conectar-se à alguma rede wi-fi

    // se obtiver sucesso, encerra o AP: stopAP()

}

void softAP_config::stopAP() {
    WiFi.softAPdisconnect(true);
    Serial.println("SoftAP desativado.");
    digitalWrite(apStatus_output, LOW);
}