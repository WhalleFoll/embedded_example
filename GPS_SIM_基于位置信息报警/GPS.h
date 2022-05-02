#ifndef __GPS_H__
#define __GPS_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uart_init.h>
#include < gsm.h   >
//函数或者变量声明
extern void Delay_ms(unsigned int n);
extern void GPS_deal();
extern void UTCDate2LocalDate(void);
extern bit IsLeapYear(unsigned int uiYear);	
extern unsigned char GetMaxDay(unsigned char Month_Value,unsigned int Year_Value);

extern unsigned char RX_Buffer[72];
extern unsigned char RX_Count;
extern unsigned char Hour,Min_High,Min_Low,Sec_High,Sec_Low;
extern unsigned char Month,Day,Month_High, Month_Low,Day_Low ,Day_High, Year_High,Year_Low;
extern unsigned int Year;
extern unsigned char MaxDay;

extern bit Flag_GPS_OK;

#endif