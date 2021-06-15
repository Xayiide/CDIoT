#ifndef COMMON_H
#define COMMON_H

#define BAUDRATE  115200
#define BOT_TOKEN "" // VACIAR ANTES DE PUSHEAR
#define NUSERS 2

#define WSSID   ""         // main.ino
#define WPASS   ""  // main.ino
#define NTPPOOL "pool.ntp.org" // WiFi.cpp

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

extern struct stats st; // utils.cpp
extern const int USERS[NUSERS]; // main.ino
extern byte fpgastat; // UART.cpp // Mantiene el byte a enviar por la UART

#endif // COMMON_H
