#include <ESP8266WiFi.h>          // WiFi
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> // Telegram
#include <Wire.h>
// #include <NTPClient.h>         // Tiempo
// #include <ArduinoJson.h>

#define BOT_TOKEN "" // DEJAR VACIO ANTES DE PUSHEAR

#define ESPLED 16 // D0
#define MCULED 2  // D4
#define FLASH  0  // D3
#define NUSERS 4


const int USERS[NUSERS] = {0,
                           0,
                           0,
                           0}; // BORRAR ANTES DE PUSHEAR


const char *ssid = ""; // WiFi SSID
const char *pass = ""; // WiFi password


void conectwifi(const char *, const char *);
void handleMsg(int);
bool checkUser(String);





void setup() {
  Serial.begin(115200);

  connectwifi(ssid, pass);

  
}

void loop() {

}



void connectwifi(const char *ssid, const char *pass) {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(100);
  
  WiFi.begin(ssid, pass);
  Serial.print("\t\t[*] Connecting to: ");
  Serial.print(WiFi.SSID());

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\n\t\t[+] Connection established [");
  Serial.print(WiFi.localIP());
  Serial.println("]");
} // connectwifi


void handleMsg(int numMsgs) {
  for (int i = 0; i < numMsgs; i++) {
    String chatId = String(bot.messages[i].char_id);
    if (checkUser(chatId) == 0) {
      bot.sendMessage(chatId, "Unautorhized User", "");
      continue;
    }

    String text = bot.messages[i].text;
    String from = bot.messages[i].from_name;

    if (text == "/start") {
      // TODO: No prioritario pero queda bien
    }

    if (text == "/check") {
      // TODO: imprimir estado del sistema
    }
  }
}

bool checkUser(String chatId) {
  bool OK = false;

  for (int i = 0; i < NUSERS) {
    if (chatId == USERS[i])
      OK = true;
  }
  return OK;
}


 /* 0  -> D3
    1  -> D10
    2  -> D4
    3  -> D9
    4  -> D2
    5  -> D1
    12 -> D6
    13 -> D7
    14 -> D5
    15 -> D8
    16 -> D0 */
