#include <reg52.h>
#include "keyscan.h"
//#include "key.h"
//#include "usart.h"
//#include "iic.h"
#include "DS1302.h"
#include "onewire.h"
sfr AUXR=0x8e;
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;

sbit R1 = P3^0;  
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;


sbit C3 = P3^5;
sbit C4 = P3^4;

unsigned char  smgduan[16]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,
                                0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,
                                0x86,0x8E}; // 0-9 

unsigned char  smgduan2[10]={0x40,0x79,0x24,0x30,0x4d,0x12,0x02,0x78,0x00,0x10}; // ��С�����0-9 
unsigned char  smgduan3[5]={0x8E,0xC8,0xC1,0xBF,0xF9}; // F P U U - 1

// �� ��   ʱ  �� ��  ��   �� 
// 00 30   20  12  3  ��   21
//BCD ��
unsigned char TIME[7] = {0x00, 0x25, 0x23, 0x09, 0x04, 0x06, 0x22};

unsigned char code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
unsigned char code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

unsigned char ui = 0;
unsigned char ui_s13 = 0;

unsigned char tamp_dat = 0;
unsigned int temp_sys = 23;
unsigned int temp = 0;
unsigned char time_tongzhi = 0;
unsigned char JiDian_i = 0;


extern unsigned char keyNum;  //�������
void Init_Timer();
void switchsmg(unsigned char position,unsigned char dat);


void DS1302_ReadTime();
void DS1302_Config();

void JidianQi(unsigned char i);		//0 �رջ�����
void ReadTemperature();
void BiJiao_times();

void init_system();
void Init_Timer0(); //��ʱ��
void DisplaySMG_DS1302_UI2();
void DisplaySMG_DS18B20_UI1();  //�¶�
void DisplaySMG_syst_UI3();  //��������
void DisplaySMG_DS1302_UI2_2();
void HC138(unsigned char n);
void shua_xin();
	
void delay(unsigned int ms)
{
	 unsigned int i;
	 while(ms--)
		{
			for(i=120;i>0;i--);
		}
}


/*===============��ʱ��0==================*/
/*                ��ʱ0.1�� 5��           */
void Init_Timer0()
{
        TMOD = 0x01;                    
        TH0 = (65536 - 50000) / 256;      
        TL0 = (65536 - 50000) % 256;
        ET0 = 1;                       
        EA = 1;                               
        TR0 = 1;                       
}
/*============��ʱ��0===============*/
unsigned char count = 0;
unsigned char count_led3 = 0;
void SeviceTimer0() interrupt 1
{
        TH0 = (65536 - 50000) / 256;
        TL0 = (65536 - 50000) % 256;
		
		count_led3++;
        HC138(4);
		P0=0xff;
		if(ui_s13==0)		 //�¶ȹ���ģʽ	 LED ��
		{
		   LED2=0;
		}
	    else
		{
			LED2=1;
		}

		
		if(JiDian_i==1)
		{
			if(count_led3 == 2)                    //0.1 ʱ��
	        {
	                LED3 = ~LED3;
					count_led3=0;
	        }
		}
		else
		{
			LED3=1;
		}



	 	if(time_tongzhi==1)	  //����
	    {
	      count++;
		  LED1 =0;
		  JidianQi(1);  //�̵��� ��
	    }
		else
		{
		 LED1 =1;
		}
		
        if(count == 100)       //  5��ʱ�䵽        LED1 ��   
        {
                LED1 =1;
				JidianQi(0);  //�̵��� ��
                count = 0;
				time_tongzhi=0;
        }
}

