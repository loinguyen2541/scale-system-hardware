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
    bool Post(String cardId, float weightIn);
    bool Put(String cardId, float weightOut);
};

#endif