#include <Arduino.h>
#include "include/UART.h"
#include "include/common.h"
#include "include/utils.h"

byte fpgastat;

void UartRecv() { 
	byte n = Serial1.available();
	if (n != 0) {
		byte x = Serial1.read();
		printRecv(x);
		decod(x);
	}
}

void UartSend(byte x) {
	Serial1.write(x);
}

void PrintRcv(byte x) {
	Serial.print("<[");
	Serial.print(x, BIN);
	Serial.print("-0x");
	Serial.print(x, HEX);
	Serial.println("]>");
}
