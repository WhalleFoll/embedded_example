#include  "led.h"

void Led_Init(void)
{
  //PI0,PI1,PI2,PI3  低速推挽输出
  PI_DDR |= 0x0f;  
  PI_CR1 |= 0x0f;
  PI_CR2 &= 0xf0;
  //初始化灭
  LED1 = 1;
  LED2 = 1;
  LED3 = 1;
  LED4 = 1;
}

