#include "timer4.h"

void TIM4_Init(void) //200us
{
  TIM4_PSCR = 0x07; // 128分频125kHz
  TIM4_ARR  = 0x7c; // 自动重装载寄存器125，1ms
  TIM4_IER  = 0x01; //开启tim4更新中断
  TIM4_CNTR = 0x00;    //初始值
  TIM4_CR1 |= 0x01; //使能计数器，CEN=1
}