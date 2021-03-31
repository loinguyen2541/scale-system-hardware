#ifndef HTTP_CPP
#define HTTP_CPP

#include <WiFiClientSecure.h>
#include <Arduino.h>

class HttpUtil
{
private:
    /* data */
public:
    String host = "iesystem-api.azurewebsites.net";
    int httpsPort = 443;
    WiFiClientSecure client;
    HttpUtil(/* args */);
    ~HttpUtil();
    void Post();
};

#endif