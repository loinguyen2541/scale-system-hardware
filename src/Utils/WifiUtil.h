#ifndef WIFI_CPP
#define WIFI_CPP

#include <ESP8266WiFi.h>

class WifiUtil
{
private:
    /* data */
public:
    const char *ssid = "FPTU_Student";
    const char *password = "12345678";
    WifiUtil();
    ~WifiUtil();
    void Connect();
};

#endif