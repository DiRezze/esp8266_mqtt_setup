#include "softAP_config.h"

IPAddress local_IP(192, 168, 100, 1);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8); 

softAP_config::softAP_config(const char* ssid, const char* password) : _ssid(ssid), _password(password) {}

void softAP_config::startAP() {
    // configura e inicia o softAP
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(_ssid,_password);

    Serial.println("SoftAP ativado!");

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
    // desativa o softAP
    WiFi.softAPdisconnect(true);
    Serial.println("SoftAP desativado.");
}
