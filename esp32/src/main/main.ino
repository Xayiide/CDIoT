// #include <ESP8266WiFi.h>          // ESP32: <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <UniversalTelegramBot.h> // Telegram
// #include <Wire.h>
// #include <NTPClient.h>         // Tiempo
// #include <ArduinoJson.h>

#include "include/UART.h"
#include "include/utils.h"
#include "include/common.h"
#include "include/telegram.h"
#include "include/wifi.h"

#define ESPLED 16 // D0
#define MCULED 2  // D4
#define FLASH  0  // D3


const int USERS[NUSERS] = {0,
                           0,
                           0,
                           0}; // BORRAR ANTES DE PUSHEAR

void setup() {
  Serial1.begin(BAUDRATE);
  Serial.begin(BAUDRATE);

  connectwifi(SSID, PASS);
}

void loop() {
  delay(1000);
  checkUpdates();
}

 /* 0  -> D3  -> FLASH buttom
    1  -> D10 
    2  -> D4  -> MCULED
    3  -> D9
    4  -> D2
    5  -> D1
    12 -> D6
    13 -> D7
    14 -> D5
    15 -> D8
    16 -> D0  -> ESPLED
  */
