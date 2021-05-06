#ifndef UART_H
#define UART_H

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

void recv();

void send();

void pfrecv(byte);

void decod(byte);

void decodst(byte);

void decoddat(byte);

void decodprs(byte);

void decodac(byte);

void decodtemp(byte);

#endif // UART_H
