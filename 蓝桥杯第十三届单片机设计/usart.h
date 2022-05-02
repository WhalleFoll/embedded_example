#ifndef __USART_H__
#define __USART_H__
#include <reg52.h>
sfr AUXR=0x8e;
#define u8 unsigned char
#define u16 unsigned int

void PutString(u8 *TXStr);
void SendByte(unsigned char dat);  //SendByte(0x5a)
#endif