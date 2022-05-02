#ifndef _LED_H_
#define _LED_H_

#include "sys.h"

#define LED1        PI_ODR_ODR3
#define LED2        PI_ODR_ODR2
#define LED3        PI_ODR_ODR1
#define LED4        PI_ODR_ODR0

void Led_Init(void);

#endif
