#ifndef __ADLX345_H_
#define __ADLX234_H_

//---包含头文件---//
#include  <STC12C5A60S2.h>	
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>
#include  <GSM.h>
#include  "uart_init.h"
//---重定义关键词---//
#define   uchar unsigned char
#define   uint unsigned int	
#define   DataPort P0    //LCD1602数据端口
#define	SlaveAddress   0xA6	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A
//据缓存区      	
typedef unsigned char  BYTE;
typedef unsigned short WORD;	
                     


//---定义使用的IO口---//
sbit	  SCL=P0^6;      //IIC时钟引脚定义
sbit 	  SDA=P0^7;      //IIC数据引脚定义
sbit      LED=P2^0;

sbit      LCM_RS=P2^6;   //LCD1602命令端口		
sbit      LCM_RW=P2^5;   //LCD1602命令端口		
sbit      LCM_EN=P2^7;   //LCD1602命令端口


//---定义全局函数---//
void delay1(unsigned int k);

void Init_ADXL345(void);             //初始化ADXL345

//void WriteDataLCM(uchar dataW);
//void WriteCommandLCM(uchar CMD,uchar Attribc);
//void DisplayOneChar(uchar X,uchar Y,uchar DData);
void conversion(uint temp_data);

void  Single_Write_ADXL345(uchar REG_Address,uchar REG_data);   //单个写入数据
uchar Single_Read_ADXL345(uchar REG_Address);                   //单个读取内部寄存器数据
void  Multiple_Read_ADXL345();                                  //连续的读取内部寄存器数据
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
