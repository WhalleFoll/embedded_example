#include  "tts6288a.h"

void TTS6288A_Init(void)
{
  UART3_CR1=0x00;   // ��У��
  UART3_CR3=0x00;  //λֹͣλ
  UART3_BRR2=0x03;  // ���ò����ʣ�9600
  UART3_BRR1=0x68;
  UART3_CR2=0x08;//ʹ�ܷ���
}
void TTS6288A_Send(u8* str)
{
  while(*str != '\0')
  {
    UART3_SR &= 0xBF;        
    UART3_DR  = *str++;     //�����������ݷ������ݼĴ���
    while(!(UART3_SR & 0x40));      //�ȴ��������
    UART3_SR &= 0xBF; //���������ɱ�־λ
  }
}