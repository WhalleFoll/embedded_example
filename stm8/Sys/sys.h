#ifndef _SYS_H_
#define _SYS_H_

#include "iostm8s208mb.h"
#include <stdio.h>

typedef unsigned char u8;
typedef unsigned short  u16;
typedef unsigned long u32;

void delay(u16 Count);
void Clk_Tran_HSE(void);

#endif



