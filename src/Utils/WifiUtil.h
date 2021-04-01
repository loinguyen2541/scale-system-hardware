#ifndef WIFI_CPP
#define WIFI_CPP

#include <ESP8266WiFi.h>

class WifiUtil
{
private:
    /* data */
public:
    const char *ssid = "scale_system";
    const char *password = "12356789";
    WifiUtil();
    ~WifiUtil();
    void Connect();
};

#endif