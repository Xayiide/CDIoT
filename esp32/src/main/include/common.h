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
	BAJADAS  = 1
};

struct stats {
	enum stPers stP;
	bool aire;
	bool calef;
	bool alarm;
	byte temp;
};

struct sdata {
	byte  dist;
	byte  luz;
	float temp;
};

extern struct stats st;   // utils.cpp
extern struct sdata datos; // utils.cpp
extern const int USERS[NUSERS]; // main.ino
extern byte fpgastat; // UART.cpp // Mantiene el byte a enviar por la UART

#endif // COMMON_H
