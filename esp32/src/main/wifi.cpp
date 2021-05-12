
#include "include/wifi.h"

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
}
