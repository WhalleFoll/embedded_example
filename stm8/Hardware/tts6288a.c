#include  "tts6288a.h"

void TTS6288A_Init(void)
{
  UART3_CR1=0x00;   // 无校验
  UART3_CR3=0x00;  //位停止位
  UART3_BRR2=0x03;  // 配置波特率，9600
  UART3_BRR1=0x68;
  UART3_CR2=0x08;//使能发送
}
void TTS6288A_Send(u8* str)
{
  while(*str != '\0')
  {
    UART3_SR &= 0xBF;        
    UART3_DR  = *str++;     //将待发送数据放入数据寄存器
    while(!(UART3_SR & 0x40));      //等待发送完成
    UART3_SR &= 0xBF; //清除发送完成标志位
  }
}