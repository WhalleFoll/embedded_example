#include "uart1.h"



u8 RecvData=0;
void Uart1_Init(void)
{
//  0000 0000 1、设定通信数据位数，1-8-n,无校验
  UART1_CR1=0x00;
//  0000 0000 2、设定通信停止位位数，1位停止位
  UART1_CR3=0x00;
//  3、配置波特率，9600（16MHz下）
//  UART_DIV=fMASTER波特率
//  =1600 00009600=1667=0x0683
  UART1_BRR2=0x03;
  UART1_BRR1=0x68;
//  4、使能发送，接收功能，使能接收中断
  UART1_CR2=0x2C;//0010 1100
}

void UART1_SendByte(u8 SendData)
{
//  1、清除发送完成标志位
  UART1_SR &= 0xBF;        //1011 1111
//  2、将待发送数据放入数据寄存器
  UART1_DR = SendData;
//  3、等待发送完成
  while(!(UART1_SR & 0x40));      //0100 0000
//  4、清除发送完成标志位
  UART1_SR &= 0xBF;
}

u8 UART1_ReceiveByte(void)
{
  u8 buf;
  while(!(UART1_SR & 0x20));  //等待接收完成
  UART1_SR &= 0xDF;    //清空接受标志位
  buf = UART1_DR;     //接收数据
  return buf;
}

int putchar(int ch)
{
  UART1_SendByte((u8)ch);
  return ch;
}




#pragma vector = 0x14
__interrupt void UART1_RX_IRQHandler()
{
  if(UART1_SR&0x20)
  {
    RecvData=UART1_DR;
    UART1_SR &=0xDF; //1101 1111
  }
}
