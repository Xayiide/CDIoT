#ifndef UART_H
#define UART_H

const byte cmdAireON    = 0b00010001;
const byte cmdAireOFF   = 0b00010000;
const byte cmdCalefON   = 0b00010101;
const byte cmdCalefOFF  = 0b00010100;
const byte cmdTempAUTO  = 0b00011000;

const byte cmdSubirP = 0b00100001;
const byte cmdBajarP = 0b00100000;
const byte cmdAutoP  = 0b00110000;

const byte umbralTMP = 0b01000000;
const byte umbralLUZ = 0b10000000;



void UartRecv(int n);
void UartSend(int n, byte x);
void PrintRecv(byte);

#endif // UART_H
