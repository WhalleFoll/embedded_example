#include "timer2.h"

void TIM2_Init(void) //2ms
{
  TIM2_PSCR = 0x04;    // 16分频1MHz
  TIM2_ARRH = 0x03;
  TIM2_ARRL = 0xE;    // 自动重装载寄存器1000， 1ms
  TIM2_IER  = 0x01;    //开启tim2更新中断
  TIM2_CNTRH= 0x00;    //初始值
  TIM2_CNTRL= 0x00;    //初始值
  TIM2_CR1 |= 0x01;   //使能计数器，CEN=1
}

