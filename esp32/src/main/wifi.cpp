//#include <Arduino.h>
#include <UniversalTelegramBot.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

#include "include/common.h"
#include "include/wifi.h"
#include "include/utils.h"
#include "include/UART.h"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void connectwifi() {
  Serial.print("\t\t[*] Connecting to: ");
  Serial.print(WSSID);
  WiFi.begin(WSSID, WPASS);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.print("\n\t\t[+] Connection established [");
	Serial.print(WiFi.localIP());
	Serial.println("]");

  connecttime();
}

void connecttime() {
  Serial.print("\t\t[*] Retrieving time: ");
  configTime(0, 0, NTPPOOL);
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print("-");
    delay(100);
    now = time(nullptr);
  }
  Serial.print(" ");
  Serial.println(now);
}

void checkUpdates() {
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  Serial.print("\t[+] Updates: ");
  Serial.println(numNewMessages);
  while (numNewMessages) {
    handleMsg(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
}

void handleMsg(int numMsgs) {
  for (int i = 0; i < numMsgs; i++) {
    String chatId = bot.messages[i].chat_id;
    if (checkUser(chatId) == 0) {
      bot.sendMessage(chatId, "Unauthorized user", "");
      continue; // TODO ??
    }

    String text = bot.messages[i].text;
    String from = bot.messages[i].from_name;
    
    if (text == "/start") {
      Serial.println("/start");
      bot.sendMessage(chatId, "Hello!");
    }

    else if (text == "/check") {
      Serial.println("/check");
      bot.sendMessage(chatId, "Checking status...");
      String st = ststring();
      bot.sendMessage(chatId, st);
    }

    else if (text == "/subirPersianas") {
      Serial.println("/subirPersianas");
      bot.sendMessage(chatId, "Subiendo Persianas");
      // Enviar orden de subir las persianas a la FPGA 
    }

    else if (text == "/bajarPersianas") {
      Serial.println("/bajarPersianas");
      bot.sendMessage(chatId, "Bajando Persianas");
      // Enviar orden de bajar las persianas a la FPGA
    }

    
  }
}
