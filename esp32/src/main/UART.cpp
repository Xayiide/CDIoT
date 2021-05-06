#include "include/UART.h"


void recv() { // TODO: recibir puntero a SoftwareSerial
	// Utiliza SUART
	// ¿Hacer que reciba puntero a SUART?
}

void send() { // TODO: recibir puntero a SoftwareSerial
	// Lo mismo que recv()
}

void pfrcv(byte x) {
	Serial.print("<[");
	Serial.print(x, BIN);
	Serial.print("-0x");
	Serial.print(x, HEX);
	Serial.printl("]>");
}

void decod(byte x) {
	// MSB -> 1 = packet is status data
	//     -> 0 = packet is sensor data
	bitRead(x, 7) ? decodst(x) : decoddat(x);
}


void decodst(byte x) {
	decodprs(x);
	decodac(x);
	decodtemp(x);
}

void decoddat(byte x) {
	Serial.println(" - - - - ERROR - - - - ");
}

// Utiliza st, tiene que recibirlo por parámetro como puntero
void decodprs(byte x) { // TODO: recibir puntero a st
  if (!bitRead(x, 6) && !bitRead(x, 5)) { // 00
    st.stP = SUBIDAS;
    Serial.println("Subidas");
  }
  else if (!bitRead(x, 6) && bitRead(x, 5)) { // 01
    st.stP = SUBIENDO;
    Serial.println("Subiendo");
  }
  else if (bitRead(x, 6) && !bitRead(x, 5)) { // 10
    st.stP = BAJANDO;
    Serial.println("Bajando");
  }
  else if (bitRead(x, 6) && bitRead(x, 5)) { // 11
    st.stP = BAJADAS;
    Serial.println("Bajadas");
  }
}


void decodac(byte x) { // TODO: recibir puntero a st
	if (bitRead(x, 4)) {
		st.aire  = false;
		st.calef = true;
		Serial.println("1 -> calef");
	} else {
		st.aire  = true;
		st.calef = false;
		Serial.println("0 -> aire");
	}
}


void decodtemp(byte x) { // TODO: puntero a struct st
	byte tmp = 0x00;
	for (int i = 3; i > 0; i--) {
		tmp = tmp | bitRead(x, i);
		tmp <<= 1;
	}
	tmp += 14;
	st.temp = tmp;
	Serial.print("tmp: 0b");
	Serial.print(tmp, BIN);
	Serial.print(", ");
	Serial.print(tmp, DEC);
}
