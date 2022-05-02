#ifndef __LCD1602_H
#define __LCD1602_H
#include "config.h"
#include <intrins.h> 
#include <math.h>    //Keil library   
#include <stdio.h>   //Keil library 
#define LCD_DB        P0
//sbit         LCD_RS=P2^0;   //P2^0��p2.0����˼��LCD_RS��P2.0��Ч��������LCD_RS ��д�����Ƕ�P2.0��д �ô�����LCD_RS����ֱ�����ˣ�д������˾ͻ�֪���б�Ҫde
//sbit         LCD_RW=P2^1;   //P2^1��p2.1����˼
//sbit         LCD_E=P2^2;    //P2^2��p2.2����˼

sbit         LCD_RS=P1^0;   //P2^0��p2.0����˼��LCD_RS��P2.0��Ч��������LCD_RS ��д�����Ƕ�P2.0��д �ô�����LCD_RS����ֱ�����ˣ�д������˾ͻ�֪���б�Ҫde
sbit         LCD_RW=P1^1;   //P2^1��p2.1����˼
sbit         LCD_E=P1^2;    //P2^2��p2.2����˼

/******���庯��****************/
#define uchar unsigned char
#define uint unsigned int
void LCD_init(void);                          //��ʼ������
void LCD_write_command(uchar command);        //дָ���
void LCD_write_data(uchar dat);               //д���ݺ���
void LCD_disp_char(uchar x,uchar y,uchar dat);//��ĳ����Ļλ������ʾһ���ַ�,X��0-15),y(1-2)
void LCD_disp_str(uchar x,uchar y,uchar *str); //LCD1602��ʾ�ַ�������
void delay_n10us(uint n);                     //��ʱ����

//*********************�ڶ�����DHT90����   START**************************************** 
sbit SCK  = P2^6;      //����ͨѶʱ�Ӷ˿�
sbit DATA = P2^7;      //����ͨѶ���ݶ˿�

#define noACK 0             //�����ж��Ƿ����ͨѶ
#define ACK   1             //�������ݴ���
                            //adr  command  r/w 
#define STATUS_REG_W 0x06   //000   0011    0 
#define STATUS_REG_R 0x07   //000   0011    1 
#define MEASURE_TEMP 0x03   //000   0001    1 
#define MEASURE_HUMI 0x05   //000   0010    1 
#define RESET        0x1e   //000   1111    0 

/****************���庯��****************/
void s_transstart(void);               //�������亯��
void s_connectionreset(void);          //���Ӹ�λ����
char s_write_byte(unsigned char value);//DHT90д����
char s_read_byte(unsigned char ack);   //DHT90������
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);//������ʪ�Ⱥ���
void calc_dht90(float *p_humidity ,float *p_temperature);//��ʪ�Ȳ���
//void dht(void);
#endif

