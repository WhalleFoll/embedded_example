#include "timer4.h"

void TIM4_Init(void) //200us
{
  TIM4_PSCR = 0x07; // 128��Ƶ125kHz
  TIM4_ARR  = 0x7c; // �Զ���װ�ؼĴ���125��1ms
  TIM4_IER  = 0x01; //����tim4�����ж�
  TIM4_CNTR = 0x00;    //��ʼֵ
  TIM4_CR1 |= 0x01; //ʹ�ܼ�������CEN=1
}