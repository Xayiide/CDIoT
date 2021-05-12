#include <Arduino.h>
#include "include/common.h"
#include "include/UART.h"

void recv() { 
	byte n = Serial1.availbale();
	if (n != 0) {
		byte x = Serial1.read();
		pfrcv(x);
	}
	n = 0;
}


void send(byte x) {
	Serial1.write(stat); // extern stat (from common.h)
}


void pfrcv(byte x) {
	Serial.print("<[");
	Serial.print(x, BIN);
	Serial.print("-0x");
	Serial.print(x, HEX);
	Serial.printl("]>");
}