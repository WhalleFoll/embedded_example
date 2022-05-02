#include "timer3.h"

void TIM3_Init(void) //2ms
{
  TIM3_PSCR = 0x04;    // 16分频1MHz
  TIM3_ARRH = (1000-1)>>8;
  TIM3_ARRL = (1000-1)&0x00ff;    
  TIM3_IER  = 0x01;    //开启tim3更新中断
  TIM3_CNTRH= 0x00;    //初始值
  TIM3_CNTRL= 0x00;    //初始值
  TIM3_CR1 |= 0x01;   //使能计数器，CEN=1
}

