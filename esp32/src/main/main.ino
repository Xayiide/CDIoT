#include <ESP8266WiFi.h>          // ESP32: <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> // Telegram
#include <Wire.h>
#include <SoftwareSerial.h>
// #include <NTPClient.h>         // Tiempo
// #include <ArduinoJson.h>

#define BOT_TOKEN "" // DEJAR VACIO ANTES DE PUSHEAR

#define ESPLED 16 // D0
#define MCULED 2  // D4
#define FLASH  0  // D3
#define NUSERS 4
#define BAUDRT 115200


const int USERS[NUSERS] = {0,
                           0,
                           0,
                           0}; // BORRAR ANTES DE PUSHEAR

const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
SoftwareSerial SUART(4, 5); // Check pins acording to board

byte stat = 0;

enum stPers {
  SUBIDAS  = 0;
  SUBIENDO = 1;
  BAJANDO  = 2;
  BAJADAS  = 3;
};

struct stats {
  enum stPers stP;
  bool aire;
  bool calef;
  byte temp;
};


const char *SSID = ""; // WiFi SSID
const char *PASS = ""; // WiFi password
struct stats stats;

void conectwifi(const char *, const char *);
void handleMsg(int);
bool checkUser(String);
void rcv();
void snd();
void pfrcv(byte);
void decod(byte);
void decodst(byte);
void decoddat(byte);
void decodprs(byte);
void decodac(byte);
void decodtemp(byte);


void setup() {
  SUART.begin(BAUDRT);
  Serial.begin(BAUDRT);

  connectwifi(SSID, PASS);
}

void loop() {
  delay(1000);

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

void rcv() {
  byte n = SUART.available();
  if (n != 0) { // n != 0 -> data arrived
    char x = SUART.read();
    pfrcv(x);
    decod(x);
  }
  n = 0;
}

void snd() {
  // TODO
}

void pfrcv(byte x) {
  Serial.print("<[");
  Serial.print(x, BIN);
  Serial.print("-0x");
  Serial.print(x, HEX);
  Serial.println("]");
}


void decod(byte x) {
  // MSB -> 1 = packet is status data
  //     -> 0 = packet is sensor data
  bitRead(x, 7) ? decodst(x) : decoddat(x);
}

void decodst(byte x) {
  decodprs(x);
  decodac(x);
  decodtemp(x);
}

void decodprs(byte x) {
  if (!bitRead(x, 6) && !bitRead(x, 5)) { // 00
    st.stP = SUBIDAS;
    Serial.println("Subidas");
  }
  else if (!bitRead(x, 6) && bitRead(x, 5)) { // 01
    st.stP = SUBIENDO;
    Serial.println("Subiendo");
  }
  else if (bitRead(x, 6) && !bitRead(x, 5)) { // 10
    st.stP = BAJANDO;
    Serial.println("Bajando");
  }
  else if (bitRead(x, 6) && bitRead(x, 5)) { // 11
    st.stP = BAJADAS;
    Serial.println("Bajadas");
  }
}

void decodac(byte x) {
  if (bitRead(x, 4)) {
    st.aire  = false;
    st.calef = true;
    Serial.println("1 -> calef");
  } else {
    st.aire  = true;
    st.calef = false;
    Serial.println("0 -> aire");
  }
}

void decodtemp(byte x) {
  byte tmp = 0x00;
  for (int i = 3; i > 0; i--) {
    tmp = tmp | bitRead(x, i);
    tmp <<= 1;
  }
  tmp += 14;
  st.temp = tmp;
  Serial.print("tmp: 0b");
  Serial.print(tmp, BIN);
  Serial.print(", ");
  Serial.println(tmp, DEC);
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
