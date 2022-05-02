#include "lcd1602.h"

void LCD1602_Init(void)
{
  //PB
  PB_DDR = 0xFF;  //���ģʽ
  PB_CR1 = 0xFF;  //�������
  PB_CR2 = 0x00;  //����
  //PF0  �����������
  PF_DDR_DDR0 = 1;  
  PF_CR1_C10 = 1;
  PF_CR2_C20 = 0;
  //PF3  �����������
  PF_DDR_DDR3 = 1;
  PF_CR1_C13 = 1;
  PF_CR2_C23 = 0;
  //PF4  �����������
  PF_DDR_DDR4 = 1;
  PF_CR1_C14 = 1;
  PF_CR2_C24 = 0;
  
  PORT = 0xFF; //��ʼ��
  
  LCD1602_Write(0x38,0);  //��������8λ����ʾ2�У�5*7����/�ַ�
  LCD1602_Write(0x0C,0);  //����ʾ������ʾ���
  LCD1602_Write(0x06,0);  //д�ַ����ַ�Զ���һ
  LCD1602_Write(0x01,0);  //��ʾ���㣬����ָ������
}

//д�����������
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
//��ָ��λ����ʾ�ַ�
void LCD1602_DIS_CHAR(u8 x,u8 y,u8 z)
{
  u8 address;
  if(x==1)
    address = y;
  else
    address = 0x40+y;
  //ѡ�е�ַ���趨DDRAM��ַ��
  LCD1602_Write(0x80+address,0);
  //д���ַ�����
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

