#include "sys.h"

void delay(u16 Count)
{
  u8 i,j;
  while(Count--)
  {
    for(i=0;i<50;i++)
      for(j=0;j<20;j++);
  }
}

void Clk_Tran_HSE(void)
{
  if(CLK_CMSR != 0xB4)
  {
    CLK_SWCR |= 0x02;  //使能时钟切换
    CLK_SWR   = 0xB4;  //HSE为主时钟源
    while(!(CLK_SWCR&0x08)); //等待完成
    CLK_SWCR = 0; //清除标志位
  }
}
