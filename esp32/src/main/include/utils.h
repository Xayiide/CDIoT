#ifndef UTILS_H
#define UTILS_H

bool checkUser(String);
void decod(byte);
void decodStats(byte);
void decodData (byte);
void decodPers (byte);
void decodAirC (byte);
void decodTemp (byte);
void decodAlarm(byte);

byte tmpfix(int);



String statsStr();
String sensorStr();

#endif // UTILS_H
