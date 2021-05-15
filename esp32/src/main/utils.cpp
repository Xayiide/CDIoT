#include <Arduino.h>
#include "include/common.h"
#include "include/utils.h"


struct stats st; // extern

bool checkUser(String c) {
	int chatId = c.toInt();

	for (int i = 0; i < NUSERS; i++)
		if (chatId == USERS[i])
			return true;
	return false;
}

void decod(byte x) {
	// MSB = 1 -> packet is status data
	//     = 0 -> packet is sensor data
	bitRead(x, 7) ? decodst(x) : decoddat(x);
}

void decodst(byte x) {
  decodprs(x);
  decodac(x);
  decodtemp(x);
}

void decodprs(byte x) {
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

void decodac(byte x) {
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

void decodtemp(byte x) {
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
  Serial.println(tmp, DEC);
}

void decoddat(byte x) {
}

String ststring() {
  String ststring = "";
  ststring += "Persianas ";
  switch(st.stP) {
    case SUBIENDO:
      ststring += "subiendo.";
      break;
    case SUBIDAS:
      ststring += "subidas.";
      break;
    case BAJADAS:
      ststring += "bajadas.";
      break;
    case BAJANDO:
      ststring += "bajando.";
      break;
  }
  if (st.aire) {
    ststring += "\nAire: ";
    ststring += String(st.temp);
    ststring += ".";
  } else if (st.calef) {
    ststring += "\nCalefacción: ";
    ststring += String(st.temp);
    ststring += ".";
  }
  return ststring;
}
