#include "timer3.h"

void TIM3_Init(void) //2ms
{
  TIM3_PSCR = 0x04;    // 16��Ƶ1MHz
  TIM3_ARRH = (1000-1)>>8;
  TIM3_ARRL = (1000-1)&0x00ff;    
  TIM3_IER  = 0x01;    //����tim3�����ж�
  TIM3_CNTRH= 0x00;    //��ʼֵ
  TIM3_CNTRL= 0x00;    //��ʼֵ
  TIM3_CR1 |= 0x01;   //ʹ�ܼ�������CEN=1
}