/*************************************************************************/
/* ��Ƭ���ϵ�� ��DS1302ʱ�� ����Ϊ 2022 �� ���� 4�� 9�� 23�� 25 �� 00�� */
/*                      DS1302_Config();      //ʱ���ʼ��  23 ʱ 25��   */
/*************************************************************************/
void main()
{   
	init_system();  //ϵͳ��ʼ��
	Init_Timer0();  //��ʱ����ʼ��
	HC138(4);
    P0=0xff;        

	DS1302_Config();  //ʱ���ʼ��  23 ʱ 25��
	Read_DS18B20();	  //�¶ȳ�ʼ��
	ScanKeys();
	delay(100);
	
	while(1)
		{
		 shua_xin();   //
		 ScanKeys();
		 switch(keyNum)
		 {
			 case 17:{
			          if(ui_s13==1)
					  {
				  	  		R3 = 0;
					        R2 = R1 = R4 = 1;
					        C3 = C4 = 1;
					        if(C4 == 0)			  // s17
					        {
							       while(C4 == 0)
								   {
								   	 DisplaySMG_DS1302_UI2_2();							
								   }
                            }
					  }
					  else
					  {
					   temp_sys--;
					  }			          
			         };break;

			 case 16:{					 
					  temp_sys++; 
					 };break;
								  
			 case 13:{					 
					  ui_s13++;
					  if(ui_s13==2)
					  {
					  	ui_s13=0;
					  }					      
					 };break;
			 case 12:{					 
					  ui++;
					  if(ui==3)
					  {
					  	ui=0;
					  }					      
					 };break;
			 default: break;
		 }
		 
		}
}


//138�߼�д��																
void HC138(unsigned char n)
{
	switch(n)
        {																
		 case 4:P2=(P2&0X1F)|0X80;break;//LED 
		 case 5:P2=(P2&0X1F)|0XA0;break;//���������̵���
		 case 6:P2=(P2&0X1F)|0XC0;break;//ѡλ
	     case 7:P2=(P2&0X1F)|0XE0;break;//ѡ��
         default: break;	
		}
}
			

void switchsmg(unsigned char position,unsigned char dat)
{
	
    HC138(6);
	P0=0x01<<position ;  //  <<����  ��������λ
	HC138(7);
	P0=dat;
}




void DisplaySMG_DS18B20_UI1()  //�¶�
{
    //ReadTemperature();
	switchsmg(0, smgduan3[2]);  //	   U
	delay(10);
	switchsmg(1, smgduan[1]);  //	   1
	delay(10);
	
	switchsmg(5, smgduan[(temp/100)%10]);  //
	delay(10);
    switchsmg(6, smgduan2[(temp/10)%10]);  //
	delay(10);
    switchsmg(7, smgduan[temp%10]);  //	
	delay(10);
    
}

void DisplaySMG_DS1302_UI2()  //ʱ��
{   
    DS1302_ReadTime();
	switchsmg(0, smgduan3[2]);  // U
	delay(10);
	switchsmg(1, smgduan[2]);  // 2 
	delay(10);
				 
	switchsmg(3, smgduan[TIME[2]/16]);  //
	delay(10);
    switchsmg(4, smgduan[TIME[2]&0x0f]);  
	delay(10);

    switchsmg(5, smgduan3[3]);  //	   -
	delay(10);
	switchsmg(6, smgduan[TIME[1]/16]);  //	
	delay(10);
    switchsmg(7, smgduan[TIME[1]&0x0f]);  //	
	delay(10);
     

}

void DisplaySMG_DS1302_UI2_2()  //ʱ�� 2
{   
    DS1302_ReadTime();
	switchsmg(0, smgduan3[2]);  // U
	delay(10);
	switchsmg(1, smgduan[2]);  // 2 
	delay(10);
				 
	switchsmg(3, smgduan[TIME[1]/16]);  //
	delay(10);
    switchsmg(4, smgduan[TIME[1]&0x0f]);  
	delay(10);

    switchsmg(5, smgduan3[3]);  //	   -
	delay(10);
	switchsmg(6, smgduan[TIME[0]/16]);  //	
	delay(10);
    switchsmg(7, smgduan[TIME[0]&0x0f]);  //	
	delay(10);
     

}

