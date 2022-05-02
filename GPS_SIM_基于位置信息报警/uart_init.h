#ifndef __UART_INIT_H_
#define __UART_INIT_H_

//---包含头文件---//
#include "stc12c5a60s2.h"
#include "intrins.h"

//---重定义关键词---//
#define uint unsigned int
#define uchar unsigned char	
	

#define FOSC 11059200L      //System frequency
#define BAUD 115200          //UART baudrate
#define BAUD1 9600          //UART baudrate
/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity
#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3

#define PARITYBIT EVEN_PARITY   //Testing even parity

//---定义ds1302使用的IO口---//


//---定义全局函数---//
void SendData1(uchar dat);
void SendString1(char *s);
void SendData2(uchar dat);
void SendString2(char *s);
void uart1_init();
void uart2_init();

#endif