#include "HttpUtil.h"

char fingerprint[] PROGMEM = "8b 00 83 0b cc f2 46 f7 96 d3 8e b5 e1 2f cf bd 1d 3a 61 50";

HttpUtil::HttpUtil(/* args */)
{
    client.setFingerprint(fingerprint);
    if (!client.connect(host, httpsPort))
    {
        Serial.println("connection failed");
        return;
    }
}

HttpUtil::~HttpUtil()
{
}

void HttpUtil::Post()
{
    String url = "/api/transactions/automatic?weightIn=170&cardId=214418643";

    Serial.print("requesting URL: ");
    Serial.println(url);
    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
                 "Content-Length: 0\r\n" +
                 "Accept: */*\r\n" +
                 "Accept-Encoding: gzip, deflate, br\r\n" +
                 "Connection: close\r\n\r\n");
    Serial.println("request sent");
    while (client.connected())
    {
        String line = client.readStringUntil('\n');
        if (line == "\r")
        {
            Serial.println("headers received");
            break;
        }
    }

    Serial.println("reply was:");
    Serial.println("==========");
    String line;
    while (client.available())
    {
        line = client.readStringUntil('\n'); //Read Line by Line
        Serial.println(line);                //Print response
    }
    Serial.println("==========");
    Serial.println("closing connection");
}