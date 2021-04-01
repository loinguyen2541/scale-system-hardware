#include <SPI.h>
#include <MFRC522.h>
#include <math.h>
#include <string.h>
#include "objects/Card.cpp"
#include "utils/HttpUtil.h"
#include "utils/WifiUtil.h"
#include "Utils/ScaleUtil.h"

#define RST_PIN D3
#define SS_PIN D8
#define BUZZER_PIN D0
const int LOADCELL_DOUT_PIN = D1;
const int LOADCELL_SCK_PIN = D2;

MFRC522 mfrc522(SS_PIN, RST_PIN);

String before_value = "begin";
String result = "0.0";
float weight = 0.0;
int statusCode = 0;

String responeContent = "";

IdentityCard card;

HttpUtil httpUtil;

WifiUtil wifi;

ScaleUtil scale;

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  //init wifi
  wifi.Connect();
  //init rfc
  mfrc522.PCD_Init();
  //init pin
  pinMode(BUZZER_PIN, OUTPUT);

  // *********************************
  // Http Client
  // *********************************

  //httpUtil.Put("asdsa", 100);
}

void scanCard()
{
  String nfc_value = "";
  String weightOfVehicle;

  if (mfrc522.PICC_IsNewCardPresent())
  {
    if (mfrc522.PICC_ReadCardSerial())
    {
      //noti by pin
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      //get card id
      for (byte i = 0; i < mfrc522.uid.size; ++i)
      {
        nfc_value += mfrc522.uid.uidByte[i];
      }
      Serial.println(nfc_value);
      //check duplicate card
      if (before_value != nfc_value)
      {
        //check card existed
        //get api check card
        Serial.println("Card: " + nfc_value);
        if (card.identityCardId == 0 || card.partnerId == 0)
        {
          //the khong hop le
          Serial.println("Sai the");
          digitalWrite(BUZZER_PIN, HIGH);
          delay(50);
          digitalWrite(BUZZER_PIN, LOW);
          delay(50);
          digitalWrite(BUZZER_PIN, HIGH);
          delay(50);
          digitalWrite(BUZZER_PIN, HIGH);
          delay(50);
          digitalWrite(BUZZER_PIN, LOW);
          delay(50);
          digitalWrite(BUZZER_PIN, HIGH);
          delay(50);
        }
        else
        {
          Serial.println("OKkkkkkkkkkkkkkkkkkkkkkkkkkkkkk: ");
          //getWeight();
          Serial.println("Result: " + result);
          //post api create transactionId
          weightOfVehicle = String(weight);
          //postAPI("http://192.168.137.36/api/transactions/automatic?weightIn=" + weightOfVehicle + "&cardId=" + card.identityCardId);
          //UpdateTransaction("http://192.168.43.36/api/transactions/automatic?cardId="+card.identityCardId+"&weightOut="+weightOfVehicle);
          card.identityCardId.trim();
          //putAPI("/api/transactions/automatic?weightOut=150&cardId=214418643");
        }
      }
      else
      {
        //trung the
        Serial.println("Trung the");
        digitalWrite(BUZZER_PIN, HIGH);
        delay(20);
        digitalWrite(BUZZER_PIN, LOW);
        delay(20);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(20);
      }
      before_value = nfc_value;
    }
  }
  mfrc522.PICC_HaltA();
}

void loop()
{
  float unit = scale.GetScale();
  Serial.println(unit);
  delay(100);
}
