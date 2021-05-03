#include <ESP8266WiFi.h>          // ESP32: <WiFi.h>
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

const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);


struct status {
  char st;       // 4 bits (2 persianas, 1 aire, 1 calef)
  int  t_aire;   // 8 bits temperatura aire
  int  t_calef;  // 8 bits temperatura calef
};


const char *SSID = ""; // WiFi SSID
const char *PASS = ""; // WiFi password
struct status stats;

void conectwifi(const char *, const char *);
void handleMsg(int);
bool checkUser(String);





void setup() {
  Serial.begin(115200);

  connectwifi(SSID, PASS);
}

void loop() {
  delay(1000);
/*
  unsigned long m = millis();
  Serial.print(m);
  Serial.print("  -  ");
  Serial.print(bot_lasttime);
  Serial.print("  =  ");
  Serial.println(m - bot_lasttime);
*/
  if (millis() - bot_lasttime > BOT_MTBS) {
    Serial.println("Entering...");
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleMsg(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
  }
  bot_lasttime = millis();
}


void connectwifi(const char *ssid, const char *pass) {
  configTime(0, 0, "pool.ntp.org");
  secured_client.setTrustAnchors(&cert);
  
  WiFi.begin(ssid, pass);
  Serial.print("\t\t[*] Connecting to: ");
  Serial.print(SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\n\t\t[+] Connection established [");
  Serial.print(WiFi.localIP());
  Serial.println("]");
} // connectwifi

void handleMsg(int numMsgs) {
  Serial.print("[handlMsg] ");
  Serial.println(numMsgs);
  for (int i = 0; i < numMsgs; i++) {
    String chatId = bot.messages[i].chat_id;
    if (checkUser(chatId) == 0) {
      bot.sendMessage(chatId, "Unautorhized User", "");
      continue;
    }

    String text = bot.messages[i].text;
    String from = bot.messages[i].from_name;

    if (text == "/start") {
      Serial.println("/start");
      bot.sendMessage(chatId, "Hello!");
    }

    if (text == "/check") {
      Serial.println("/check");
      bot.sendMessage(chatId, "Checking status...");
    }

    if (text == "/subirPersianas" || text == "/bajarPersianas") {
      /* Pide el estado de las persianas a la FPGA" 
      int st = stpersianas() */
      if (text == "/subirPersianas") {
        Serial.println("/subirPersianas");
        /* enviar orden de subir las persianas
        mvpersianas(up) */
        bot.sendMessage(chatId, "Subiendo persianas");
      }
      if (text == "/bajarPersianas") {
        Serial.println("/bajarPersianas");
        /* enviar orden de bajar las persianas
        mvpersianas(down) */
        bot.sendMessage(chatId, "Bajando persianas");
      }
    }
  }
}

bool checkUser(String c) {
  bool OK = false;
  int chatId = c.toInt();

  for (int i = 0; i < NUSERS; i++) {
    if (chatId == USERS[i])
      OK = true;
  }
  return OK;
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
