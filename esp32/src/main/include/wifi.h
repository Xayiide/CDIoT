#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include "common.h" // SSID and PASS


WiFiClientSecure secured_client;

void connectwifi(const char *, const char *);

#endif // WIFI_H
