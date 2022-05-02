#ifndef __ADLX345_H_
#define __ADLX234_H_

//---����ͷ�ļ�---//
#include  <STC12C5A60S2.h>	
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>
#include  <GSM.h>
#include  "uart_init.h"
//---�ض���ؼ���---//
#define   uchar unsigned char
#define   uint unsigned int	
#define   DataPort P0    //LCD1602���ݶ˿�
#define	SlaveAddress   0xA6	  //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
                              //ALT  ADDRESS���Žӵ�ʱ��ַΪ0xA6���ӵ�Դʱ��ַΪ0x3A
//�ݻ�����      	
typedef unsigned char  BYTE;
typedef unsigned short WORD;	
                     


//---����ʹ�õ�IO��---//
sbit	  SCL=P0^6;      //IICʱ�����Ŷ���
sbit 	  SDA=P0^7;      //IIC�������Ŷ���
sbit      LED=P2^0;

sbit      LCM_RS=P2^6;   //LCD1602����˿�		
sbit      LCM_RW=P2^5;   //LCD1602����˿�		
sbit      LCM_EN=P2^7;   //LCD1602����˿�


//---����ȫ�ֺ���---//
void delay1(unsigned int k);

void Init_ADXL345(void);             //��ʼ��ADXL345

//void WriteDataLCM(uchar dataW);
//void WriteCommandLCM(uchar CMD,uchar Attribc);
//void DisplayOneChar(uchar X,uchar Y,uchar DData);
void conversion(uint temp_data);

void  Single_Write_ADXL345(uchar REG_Address,uchar REG_data);   //����д������
uchar Single_Read_ADXL345(uchar REG_Address);                   //������ȡ�ڲ��Ĵ�������
void  Multiple_Read_ADXL345();                                  //�����Ķ�ȡ�ڲ��Ĵ�������
//------------------------------------
void Delay5us();
void Delay5ms();
void ADXL345_Start();
void ADXL345_Stop();
void ADXL345_SendACK(bit ack);
bit  ADXL345_RecvACK();
void ADXL345_SendByte(BYTE dat);
BYTE ADXL345_RecvByte();
void ADXL345_ReadPage();
void ADXL345_WritePage();
void ADXL345_deal();

#endif
