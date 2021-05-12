#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h> // No se si hace falta esto

bool checkUser(String);
void decod(byte);
void decodst(byte);
void decoddat(byte);
void decodprs(byte);
void decodac(byte);
void decodtemp(byte);

#endif // UTILS_H
