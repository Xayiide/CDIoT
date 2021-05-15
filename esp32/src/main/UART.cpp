#include <Arduino.h>
#include "include/UART.h"
#include "include/common.h"
#include "include/utils.h"

byte fpgastat;

void urecv() { 
	byte n = Serial1.available();
	if (n != 0) {
		byte x = Serial1.read();
		pfrcv(x);
		decod(x);
	}
}

void usend(byte x) {
	Serial1.write(fpgastat); // extern stat (from common.h)
}

void pfrcv(byte x) {
	Serial.print("<[");
	Serial.print(x, BIN);
	Serial.print("-0x");
	Serial.print(x, HEX);
	Serial.println("]>");
}
