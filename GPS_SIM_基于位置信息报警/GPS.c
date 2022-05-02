
#include "GPS.h"

//定义变量
unsigned char KEY_NUM = 0;
bit Page = 0;
unsigned char xdata Display_GPGGA_Buffer[68];
unsigned char xdata Display_GPRMC_Buffer[68];
bit Flag_OV = 0;
bit Flag_Calc_GPGGA_OK = 0;
bit Flag_Calc_GPRMC_OK = 0;
unsigned char RX_Buffer[72];
unsigned char RX_Count = 0;
unsigned char Hour = 0,Min_High = 0,Min_Low = 0,Sec_High = 0,Sec_Low = 0,Min_Low1 = 0;
unsigned char Month = 0,Day = 0,Month_High = 0, Month_Low = 0,Day_Low = 0 ,Day_High = 0, Year_High = 0,Year_Low = 0;
unsigned int Year = 0;
bit Flag_GPS_OK = 0;
unsigned char MaxDay = 0;

unsigned char code SMS_send_front[]="设备现在所处的位置";
void N_S_deal(void);
void E_W_deal(void);
//****************************************************
//主函数
//****************************************************
void GPS_deal()
{
	unsigned char i = 0;
  //ES=0;
//	   GSM_TEXT();
//     SendString2(SMS_send_3);
//	   SendString2(PhoneCall_11);
//     SendString2("\r\n");   //发送回车
//     Delay_ms(3000);  
//	   SendString2(SMS_send_front);
//	SendString2("\r\n");
     //SendData2('1');
		if(Flag_GPS_OK == 1 && RX_Buffer[4] == 'G' && RX_Buffer[6] == ',' && RX_Buffer[13] == '.')			//确定是否收到"GPGGA"这一帧数据
		{
			for( i = 0; i < 68 ; i++)
			{
				Display_GPGGA_Buffer[i] = RX_Buffer[i];	
			}
			Hour = (Display_GPGGA_Buffer[7]-0x30)*10+(Display_GPGGA_Buffer[8]-0x30)+8;			//UTC时间转换到北京时间		UTC+8
																								//0x30为ASCII转换为数字
			if( Hour >= 24)				//溢出
			{
				Hour %= 24;				//获取当前Hour
				Flag_OV = 1;			//日期进位
			}
			else
			{
				Flag_OV = 0;
			}

			Min_High = Display_GPGGA_Buffer[9];
			Min_Low = Display_GPGGA_Buffer[10];
	
			Sec_High = Display_GPGGA_Buffer[11];
			Sec_Low = Display_GPGGA_Buffer[12];

			Flag_Calc_GPGGA_OK = 1;
		}

		if(Flag_Calc_GPGGA_OK == 1)
		{
			Flag_Calc_GPGGA_OK = 0;
	    
     //SendData2('1');
			SendString2("\r\n");
//			SendString2("TIME: \r\n");

//			SendData2(Hour/10+0x30);
//			SendData2(Hour%10+0x30);

//			SendData2(':');

//			SendData2(Min_High);
//			SendData2(Min_Low);

//			SendData2(':');
//	
//			SendData2(Sec_High);
//			SendData2(Sec_Low);
//      Delay_ms(1000);
//			SendString2("\r\n");
//			SendString2("HIGH: ");
//			SendData2(Display_GPGGA_Buffer[54]);	
//			SendData2(Display_GPGGA_Buffer[55]);	
//			SendData2(Display_GPGGA_Buffer[56]);	
//			SendData2(Display_GPGGA_Buffer[57]);
//			SendString2("m\r\n");
			if((Min_Low-Min_Low1)>=1)
			{
			GSM_TEXT();
			SendString2(SMS_send_front);
			SendString2("\r\n");
			//Delay_ms(3000);
    
	   // SendData2(Min_Low);
			//Delay_ms(3000);
			if(Display_GPGGA_Buffer[28]=='N')//N 或者 S
			{	
				SendString2("北纬:");
         				
      }
			else SendString2("南纬:");        			
			N_S_deal();
			SendString2("\r\n");	
//Delay_ms(3000);			
      if(Display_GPGGA_Buffer[42]=='E')	//E 或者 W
			{	
				SendString2("东经:");		
      }
			else SendString2("西经:");	
		  E_W_deal();
			SendString2("\r\n");
			//Delay_ms(1000);
      SendData2(0x1a);  //发送短息内容结束符对应的ASCII为0x1a
			SendString2("\r\n");
      ES=1;  
			
		}			
			Min_Low1=Min_Low;
			if(Min_Low==9)
				Min_Low1=0;
		}
		
		if(Flag_GPS_OK == 1 && RX_Buffer[4] == 'M' && RX_Buffer[52] == ',' && RX_Buffer[59] == ',')			//确定是否收到"GPRMC"这一帧数据
		{
			for( i = 0; i < 68 ; i++)
			{
				Display_GPRMC_Buffer[i] = RX_Buffer[i];	
			}

			Year_High = Display_GPRMC_Buffer[57];
			Year_Low = Display_GPRMC_Buffer[58];

			Month_High = Display_GPRMC_Buffer[55];
			Month_Low = Display_GPRMC_Buffer[56];

			Day_High = Display_GPRMC_Buffer[53];
			Day_Low = Display_GPRMC_Buffer[54];


			if(Flag_OV == 1)			//有进位
			{
				UTCDate2LocalDate();			//UTC日期转换为北京时间		
			}

			Flag_Calc_GPRMC_OK = 1;
		}

		if(Flag_Calc_GPRMC_OK == 1)
		{
			Flag_Calc_GPRMC_OK = 0;

//			SendString2("20");
//			SendData2(Year_High);
//			SendData2(Year_Low);
//			SendData2('-');
//	
//			SendData2(Month_High);
//			SendData2(Month_Low);
//			SendData2('-');
//	
//			SendData2(Day_High);
//			SendData2(Day_Low);

//			SendString2("\r\n");
//			
//			
//			SendString2("Speed:");			

//			SendData2(Display_GPRMC_Buffer[46]);		
//			SendData2(Display_GPRMC_Buffer[47]);		
//			SendData2(Display_GPRMC_Buffer[48]);			
//			SendData2(Display_GPRMC_Buffer[49]);	
//			SendData2(Display_GPRMC_Buffer[50]);
//			
//			SendString2("\r\n");			
		}		
	//SendData2('2');
		 //SendData2(0x1a);  //发送短息内容结束符对应的ASCII为0x1a
//     ES=1;
//      Delay_ms(1000);
//     Delay_ms(5000);   
}
//****************************************************
//UTC日期与当地日期转换
//****************************************************
void UTCDate2LocalDate(void)
{
	Day = (Day_High - 0x30) * 10 + (Day_Low-0x30) + 1;		//日  加一
	Month = (Month_High - 0x30) * 10 + (Month_Low - 0x30);
	Year = 2000 + (Year_High - 0x30) * 10 + (Year_Low - 0x30);
	
	MaxDay = GetMaxDay(Month,Year);				//获取当月 天数 最大值
	if(Day > MaxDay)		//溢出
	{
		Day = 1;
		Month += 1;
		if(Month > 12)
		{
			Year+=1;
		}
	}

	Day_High = Day/10 + 0x30;				//转换日期值为ASCII
	Day_Low = Day%10 + 0x30;

	Month_High = Month/10 + 0x30;			//转换月份值为ASCII
	Month_Low = Month%10 + 0x30;

	Year_High = Year%100/10 + 0x30;			//转换年份值为ASCII
	Year_Low = Year%10 + 0x30;			
}

