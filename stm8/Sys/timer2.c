#include "timer2.h"

void TIM2_Init(void) //2ms
{
  TIM2_PSCR = 0x04;    // 16��Ƶ1MHz
  TIM2_ARRH = 0x03;
  TIM2_ARRL = 0xE;    // �Զ���װ�ؼĴ���1000�� 1ms
  TIM2_IER  = 0x01;    //����tim2�����ж�
  TIM2_CNTRH= 0x00;    //��ʼֵ
  TIM2_CNTRL= 0x00;    //��ʼֵ
  TIM2_CR1 |= 0x01;   //ʹ�ܼ�������CEN=1
}

