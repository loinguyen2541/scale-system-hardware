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

    String url = "/api/transactions/automatic?weightIn=" + String(weightIn) + "&cardId=" + cardId;

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
        line = client.readString();
    }

    if (line.indexOf("Card is not exist") > -1)
    {

        Serial.println("error");
        return false;
    }
    else
    {
        Serial.println(line);
        result = true;
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

    String url = "/api/transactions/automatic/" + cardId + "?weightOut=" + weightOut;

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

    while (client.available())
    {
        line = client.readString();
    }

    if (line.indexOf("Card is not exist") > -1)
    {

        Serial.println("error");
        return false;
    }
    else
    {
        Serial.println(line);
        result = true;
    }
    Serial.println("==========");
    Serial.println("closing connection");
    return result;
}