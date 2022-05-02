#include  "uart3.h"

u8 Text1[]={"<V>3"};
u8 Text2[]={"<M>1"};
u8 tts1[]={"<G>程序准备就绪"};
u8 tts2[]={"<G>亮度增强"};
u8 tts3[]={"<G>亮度减弱"};
void UART3_init(void)
{
  UART3_CR1 = 0x00;//通信数据位八位，无校验位；
  UART3_CR3 = 0x00;//一位停止位；
  
  UART3_BRR2 = 0x03;
  UART3_BRR1 = 0x68;//波特率9600
  
  UART3_CR2 = 0x08;//使能
}

void UART3_sendstring(u8 *p,u16 len)
{
  u8 i;
  
  for(i=0;i<len;i++)
  {
    UART3_sendbyte(p[i]);
  }
}
void UART3_sendbyte(u8 data)
{
  UART3_SR&= 0xBF;
  UART3_DR = data;
  while(!(UART3_SR & 0x40));
  UART3_SR&= 0xBF;
  
}

void musics()//程序已就绪，开始工作！
{
  UART3_sendstring(Text1,sizeof(Text1));//TTS音量
  delay(500);
  
  UART3_sendstring(Text2,sizeof(Text2));//TTS播报内容
  delay(500);
}

void TTS1()//程序已就绪，开始工作！
{
  UART3_sendstring(Text1,sizeof(Text1));//TTS音量
  delay(500);
  UART3_sendstring(tts1,sizeof(tts1));//TTS播报内容
  delay(500);
  
}

void TTS2()//亮度增强
{
  UART3_sendstring(Text1,sizeof(Text1));//TTS音量
  delay(500);
  UART3_sendstring(tts2,sizeof(tts2));//TTS播报内容
  delay(500);
}
void TTS3()//亮度减弱
{
  UART3_sendstring(Text1,sizeof(Text1));//TTS音量
  delay(500);
  UART3_sendstring(tts3,sizeof(tts3));//TTS播报内容
  delay(500);
}