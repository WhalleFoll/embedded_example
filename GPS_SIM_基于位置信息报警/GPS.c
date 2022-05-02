
#include "GPS.h"

//�������
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

unsigned char code SMS_send_front[]="�豸����������λ��";
void N_S_deal(void);
void E_W_deal(void);
//****************************************************
//������
//****************************************************
void GPS_deal()
{
	unsigned char i = 0;
  //ES=0;
//	   GSM_TEXT();
//     SendString2(SMS_send_3);
//	   SendString2(PhoneCall_11);
//     SendString2("\r\n");   //���ͻس�
//     Delay_ms(3000);  
//	   SendString2(SMS_send_front);
//	SendString2("\r\n");
     //SendData2('1');
		if(Flag_GPS_OK == 1 && RX_Buffer[4] == 'G' && RX_Buffer[6] == ',' && RX_Buffer[13] == '.')			//ȷ���Ƿ��յ�"GPGGA"��һ֡����
		{
			for( i = 0; i < 68 ; i++)
			{
				Display_GPGGA_Buffer[i] = RX_Buffer[i];	
			}
			Hour = (Display_GPGGA_Buffer[7]-0x30)*10+(Display_GPGGA_Buffer[8]-0x30)+8;			//UTCʱ��ת��������ʱ��		UTC+8
																								//0x30ΪASCIIת��Ϊ����
			if( Hour >= 24)				//���
			{
				Hour %= 24;				//��ȡ��ǰHour
				Flag_OV = 1;			//���ڽ�λ
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
			if(Display_GPGGA_Buffer[28]=='N')//N ���� S
			{	
				SendString2("��γ:");
         				
      }
			else SendString2("��γ:");        			
			N_S_deal();
			SendString2("\r\n");	
//Delay_ms(3000);			
      if(Display_GPGGA_Buffer[42]=='E')	//E ���� W
			{	
				SendString2("����:");		
      }
			else SendString2("����:");	
		  E_W_deal();
			SendString2("\r\n");
			//Delay_ms(1000);
      SendData2(0x1a);  //���Ͷ�Ϣ���ݽ�������Ӧ��ASCIIΪ0x1a
			SendString2("\r\n");
      ES=1;  
			
		}			
			Min_Low1=Min_Low;
			if(Min_Low==9)
				Min_Low1=0;
		}
		
		if(Flag_GPS_OK == 1 && RX_Buffer[4] == 'M' && RX_Buffer[52] == ',' && RX_Buffer[59] == ',')			//ȷ���Ƿ��յ�"GPRMC"��һ֡����
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


			if(Flag_OV == 1)			//�н�λ
			{
				UTCDate2LocalDate();			//UTC����ת��Ϊ����ʱ��		
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
		 //SendData2(0x1a);  //���Ͷ�Ϣ���ݽ�������Ӧ��ASCIIΪ0x1a
//     ES=1;
//      Delay_ms(1000);
//     Delay_ms(5000);   
}
//****************************************************
//UTC�����뵱������ת��
//****************************************************
void UTCDate2LocalDate(void)
{
	Day = (Day_High - 0x30) * 10 + (Day_Low-0x30) + 1;		//��  ��һ
	Month = (Month_High - 0x30) * 10 + (Month_Low - 0x30);
	Year = 2000 + (Year_High - 0x30) * 10 + (Year_Low - 0x30);
	
	MaxDay = GetMaxDay(Month,Year);				//��ȡ���� ���� ���ֵ
	if(Day > MaxDay)		//���
	{
		Day = 1;
		Month += 1;
		if(Month > 12)
		{
			Year+=1;
		}
	}

	Day_High = Day/10 + 0x30;				//ת������ֵΪASCII
	Day_Low = Day%10 + 0x30;

	Month_High = Month/10 + 0x30;			//ת���·�ֵΪASCII
	Month_Low = Month%10 + 0x30;

	Year_High = Year%100/10 + 0x30;			//ת�����ֵΪASCII
	Year_Low = Year%10 + 0x30;			
}

//****************************************************
//��ȡ�����������ֵ
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
				//2�·ݱȽ����⣬��Ҫ�����ǲ����������жϵ�����28�컹29��
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
//������
//****************************************************
bit IsLeapYear(unsigned int uiYear)
{
	return (((uiYear%4)==0)&&((uiYear%100)!=0))||((uiYear%400)==0);
}


//****************************************************
//MS��ʱ����(12M�����²���)
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
	    SendData2(s1);			//γ��
			SendData2(s2);			//γ��
			SendData2('.');			//γ��
			SendData2(s3);			//γ��
			SendData2(s4);			//γ��			
			SendData2(s5);			//γ��
			SendData2(s6);			//γ��
			SendData2(s7);			//γ��
			SendData2(s8);			//γ��
			SendData2(s9);			//γ��
			//SendData2(s10);			//γ��			
	    
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
	    SendData2(s1);			//����
			SendData2(s2);	
			SendData2(s3);
	    SendData2('.');	//('.')		
			SendData2(s4);			//����
			SendData2(s5);
			
			SendData2(s6);	
			SendData2(s7);
			SendData2(s8);	
			SendData2(s9);
			SendData2(s10);

}


