#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <UniversalTelegramBot.h>
#include "common.h" // BOT_TOKEN
#include "wifi.h"   // SSID, PASS, secured_client

const unsigned long BOT_MTBS = 1000;
unsigned long       bot_lasttime;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void handleMsg(int);
void checkUpdates();

#endif // TELEGRAM_H
