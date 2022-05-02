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

unsigned char  smgduan2[10]={0x40,0x79,0x24,0x30,0x4d,0x12,0x02,0x78,0x00,0x10}; // 带小数点的0-9 
unsigned char  smgduan3[5]={0x8E,0xC8,0xC1,0xBF,0xF9}; // F P U U - 1

// 秒 分   时  日 月  周   年 
// 00 30   20  12  3  五   21
//BCD 码
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


extern unsigned char keyNum;  //矩阵键盘
void Init_Timer();
void switchsmg(unsigned char position,unsigned char dat);


void DS1302_ReadTime();
void DS1302_Config();

void JidianQi(unsigned char i);		//0 关闭机电其
void ReadTemperature();
void BiJiao_times();

void init_system();
void Init_Timer0(); //定时器
void DisplaySMG_DS1302_UI2();
void DisplaySMG_DS18B20_UI1();  //温度
void DisplaySMG_syst_UI3();  //参数设置
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


/*===============定时器0==================*/
/*                定时0.1秒 5秒           */
void Init_Timer0()
{
        TMOD = 0x01;                    
        TH0 = (65536 - 50000) / 256;      
        TL0 = (65536 - 50000) % 256;
        ET0 = 1;                       
        EA = 1;                               
        TR0 = 1;                       
}
/*============定时器0===============*/
unsigned char count = 0;
unsigned char count_led3 = 0;
void SeviceTimer0() interrupt 1
{
        TH0 = (65536 - 50000) / 256;
        TL0 = (65536 - 50000) % 256;
		
		count_led3++;
        HC138(4);
		P0=0xff;
		if(ui_s13==0)		 //温度工作模式	 LED 亮
		{
		   LED2=0;
		}
	    else
		{
			LED2=1;
		}

		
		if(JiDian_i==1)
		{
			if(count_led3 == 2)                    //0.1 时间
	        {
	                LED3 = ~LED3;
					count_led3=0;
	        }
		}
		else
		{
			LED3=1;
		}



	 	if(time_tongzhi==1)	  //整点
	    {
	      count++;
		  LED1 =0;
		  JidianQi(1);  //继电器 亮
	    }
		else
		{
		 LED1 =1;
		}
		
        if(count == 100)       //  5秒时间到        LED1 灭   
        {
                LED1 =1;
				JidianQi(0);  //继电器 灭
                count = 0;
				time_tongzhi=0;
        }
}

/*************************************************************************/
/* 单片机上电后 将DS1302时间 设置为 2022 年 周六 4月 9日 23点 25 分 00秒 */
/*                      DS1302_Config();      //时间初始化  23 时 25分   */
/*************************************************************************/
void main()
{   
	init_system();  //系统初始化
	Init_Timer0();  //定时器初始化
	HC138(4);
    P0=0xff;        

	DS1302_Config();  //时间初始化  23 时 25分
	Read_DS18B20();	  //温度初始化
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


//138高级写法																
void HC138(unsigned char n)
{
	switch(n)
        {																
		 case 4:P2=(P2&0X1F)|0X80;break;//LED 
		 case 5:P2=(P2&0X1F)|0XA0;break;//蜂鸣器，继电器
		 case 6:P2=(P2&0X1F)|0XC0;break;//选位
	     case 7:P2=(P2&0X1F)|0XE0;break;//选段
         default: break;	
		}
}
			

void switchsmg(unsigned char position,unsigned char dat)
{
	
    HC138(6);
	P0=0x01<<position ;  //  <<左移  数码右移位
	HC138(7);
	P0=dat;
}




void DisplaySMG_DS18B20_UI1()  //温度
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

void DisplaySMG_DS1302_UI2()  //时间
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

void DisplaySMG_DS1302_UI2_2()  //时间 2
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

void DisplaySMG_syst_UI3()  //参数设置
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
   if(ui_s13==0)		 //温度工作模式
   {	
   	  	if(((temp/100)%10)*10+(temp/10)%10>temp_sys)	 
		{
		   JidianQi(1);	  //
		   JiDian_i=1;    // 继电器亮
		}
		else
		{
		   JidianQi(0);
		   JiDian_i=0;		// 继电器灭
		}
   }
   else
   {	
        JidianQi(0);	// 继电器灭
   	    BiJiao_times();
   }


   if(ui==0)
   {
     DisplaySMG_DS18B20_UI1(); //页面一
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


void JidianQi(unsigned char i)		//0 打开机电其
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
// 秒 分   时  日 月  周   年 
// 00 30   20  12  3  五   21
//BCD 码
//unsigned char TIME[7] = {0x00, 0x30, 0x09, 0x09, 0x04, 0x06, 0x22};
//switchsmg(3, smgduan[TIME[1]/16]);  //
//delay(10);
//switchsmg(4, smgduan[TIME[1]&0x0f]);
void BiJiao_times()
{
    DS1302_ReadTime();
	if(TIME[1]/16==0 && TIME[1]&0x0f==0 && TIME[0]/16==0 && TIME[0]&0x0f==0)  //分 秒
	{
	   time_tongzhi=1;
	}

}


void init_system()
{
	P2=0xa0;//1010 0000蜂鸣器继电器选通
	P0=0X00;//关闭蜂鸣器、继电器
	P2=0X00;//取消选通
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




