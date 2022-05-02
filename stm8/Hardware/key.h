#ifndef _KEY_H_
#define _KEY_H_

#include "sys.h"

#define KEY1 PC_IDR_IDR0
#define KEY2 PC_IDR_IDR1
#define KEY3 PC_IDR_IDR2
#define KEY4 PC_IDR_IDR3

void Key_Init(void);
unsigned char Key_Read(void);

#endif