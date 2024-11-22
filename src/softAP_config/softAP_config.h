#ifndef softAp_config_H
#define softAp_config_H

#include <ESP8266WiFI.h>

class softAP_config {
    private:
        const char* _ssid;
        const char* _password;
        
    public:
        softAP_config(const char* ssid, const char* password);
        void startAP();
        void listenForCredentials();
        void stopAP();
}

#endif // softAP_config
