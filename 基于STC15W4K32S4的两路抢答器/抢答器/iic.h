#ifndef _IIC_H
#define _IIC_H

#include "config.h"
#include "intrins.h"
#include "delay.h"
void IIC_Start(void); 
void IIC_Stop(void);  
bit IIC_WaitAck(void);  
void IIC_SendAck(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
unsigned char IIC_RecByte(void); 

unsigned char Read_24C02(unsigned char addr);
void Write_24C02(unsigned char addr, unsigned char dat);

#endif