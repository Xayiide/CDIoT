#include "include/telegram.h"


void handleMsg(int numMsgs) {
	Serial.print("[hndlMsg] ");
	Serial.println(numMsgs);

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

		if (text == "/check") {
			Serial.println("/check");
			bot.sendMessage(chatId, "Checking status...");
		}
		
		if (text == "/subirPersianas" || text == "/bajarPersianas") {
			if (text == "/subirPersianas") {
				Serial.println("/subirPersianas");
				bot.sendMessage(chatId, "Subiendo Persianas");
				/* Enviar orden de subir las persianas a la FPGA */
				/* mvpersianas(up) o algo así */
			}

			if (text == "/bajarPersianas") {
				Serial.println("/bajarPersianas");
				bot.sendMessage(chatId, "Bajando Persianas");
				/* mvpersianas(down) */
			}
		}
	}
}

void checkUpdates() {
	if (millis() - bot_lasttime > BOT_MTBS) {
		int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
		while (numNewMessages) {
			handleMsg(numNewMessages);
			numNewMessages = bot.getUpdates(bot.last_message_receied + 1);
		}
	}
	bot_lasttime = millist();
}
