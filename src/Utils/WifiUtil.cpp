
#include "WifiUtil.h"

WifiUtil::WifiUtil()
{
}

WifiUtil::~WifiUtil()
{
}

void WifiUtil::Connect()
{

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print("Connecting..");
    }
    Serial.print("Connect Success");
}