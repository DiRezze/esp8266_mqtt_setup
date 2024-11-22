#ifndef WiFiManager_H

#define WiFiManager_H

#include <ESP8266WiFI.h>
#include <softAP_config.h>

class WiFiManager{
    public:
        const char* WiFi_ssid;
        const char* WiFi_password;
        int statusLedPin;
        softAp_config AccessPoint;
    
    private:

        // construtor da classe
        WiFiManager(const char* WiFi_ssid, const char* WiFi_password, int statusLedPin);

        // tenta conectar à rede wifi com base nos parâmetros passados; retorna false imediatamente caso algum seja nulo
        bool connect(const char* WiFi_ssid, const char* WiFi_password);

        // lida com a desconexão do WiFi
        void handleDisconnection();

        // inicia um softAP ao falhar na conexão
        void startSoftAP();

};

#endif
