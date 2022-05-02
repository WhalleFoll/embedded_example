#include  "ds18b20.h"

void delay_us(unsigned int n) 
{
  for(;n>0;n--)
  {
    asm("nop"); //��STM8���棬16M����_nop_() ��ʱ�� 333ns
    asm("nop");
    asm("nop");
    asm("nop");
  }
}
void delay_ms(unsigned int time)
{
unsigned int i;
while(time--)
for(i=900;i>0;i--)
delay_us(1);
}

void DQ_DDR(u8 ddr) //���÷���
{  
  if(ddr)
    PI_DDR_DDR4 = 1; //1:�����������
  else
    PI_DDR_DDR4 = 0; //2:���ж���������
  PI_CR1_C14 = 1;
  PI_CR2_C24 = 0;
}
void DS18B20_Rst(void)
{
  //��λDS18B20
    DQ_DDR(1);
    DS18B20_DQ = 0;
    delay_us(480);//��ʱ480΢��	
    DS18B20_DQ = 1;
    delay_us(20);//��ʱ5-60΢��	
}
//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
u8 DS18B20_Check(void) 
{
    u8 retry=0;
    DQ_DDR(0);
    while(DS18B20_IQ && retry<200)
    {
        retry++;
        delay_us(1);
    }

    if(retry>=200)
        return 1;
    else 
        retry = 0;
    while(!DS18B20_IQ && retry<240)
    {
        retry++;
        delay_us(1);
    }

    if(retry>=240)
        return 1;	    
    return 0;
}
//��DS18B20��ȡһ��λ
//����ֵ��1/0
u8 DS18B20_Read_Bit(void) 	 
{
    u8 data;
    DQ_DDR(1);
    DS18B20_DQ = 0;
    delay_us(2);
    DS18B20_DQ = 1;
    DQ_DDR(0);
    delay_us(12);
    if(DS18B20_IQ)
        data=1;
    else 
        data=0;	 
    delay_us(50);           
    return data;
}
//��DS18B20��ȡһ���ֽ�
//����ֵ������������
u8 DS18B20_Read_Byte(void)
{
    u8 i,j,dat;
    dat=0;
    for (i=1;i<=8;i++) 
    {
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}

void DS18B20_Write_Byte(u8 dat)
{
    u8 j;
    u8 testb;
    DQ_DDR(1);
    for(j=0;j<8;j++)
    {
	testb=dat&0x01;
	dat=dat>>1;
	if (testb) 
        {
	     DS18B20_DQ = 0;
	     delay_us(2);  
	     DS18B20_DQ = 1;
	     delay_us(60);
	}
	else 
        {
             DS18B20_DQ = 0;
             delay_us(60);  
             DS18B20_DQ = 1;
             delay_us(2);
	}
    }
}
//��ʼ�¶�ת��
void DS18B20_Start(void) 
{
    DS18B20_Rst();	   
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	//дROMָ�����ROM
    DS18B20_Write_Byte(0x44);	//д����ָ��¶�ת��
}

int DS18B20_Get_Temp(void)
{
  u8 TH, TL;
  int temp;
  DS18B20_Start();  			// ds1820 start convert
  DS18B20_Rst();
  DS18B20_Check();	
  DS18B20_Write_Byte(0xCC);  //дROMָ�����ROM
  DS18B20_Write_Byte(0xBE);  //д����ָ����ݴ���
  TL = DS18B20_Read_Byte();  //����һ���Ͱ�λ
  TH = DS18B20_Read_Byte();  //���ڶ����߰�λ
  temp = (TH<<8)|TL;
  
  if(TH<=0x07)  //�¶�Ϊ��
    return temp;
  else          //�¶�Ϊ��
    return -temp;
}