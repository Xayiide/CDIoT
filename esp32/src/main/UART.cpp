#include <Arduino.h>
#include "include/common.h"
#include "include/UART.h"

byte fpgastat;

void recv() { 
	byte n = Serial1.available();
	if (n != 0) {
		byte x = Serial1.read();
		pfrcv(x);
	}
}

void send(byte x) {
	Serial1.write(fpgastat); // extern stat (from common.h)
}

void pfrcv(byte x) {
	Serial.print("<[");
	Serial.print(x, BIN);
	Serial.print("-0x");
	Serial.print(x, HEX);
	Serial.println("]>");
}