void DisplaySMG_syst_UI3()  //��������
{
    
	switchsmg(0, smgduan3[2]);  //	   U
	delay(10);
	switchsmg(1, smgduan[3]);  //	   3
	delay(10);
	
	switchsmg(6, smgduan[temp_sys/10]);  //
	delay(10);
    switchsmg(7, smgduan[temp_sys%10]);  //
	delay(10);
	
    
}

void shua_xin()
{
   ReadTemperature();
   DS1302_ReadTime();
   if(ui_s13==0)		 //�¶ȹ���ģʽ
   {	
   	  	if(((temp/100)%10)*10+(temp/10)%10>temp_sys)	 
		{
		   JidianQi(1);	  //
		   JiDian_i=1;    // �̵�����
		}
		else
		{
		   JidianQi(0);
		   JiDian_i=0;		// �̵�����
		}
   }
   else
   {	
        JidianQi(0);	// �̵�����
   	    BiJiao_times();
   }


   if(ui==0)
   {
     DisplaySMG_DS18B20_UI1(); //ҳ��һ
   }
   else if(ui==1)
   {
      DisplaySMG_DS1302_UI2();
   }
   else if(ui==2)
   {
      DisplaySMG_syst_UI3();
   }
}


void JidianQi(unsigned char i)		//0 �򿪻�����
{
	 HC138(5); //
	 if(i==1)
	 {
	  	P0=0x10;
	 }
	 else
	 {
	  P0=0x00;
	 }

}

void ReadTemperature()
{
        unsigned char LSB,MSB ;
        
        Init_DS18B20(); 
        Write_DS18B20(0xCC); 
        Write_DS18B20(0x44); 
        Init_DS18B20(); 
        Write_DS18B20(0xCC); 
        Write_DS18B20(0xBE); 
        LSB = Read_DS18B20(); 
        MSB = Read_DS18B20(); 
        
        temp = 0x0000;
        temp = MSB;
        temp <<= 8;
        temp = temp | LSB;
        temp >>= 4;
        temp = temp*10;
        temp = temp + (LSB&0x0f)*0.625;
        
        if((MSB>>4) == 0x0f)
        {
           temp |= 0x8000;
        }

}
// �� ��   ʱ  �� ��  ��   �� 
// 00 30   20  12  3  ��   21
//BCD ��
//unsigned char TIME[7] = {0x00, 0x30, 0x09, 0x09, 0x04, 0x06, 0x22};
//switchsmg(3, smgduan[TIME[1]/16]);  //
//delay(10);
//switchsmg(4, smgduan[TIME[1]&0x0f]);
void BiJiao_times()
{
    DS1302_ReadTime();
	if(TIME[1]/16==0 && TIME[1]&0x0f==0 && TIME[0]/16==0 && TIME[0]&0x0f==0)  //�� ��
	{
	   time_tongzhi=1;
	}

}


void init_system()
{
	P2=0xa0;//1010 0000�������̵���ѡͨ
	P0=0X00;//�رշ��������̵���
	P2=0X00;//ȡ��ѡͨ
}

void DS1302_Config()  //
{
        unsigned char n;
        Ds1302_Single_Byte_Write(0x8E,0x00);
        for (n=0; n<7; n++)
        {
                Ds1302_Single_Byte_Write(WRITE_RTC_ADDR[n],TIME[n]);        
        }
        Ds1302_Single_Byte_Write(0x8E,0x80);
}

void DS1302_ReadTime()
{
        unsigned char n;
        for (n=0; n<7; n++)
        {
				
				
				  TIME[n] = Ds1302_Single_Byte_Read(READ_RTC_ADDR[n]);				
                
        } 

		while(TIME[1]/16==15)
		{
				 TIME[1] = Ds1302_Single_Byte_Read(READ_RTC_ADDR[1]);
		}
		 while(TIME[2]/16==15)
		{
				 TIME[2] = Ds1302_Single_Byte_Read(READ_RTC_ADDR[2]);
		}        
}




