#include <Adafruit_FONA.h>
#include <SoftwareSerial.h>
#define FONA_RX 5
#define FONA_TX 4
#define FONA_RST 9
// PIN 17 RES



SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);
uint8_t type;

void setup() {
  while (!Serial);
  Serial.begin(9600);
  fonaSerial->begin(9600);
    if (! fona.begin(*fonaSerial)) {
      Serial.println(F("FONA Introuvable"));
    while (1);
  }
  type = fona.type();
  Serial.println(F("FONA is OK"));
  Serial.print(F("Found "));

 
  char imei[15] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("Module IMEI: "); Serial.println(imei);
  }


}

void loop() {

        uint8_t n = fona.getNetworkStatus();
        Serial.print(F("Network status "));
        Serial.print(n);
        Serial.print(F(": "));
        if (n == 0) Serial.println(F("Not registered"));
        if (n == 1) Serial.println(F("Registered (home)"));
        if (n == 2) Serial.println(F("Not registered (searching)"));
        if (n == 3) Serial.println(F("Denied"));
        if (n == 4) Serial.println(F("Unknown"));
        if (n == 5) Serial.println(F("Registered roaming"));


        if (n == 1){
          if (!fona.sendSMS("+32472555810", "LA VOITURE EST VOLEE !")) {
            Serial.println("Failed");
          } else {
            Serial.println("Sent!");
          }
          
          delay(300000);
        }
          delay(1000);

}
