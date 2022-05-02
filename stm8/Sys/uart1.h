#ifndef _UART1_H_
#define _UART1_H_

#include "sys.h"

void Uart1_Init(void);
u8 UART1_ReceiveByte(void);
void UART1_SendByte(u8 SendData);

#endif