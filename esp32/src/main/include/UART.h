#ifndef UART_H
#define UART_H

const byte subirp  = 0b00000010;
const byte bajarp  = 0b00000011;

const byte tmpair  = 0b10000000; // 0b1000----
const byte tmpcal  = 0b01000000; // 0b0100----
const byte maxlux0 = 0b11000000; // 0b1100----
const byte maxlux1 = 0b11010000; // 0b1101----

void urecv();
void usend();
void pfrcv(byte);

void subirpers();
void bajarpers();
void luxumbral();
void tmpumbral();
void dstumbral();

#endif // UART_H
