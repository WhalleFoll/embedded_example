#include "uart1.h"



u8 RecvData=0;
void Uart1_Init(void)
{
//  0000 0000 1���趨ͨ������λ����1-8-n,��У��
  UART1_CR1=0x00;
//  0000 0000 2���趨ͨ��ֹͣλλ����1λֹͣλ
  UART1_CR3=0x00;
//  3�����ò����ʣ�9600��16MHz�£�
//  UART_DIV=fMASTER������
//  =1600 00009600=1667=0x0683
  UART1_BRR2=0x03;
  UART1_BRR1=0x68;
//  4��ʹ�ܷ��ͣ����չ��ܣ�ʹ�ܽ����ж�
  UART1_CR2=0x2C;//0010 1100
}

void UART1_SendByte(u8 SendData)
{
//  1�����������ɱ�־λ
  UART1_SR &= 0xBF;        //1011 1111
//  2�������������ݷ������ݼĴ���
  UART1_DR = SendData;
//  3���ȴ��������
  while(!(UART1_SR & 0x40));      //0100 0000
//  4�����������ɱ�־λ
  UART1_SR &= 0xBF;
}

u8 UART1_ReceiveByte(void)
{
  u8 buf;
  while(!(UART1_SR & 0x20));  //�ȴ��������
  UART1_SR &= 0xDF;    //��ս��ܱ�־λ
  buf = UART1_DR;     //��������
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
