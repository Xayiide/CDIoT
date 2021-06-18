//A
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

void connectWifi() {
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

  connectTime();
}

void connectTime() {
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

void checkTgUpdates() {
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  Serial.print("\t[+] Updates: ");
  Serial.println(numNewMessages);
  while (numNewMessages) {
    handleMsg(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
}

void handleTgMsg(int numMsgs) {
  for (int i = 0; i < numMsgs; i++) {
    String chatId = bot.messages[i].chat_id;
    if (checkUser(chatId) == 0) {
      bot.sendMessage(chatId, "Unauthorized user", "");
      continue;
    }

    String text = bot.messages[i].text;
    String from = bot.messages[i].from_name;
    
    if (text == "/start") {
      Serial.println("/start");
      bot.sendMessage(chatId, "Hello!");
    }

    else if (text == "/checkStatus") {
      Serial.println("/checkStatus");
      bot.sendMessage(chatId, "Checking status...");
      String st = statsStr();
      bot.sendMessage(chatId, st);
    }

    else if (text == "/checkSensors") {
      Serial.println("/checkSensors");
      bot.sendMessage(chatId, "Checking sensors...");
      String st = sensorStr();
      bot.sendMessage(st);
    }

    else if (text == "/aireON") {
      Serial.println("/aireON");
      bot.sendMessage(chatId, "Aire acondicionado encendido");
      UartSend(2, cmdAireON);
    }

    else if (txt == "/aireOFF") {
      Serial.println("/aireOFF");
      bot.sendMessage(chatId, "Aire acondicionado apagado");
      UartSend(2, cmdAireOFF);
    }

    else if (txt == "calefON") {
      Serial.println("/calefON");
      bot.sendMessage(chatId, "Calefacción encendida");
      UartSend(2, cmdCalefON);
    }

    else if (txt == "calefOFF") {
      Serial.println("/calefOFF");
      bot.sendMessage(chatId, "Calefacción apagada");
      UartSend(2, cmdCalefOFF);
    }

    else if (txt == "tmpAUTO") {
      Serial.println("/tmpAUTO");
      bot.sendMessage(chatId, "Calefacción automática");
      UartSend(2, cmdTempAUTO);

    else if (text == "/subirPersianas") {
      Serial.println("/subirPersianas");
      bot.sendMessage(chatId, "Subiendo Persianas");
      UartSend(2, cmdSubirP);
    }

    else if (text == "/bajarPersianas") {
      Serial.println("/bajarPersianas");
      bot.sendMessage(chatId, "Bajando Persianas");
      UartSend(2, cmdBajarP);
    }

    else if (text == "/persianasAUTO") {
      Serial.println("/PersianasAUTO");
      bot.sendMessage(chatId, "Persianas automáticas");
      UartSend(2, cmdAutoP);
    }

    else if (text.substring(0, 9) == "/umbralTmp") {
      int tmp = toInt(text.substring(11));
      if (tmp < 14 or tmp > 29) {
        bot.sendMessage(chatId, "Rango: [15 - 29]")
      } else {
        byte b = byte(tmp);
        b -= 0xFE; // Restamos 14
        byte aux = umbralTMP;
        aux |= b;
        UartSend(2, aux);
      }
    }

    // TODO: implementar umbral luz que es un poco toston
    else if (text.substring(0, 9) == "/umbralLuz") {
    }

  }
}

void checkAlarm() {
  if (st.alarm == true) {
    for (int i = 0; i < NUSERS; i++) {
      bot.sendMessage(USERS[i], "¡Alarma ON!");
    }
  }
}