//****************************************************
//获取当月日期最大值
//****************************************************
unsigned char GetMaxDay(unsigned char Month_Value,unsigned int Year_Value)
{
	unsigned char iDays;
	switch(Month_Value)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			{
				iDays = 31;
			}
			break;
		case 2:
			{
				//2月份比较特殊，需要根据是不是闰年来判断当月是28天还29天
				iDays = IsLeapYear(Year_Value)?29:28;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			{
				iDays = 30;
			}
			break;
		default : break;
	}
	return(iDays);						
}

//****************************************************
//闰年检测
//****************************************************
bit IsLeapYear(unsigned int uiYear)
{
	return (((uiYear%4)==0)&&((uiYear%100)!=0))||((uiYear%400)==0);
}


//****************************************************
//MS延时函数(12M晶振下测试)
//****************************************************
void Delay_ms(unsigned int n)
{
	unsigned int  i,j;
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}

void N_S_deal(void)
{
  unsigned long int sum,x1,x2,x3;
	unsigned char s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
				
      x1=(Display_GPGGA_Buffer[17]-0x30)*10+(Display_GPGGA_Buffer[18]-0x30);
      x2=((Display_GPGGA_Buffer[19]-0x30)*10+(Display_GPGGA_Buffer[20]-0x30))/60.0*100000;
	    x3=(((Display_GPGGA_Buffer[22]-0x30)*0.1+(Display_GPGGA_Buffer[23]-0x30)*0.01+(Display_GPGGA_Buffer[24]-0x30)*0.001+(Display_GPGGA_Buffer[25]-0x30)*0.0001+(Display_GPGGA_Buffer[26]-0x30)*0.00001)/60.0)*10000000;
      sum=x1*100000000+x2*1000+x3*10;
      	   
	    s1=sum/1000000000+0x30;
	    s2=sum%1000000000/100000000+0x30; 
	    s3=sum%100000000/10000000+0x30;
	    s4=sum%10000000/1000000+0x30;
	    s5=sum%1000000/100000+0x30;
	    s6=sum%100000/10000+0x30;
	    s7=sum%10000/1000+0x30;
	    s8=sum%1000/100+0x30;
	    s9=sum%100/10+0x30;
	    s10=sum%10;
	    SendData2(s1);			//纬度
			SendData2(s2);			//纬度
			SendData2('.');			//纬度
			SendData2(s3);			//纬度
			SendData2(s4);			//纬度			
			SendData2(s5);			//纬度
			SendData2(s6);			//纬度
			SendData2(s7);			//纬度
			SendData2(s8);			//纬度
			SendData2(s9);			//纬度
			//SendData2(s10);			//纬度			
	    
}
void E_W_deal(void)
{
  unsigned long int sum,x1,x2,x3;
	unsigned char s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;		
      x1=(Display_GPGGA_Buffer[30]-0x30)*100+(Display_GPGGA_Buffer[31]-0x30)*10+(Display_GPGGA_Buffer[32]-0x30);
      x2=((Display_GPGGA_Buffer[33]-0x30)*10+(Display_GPGGA_Buffer[34]-0x30))/60.0*10000000;
	    x3=(((Display_GPGGA_Buffer[36]-0x30)*0.1+(Display_GPGGA_Buffer[37]-0x30)*0.01+(Display_GPGGA_Buffer[38]-0x30)*0.001+(Display_GPGGA_Buffer[39]-0x30)*0.0001+(Display_GPGGA_Buffer[40]-0x30)*0.00001)/60.0)*10000000;
      sum=x1*10000000+x2+x3;   	    
	    s1=sum/1000000000+0x30;
	    s2=sum%1000000000/100000000+0x30; 
	    s3=sum%100000000/10000000+0x30;
	    s4=sum%10000000/1000000+0x30;
	    s5=sum%1000000/100000+0x30;
	    s6=sum%100000/10000+0x30;
	    s7=sum%10000/1000+0x30;
	    s8=sum%1000/100+0x30;
	    s9=sum%100/10+0x30;   
      s10=sum%10+0x30;
	    SendData2(s1);			//经度
			SendData2(s2);	
			SendData2(s3);
	    SendData2('.');	//('.')		
			SendData2(s4);			//经度
			SendData2(s5);
			
			SendData2(s6);	
			SendData2(s7);
			SendData2(s8);	
			SendData2(s9);
			SendData2(s10);

}


