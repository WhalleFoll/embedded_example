#include "lcd1602.h"

void LCD1602_Init(void)
{
  //PB
  PB_DDR = 0xFF;  //输出模式
  PB_CR1 = 0xFF;  //推挽输出
  PB_CR2 = 0x00;  //低速
  //PF0  低速推挽输出
  PF_DDR_DDR0 = 1;  
  PF_CR1_C10 = 1;
  PF_CR2_C20 = 0;
  //PF3  低速推挽输出
  PF_DDR_DDR3 = 1;
  PF_CR1_C13 = 1;
  PF_CR2_C23 = 0;
  //PF4  低速推挽输出
  PF_DDR_DDR4 = 1;
  PF_CR1_C14 = 1;
  PF_CR2_C24 = 0;
  
  PORT = 0xFF; //初始高
  
  LCD1602_Write(0x38,0);  //数据总线8位，显示2行，5*7点阵/字符
  LCD1602_Write(0x0C,0);  //开显示，不显示光标
  LCD1602_Write(0x06,0);  //写字符后地址自动加一
  LCD1602_Write(0x01,0);  //显示清零，数据指针清零
}

//写入命令或数据
void LCD1602_Write(u8 cmdordata,u8 writetype)
{
  if(writetype == 0)
    LCDRS = 0;
  else
    LCDRS = 1;
  LCDRW = 0;
  PORT = cmdordata;
  delay(5);
  LCDEN = 1;
  delay(5);
  LCDEN = 0;
}
//在指定位置显示字符
void LCD1602_DIS_CHAR(u8 x,u8 y,u8 z)
{
  u8 address;
  if(x==1)
    address = y;
  else
    address = 0x40+y;
  //选中地址（设定DDRAM地址）
  LCD1602_Write(0x80+address,0);
  //写入字符代码
  LCD1602_Write(z,1);
}

void LCD1602_Print(u8 line, char* str) 
{
  static u8 i=0;
  while(*str != '\0')
  {
    LCD1602_DIS_CHAR(line, i++, *str++);
  }
  i = 0;
}

