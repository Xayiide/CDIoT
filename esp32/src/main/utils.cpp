#include <Arduino.h>
#include "include/common.h"
#include "include/utils.h"

enum MachineStates {
  RCVDIST,
  RCVLUZ,
  RCVTMP
};


struct stats st;   // extern
struct data datos; // extern
struct MachineStates states;
byte lastByte = 0x00;


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
	bitRead(x, 7) ? decodStats(x) : decodDat(x);
}

void decodStats(byte x) {
  decodPers(x);
  decodAirC(x);
  decodAlarm(x);
  decodTemp(x);
}

void decodPers(byte x) {
  if (bitRead(x, 7) == 0) {
    st.stP = SUBIDAS;
    Serial.println("Subidas");
  }
  else {
    st.stP = BAJADAS;
    Serial.println("Bajadas")
  }
}

void decodAirC(byte x) {
  // [-00-----] -> Ambos apagados
  // [-01-----] -> Calef encendida
  // [-10-----] -> Aire encendido
  if (bitRead(x, 6) == 0) {
    st.aire  = false;
    if (bitRead(x, 5) == 0) { // [-00.....]
      st.calef = false;
      Serial.println("Aire y Calef apagados")
    } else { // [-01.....]
      st.calef = true;
      Serial.println("Calef encendida");
    }
  } else { // [-10.....]
    st.aire  = true;
    Serial.println("Aire encendido");
  }
}

void decodAlarm(byte x) {
  if (bitRead(x, 4) == 1) {
    st.alarm = true;
  } else {
    st.alarm = false;
  }
}

void decodTemp(byte x) {
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



void decodData(byte currByte) {
  if (lastByte == 0x00 && currByte == 0xFF) {

  }
}

String statsStr() {
  String ststring = "";
  ststring += "Persianas ";
  switch(st.stP) {
    case SUBIDAS:
      ststring += "subidas.";
      break;
    case BAJADAS:
      ststring += "bajadas.";
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
