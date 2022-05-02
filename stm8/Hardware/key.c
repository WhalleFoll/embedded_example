#include  "key.h"

void Key_Init(void)
{
  //PC0,PC1,PC2,PC3无中断上拉输入
  PC_DDR &= 0xf0; 
  PC_CR1 |= 0x0f;
  PC_CR2 &= 0xf0;
}

unsigned char Key_Read(void)
{
  if(KEY1==0) 
  { delay(10);
    if(KEY1==0)
    return 1;
  }
  
  if(KEY2==0)
  {
    delay(10);
    if(KEY2==0)
    return 2;
  }
  if(KEY3==0) return 3;
  if(KEY4==0) return 4;
  return 0;
}
