#include "buzz.h"




void Buzz_Init(void)
{
  //PD4µÍËÙÍÆÍìÊä³ö
  PD_DDR_DDR4 = 1;  
  PD_CR1_C14 = 1;
  PD_CR2_C24 = 0;
}
