/*
  程序说明: IIC总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include "IIC.h"

#define DELAY_TIME 5

#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//总线引脚定义
sbit SDA = P2^1;  /* 数据线 */
sbit SCL = P2^0;  /* 时钟线 */

void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}
//总线启动条件
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 0;
    IIC_Delay(DELAY_TIME);
    SCL = 0;	
}

//总线停止条件
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//发送应答
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0：应答，1：非应答
    IIC_Delay(DELAY_TIME);
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//等待应答
bit IIC_WaitAck(void)
{
    bit ackbit;
	
    SCL  = 1;
    IIC_Delay(DELAY_TIME);
    ackbit = SDA;
    SCL = 0;
    IIC_Delay(DELAY_TIME);
    return ackbit;
}

//通过I2C总线发送数据
void IIC_SendByte(unsigned char byt)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        SCL  = 0;
        IIC_Delay(DELAY_TIME);
        if(byt & 0x80) SDA  = 1;
        else SDA  = 0;
        IIC_Delay(DELAY_TIME);
        SCL = 1;
        byt <<= 1;
        IIC_Delay(DELAY_TIME);
    }
    SCL  = 0;  
}

//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    	SCL = 1;
	IIC_Delay(DELAY_TIME);
	da <<= 1;
	if(SDA) da |= 1;
	SCL = 0;
	IIC_Delay(DELAY_TIME);
    }
    return da;    
}




/**************************************************/
void Write_24C02(unsigned char addr, unsigned char dat)
{
	IIC_Start();						
	IIC_SendByte(0xa0); 	//写操作地址0xa0	
	IIC_WaitAck();				
	IIC_SendByte(addr); 		
	IIC_WaitAck(); 					
	IIC_SendByte(dat); 			
	IIC_WaitAck();					
	IIC_Stop();							
}
 
unsigned char Read_24C02(unsigned char addr)
{
	unsigned char tmp;
	
	IIC_Start();					
	IIC_SendByte(0xa0); 		
	IIC_WaitAck();					
	IIC_SendByte(addr); 		
	IIC_WaitAck(); 					
	
	IIC_Start();						
	IIC_SendByte(0xa1); 		//读操作地址0xa1
	IIC_WaitAck();				
	tmp = IIC_RecByte();		
	//IIC_Ack(0); 		这个是赛方库
    IIC_SendAck(0);		//书上的
	IIC_Stop();							
	return tmp;
}
 
//void Read_Write()
//{
//	dat1 = Read_24C02(0x01);
//	dat2 = Read_24C02(0x03);
//	dat3 = Read_24C02(0x05);
//	
//	dat1 = dat1 + 1;
//	dat2 = dat2 + 2;
//	dat3 = dat3 + 3;
//	
//	if(dat1 > 10)
//		dat1 = 0;
//	if(dat2 > 20)
//		dat2 = 0;
//	if(dat3 > 30)
//		dat3 = 0;
//	
//	Write_24C02(0x01, dat1);
//	delay_ms(1000);
//	Write_24C02(0x03, dat2);
//	delay_ms(1000);
//	Write_24C02(0x05, dat3);
//	delay_ms(1000);
//}