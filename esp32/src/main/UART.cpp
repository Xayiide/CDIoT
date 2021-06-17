#include <Arduino.h>
#include "include/UART.h"
#include "include/common.h"
#include "include/utils.h"

byte fpgastat;

void UartRecv(int n) { 
	byte x, z;
	if (n == 1) { // UART 1 - Data
		z = Serial1.available();
		if (z != 0) {
			x = Serial1.read();
			printRecv(x);
			decodDat(x);
		}
	}
	if (n == 2) { // UART 2 - Status
		z = Serial2.available();
		if (z != 0) {
			x = Serial2.read();
			printRecv(x);
			decodStats(x);
		}
	}
}

void UartSend(int n, byte x) {
	if (n == 1) // UART 1 - Data
		Serial1.write(x);
	if (n == 2) // UART 2 - Status
		Serial2.write(x); // o Software Serial UART o lo que sea
}

void PrintRcv(byte x) {
	Serial.print("<[");
	Serial.print(x, BIN);
	Serial.print("-0x");
	Serial.print(x, HEX);
	Serial.println("]>");
}

