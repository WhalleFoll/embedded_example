#ifndef _TIMER1_H_
#define _TIMER1_H_

#include "sys.h"

void TIM1_Init(void);
void CH1_PWM_SET(unsigned long F_SET_CH1,float Duty_CH1);

#endif