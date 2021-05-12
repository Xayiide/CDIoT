#ifndef COMMON_H
#define COMMON_H

#define BAUDRATE  115200
#define BOT_TOKEN "" // VACIAR ANTES DE PUSHEAR
#define NUSERS    4

const char *SSID = ""; // WiFi SSID
const char *PASS = ""; // WiFi password

enum stPers {
	SUBIDAS  = 0,
	SUBIENDO = 1,
	BAJANDO  = 2,
	BAJADAS  = 3
};

struct stats {
	enum stPers stP;
	bool aire;
	bool calef;
	byte temp;
};

extern stats st;
extern const int USERS[NUSERS];
extern byte stat; // Mantiene el byte a enviar por la UART

#endif // COMMON_H
