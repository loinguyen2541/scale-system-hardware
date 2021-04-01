#include "HttpUtil.h"

char fingerprint[] PROGMEM = "8b 00 83 0b cc f2 46 f7 96 d3 8e b5 e1 2f cf bd 1d 3a 61 50";

HttpUtil::HttpUtil(/* args */)
{
    client.setFingerprint(fingerprint);
}

HttpUtil::~HttpUtil()
{
}

bool HttpUtil::Post(String cardId, float weightIn)
{
    bool result = false;
    if (!client.connect(host, httpsPort))
    {
        Serial.println("connection failed");
        return false;
    }

    String url = "/api/transactions/automatic?weightIn=170&cardId=214418643a";

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
    if (client.status() == 201)
    {
        while (client.available())
        {
            line = client.readStringUntil('\n'); //Read Line by Line
            Serial.println(line);                //Print response
        }
        result = true;
    }
    else
    {
        Serial.println("Post Error!");
        while (client.available())
        {
            line = client.readStringUntil('\n'); //Read Line by Line
            Serial.println(line);                //Print response
        }
        result = false;
    }
    Serial.println("==========");
    Serial.println("closing connection");
    return result;
}

bool HttpUtil::Put(String cardId, float weightOut)
{
    bool result = false;
    if (!client.connect(host, httpsPort))
    {
        Serial.println("connection failed");
        return false;
    }

    String url = "/api/transactions/automatic/214418643?weightOut=100";

    Serial.print("requesting URL: ");
    Serial.println(url);
    client.print(String("PUT ") + url + " HTTP/1.1\r\n" +
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
    if (client.status() == 201)
    {
        while (client.available())
        {
            line = client.readStringUntil('\n'); //Read Line by Line
            Serial.println(line);                //Print response
        }
        result = true;
    }
    else
    {
        Serial.println("Post Error!");
        while (client.available())
        {
            line = client.readStringUntil('\n'); //Read Line by Line
            Serial.println(line);                //Print response
        }
        result = false;
    }
    Serial.println("==========");
    Serial.println("closing connection");
    return result;
}