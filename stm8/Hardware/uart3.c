#include  "uart3.h"

u8 Text1[]={"<V>3"};
u8 Text2[]={"<M>1"};
u8 tts1[]={"<G>����׼������"};
u8 tts2[]={"<G>������ǿ"};
u8 tts3[]={"<G>���ȼ���"};
void UART3_init(void)
{
  UART3_CR1 = 0x00;//ͨ������λ��λ����У��λ��
  UART3_CR3 = 0x00;//һλֹͣλ��
  
  UART3_BRR2 = 0x03;
  UART3_BRR1 = 0x68;//������9600
  
  UART3_CR2 = 0x08;//ʹ��
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

void musics()//�����Ѿ�������ʼ������
{
  UART3_sendstring(Text1,sizeof(Text1));//TTS����
  delay(500);
  
  UART3_sendstring(Text2,sizeof(Text2));//TTS��������
  delay(500);
}

void TTS1()//�����Ѿ�������ʼ������
{
  UART3_sendstring(Text1,sizeof(Text1));//TTS����
  delay(500);
  UART3_sendstring(tts1,sizeof(tts1));//TTS��������
  delay(500);
  
}

void TTS2()//������ǿ
{
  UART3_sendstring(Text1,sizeof(Text1));//TTS����
  delay(500);
  UART3_sendstring(tts2,sizeof(tts2));//TTS��������
  delay(500);
}
void TTS3()//���ȼ���
{
  UART3_sendstring(Text1,sizeof(Text1));//TTS����
  delay(500);
  UART3_sendstring(tts3,sizeof(tts3));//TTS��������
  delay(500);
}