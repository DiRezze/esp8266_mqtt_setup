#ifndef softAp_config_H
#define softAp_config_H

#include <ESP8266WiFI.h>

class softAP_config {
    private:
        const char* _ssid;
        const char* _password
    public:
        // construtor da biblioteca
        softAP_config(const char* ssid, const char* password);

        // inicia o SoftAP com os parâmetros hardcodificados em ./softAP_config.cpp
        void startAP();

        // escuta por credenciais através de UDP
        void listenForCredentials();

        // interrompe o SoftAP
        void stopAP();
        
}

#endif // softAP_config
