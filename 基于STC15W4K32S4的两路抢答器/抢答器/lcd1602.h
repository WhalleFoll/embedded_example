#ifndef __LCD1602_H
#define __LCD1602_H
#include "config.h"
#include <intrins.h> 
#include <math.h>    //Keil library   
#include <stdio.h>   //Keil library 
#define LCD_DB        P0
//sbit         LCD_RS=P2^0;   //P2^0是p2.0的意思；LCD_RS与P2.0等效起来，对LCD_RS 读写，就是对P2.0读写 好处在于LCD_RS含义直接明了，写程序多了就会知道有必要de
//sbit         LCD_RW=P2^1;   //P2^1是p2.1的意思
//sbit         LCD_E=P2^2;    //P2^2是p2.2的意思

sbit         LCD_RS=P1^0;   //P2^0是p2.0的意思；LCD_RS与P2.0等效起来，对LCD_RS 读写，就是对P2.0读写 好处在于LCD_RS含义直接明了，写程序多了就会知道有必要de
sbit         LCD_RW=P1^1;   //P2^1是p2.1的意思
sbit         LCD_E=P1^2;    //P2^2是p2.2的意思

/******定义函数****************/
#define uchar unsigned char
#define uint unsigned int
void LCD_init(void);                          //初始化函数
void LCD_write_command(uchar command);        //写指令函数
void LCD_write_data(uchar dat);               //写数据函数
void LCD_disp_char(uchar x,uchar y,uchar dat);//在某个屏幕位置上显示一个字符,X（0-15),y(1-2)
void LCD_disp_str(uchar x,uchar y,uchar *str); //LCD1602显示字符串函数
void delay_n10us(uint n);                     //延时函数

//*********************第二部分DHT90设置   START**************************************** 
sbit SCK  = P2^6;      //定义通讯时钟端口
sbit DATA = P2^7;      //定义通讯数据端口

#define noACK 0             //用于判断是否结束通讯
#define ACK   1             //结束数据传输
                            //adr  command  r/w 
#define STATUS_REG_W 0x06   //000   0011    0 
#define STATUS_REG_R 0x07   //000   0011    1 
#define MEASURE_TEMP 0x03   //000   0001    1 
#define MEASURE_HUMI 0x05   //000   0010    1 
#define RESET        0x1e   //000   1111    0 

/****************定义函数****************/
void s_transstart(void);               //启动传输函数
void s_connectionreset(void);          //连接复位函数
char s_write_byte(unsigned char value);//DHT90写函数
char s_read_byte(unsigned char ack);   //DHT90读函数
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);//测量温湿度函数
void calc_dht90(float *p_humidity ,float *p_temperature);//温湿度补偿
//void dht(void);
#endif

