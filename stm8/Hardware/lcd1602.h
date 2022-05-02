#ifndef _LCD1602_H_
#define _LCD1602_H_

#include "sys.h"

#define LCDRS     PF_ODR_ODR0 //写入位
#define LCDEN     PF_ODR_ODR4 //使能位
#define LCDRW     PF_ODR_ODR3 //读取位
#define PORT      PB_ODR      //数据位


void LCD1602_Write(u8 cmdordata,u8 writetype);
void LCD1602_Init(void);
void LCD1602_DIS_CHAR(u8 x,u8 y,u8 z);
void LCD1602_Print(u8 line, char* str);

#endif

