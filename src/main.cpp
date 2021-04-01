#include <SPI.h>
#include <MFRC522.h>
#include <math.h>
#include <string.h>
#include "objects/Card.cpp"
#include "utils/HttpUtil.h"
#include "utils/WifiUtil.h"
#include "Utils/ScaleUtil.h"

#include "SPI.h"
#include "PN532/PN532_SPI/PN532_SPI.h"
#include "PN532/PN532/snep.h"
#include "NdefMessage.h"

#define BUZZER_PIN D8
const int LOADCELL_DOUT_PIN = D1;
const int LOADCELL_SCK_PIN = D2;

PN532_SPI pn532spi(SPI, D0);
SNEP nfc(pn532spi);
PN532 nfc_p2p(pn532spi);

String responeContent = "";

IdentityCard card;

HttpUtil httpUtil;

WifiUtil wifi;

ScaleUtil scale;

uint8_t ndefBuffer[128];

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  //init wifi
  nfc_p2p.begin();

  wifi.Connect();
  //init rfc
  //init pin
  pinMode(BUZZER_PIN, OUTPUT);

  // *********************************
  // Http Client
  // *********************************

  //httpUtil.Put("asdsa", 100);
}

String getCardId()
{
  String cardId;
  int msgSize = nfc.read(ndefBuffer, sizeof(ndefBuffer), 500);
  if (msgSize > 0)
  {
    NdefMessage msg = NdefMessage(ndefBuffer, msgSize);
    NdefRecord record = msg.getRecord(0);

    int payloadLength = record.getPayloadLength();
    byte payload[payloadLength];
    record.getPayload(payload);
    int startChar = 0;
    if (record.getTnf() == TNF_WELL_KNOWN && record.getType() == "T")
    {
      startChar = payload[0] + 1;
    }
    else if (record.getTnf() == TNF_WELL_KNOWN && record.getType() == "U")
    {
      startChar = 1;
    }

    String payloadAsString = "";
    for (int c = startChar; c < payloadLength; c++)
    {
      payloadAsString += (char)payload[c];
    }
    cardId = payloadAsString;
    Serial.println(payloadAsString);
  }
  else
  {
    boolean success;
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; // Buffer to store the returned UID
    uint8_t uidLength;                     // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    success = nfc_p2p.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

    if (success)
    {
      Serial.println("Found a card!");
      Serial.print("UID Length: ");
      Serial.print(uidLength, DEC);
      Serial.println(" bytes");
      Serial.print("UID Value: ");
      for (uint8_t i = 0; i < uidLength; i++)
      {
        cardId = cardId + uid[i];
      }
      Serial.println("cardID   " + cardId);
      // Wait 1 second before continuing
      return cardId;
    }
  }
}

void warnBuzz()
{
  for (size_t i = 0; i < 10; i++)
  {

    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void wrongCardBuzz()
{
  for (size_t i = 0; i < 2; i++)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void loop()
{
  float unit = scale.GetScale();
  String cardId = getCardId();
  if (cardId.length() > 5)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    bool result = httpUtil.Post(cardId, unit);
    if (!result)
    {
      digitalWrite(BUZZER_PIN, LOW);
      delay(500);
      wrongCardBuzz();
    }
    else
    {
      digitalWrite(BUZZER_PIN, LOW);
      delay(500);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
    }
  }
}
