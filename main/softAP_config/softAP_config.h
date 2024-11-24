#ifndef softAP_config_H
#define softAP_config_H

#include <ESP8266WiFI.h>

class softAP_config {
    private:
        const char* _ssid;
        const char* _password;

    public:
        // Construtor da biblioteca
        softAP_config(const char* ssid, const char* password);

        // Inicia o SoftAP com os parâmetros hardcodificados em ./softAP_config.cpp
        void startAP();

        // Escuta por credenciais através de UDP
        void listenForCredentials();

        // Interrompe o SoftAP
        void stopAP();
};

#endif // softAP_config
