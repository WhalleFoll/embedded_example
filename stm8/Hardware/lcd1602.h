#ifndef _LCD1602_H_
#define _LCD1602_H_

#include "sys.h"

#define LCDRS     PF_ODR_ODR0 //д��λ
#define LCDEN     PF_ODR_ODR4 //ʹ��λ
#define LCDRW     PF_ODR_ODR3 //��ȡλ
#define PORT      PB_ODR      //����λ


void LCD1602_Write(u8 cmdordata,u8 writetype);
void LCD1602_Init(void);
void LCD1602_DIS_CHAR(u8 x,u8 y,u8 z);
void LCD1602_Print(u8 line, char* str);

#endif

