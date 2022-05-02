#include "config.h"
#include "USART1.h"
#include "delay.h"
#include "lcd1602.h"
#include "IIC.h"
#include "timer.h"
#include "GPIO.h"

sbit k1=P4^0;
sbit k2=P4^2;
sbit k3=P4^5;
sbit k4=P4^7;

sbit A0=P7^0;
sbit A1=P7^1;
sbit A2=P7^2;
sbit BEEP = P7^7;

uchar code DSY_CODE[]=
{
  0x90,0x80,0xf8,0x82,0x92,0x99,0xb0,0xa4,0xf9,0xc0
};
unsigned char dat1=0, dat2=0, dat3 =0;
unsigned char times=0,tim=0,start=0,off=0,kes=0;

void UART_config(void);
void Timer_config(void);
uchar scan_key(void);

void main(void)
{
	u8	i;

	UART_config();
	Timer_config();
	EA = 1;
     
	    LCD_init();	
        s_connectionreset(); 
	
	    dat1 = Read_24C02(0x01);
	    dat2 = Read_24C02(0x03);
		dat3 = Read_24C02(0x05);
	
        LCD_disp_str(0,1," Responder Game");
		LCD_disp_str(0,2,"A->");
	    LCD_disp_str(5,2,"B->");
        LCD_disp_char(3,2,dat1+'0');
	    LCD_disp_char(8,2,dat2+'0');
	
	  
//		Write_24C02(0x01, dat1);
//		delay_ms(100);
//		Write_24C02(0x03, dat2);
//		delay_ms(100);
//		Write_24C02(0x05, dat3);
		
		BEEP = 0;
		
		
	while (1)
	{	
//		dat1++;
//		Write_24C02(0x01, dat1);
//		delay_ms(300);
//        dat1 = Read_24C02(0x01);
//		LCD_disp_char(3,2,dat1+'0');
		scan_key();
		if(dat1>=9) dat1=0;
		if(dat2>=9) dat2=0;
		//delay_ms(600);

		
		if(COM1.RX_TimeOut > 0)		//��ʱ����
		{
			if(--COM1.RX_TimeOut == 0)
			{
				if(COM1.RX_Cnt > 0)
				{
					for(i=0; i<COM1.RX_Cnt; i++)	TX1_write2buff(RX1_Buffer[i]);	//�յ�������ԭ������
				}
				COM1.RX_Cnt = 0;
			}
		}
	}
}

uchar scan_key(void)
{
     if(k1==0)
		{
			delay_ms(100);
			if(k1==0)
			{
				A0=1;A1=1;A2=1;
				start=1;
				PrintString1("��Ϸ��ʼ!��ʼ����\r\n");
			}		
		}
		
	if((k2==0)&&(start==1))
	{
	   delay_ms(10);
	   if(k2==0)
		{
			A0=0;A1=0;A2=0;
			kes=2;
			off=1;
			dat1++;
			Write_24C02(0x01, dat1);
			LCD_disp_char(3,2,dat1+'0');
			PrintString1("A������ɹ�...\r\n");
			BEEP = 1;
			delay_ms(500);
			BEEP = 0;
		}
	}
	if((k3==0)&&(start==1))
	{
	   delay_ms(10);
	   if(k3==0)
		{
			A0=1;A1=0;A2=0;
			off=1;
			dat2++;
			kes=3;
			Write_24C02(0x03, dat2);
			LCD_disp_char(8,2,dat2+'0');
			PrintString1("B������ɹ�...\r\n");
			BEEP = 1;
			delay_ms(500);
			BEEP = 0;
		}
	}
	if(k4==0)
	{
	   delay_ms(10);
	   if(k4==0)
		{
			dat1=dat2=0;
			Write_24C02(0x01, dat1);
			delay_ms(100);
			Write_24C02(0x03, dat2);
			delay_ms(100);
			LCD_disp_char(3,2,dat1+'0');
	        LCD_disp_char(8,2,dat2+'0');
		}
	}
}
/*************  ����1��ʼ������ *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,       UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//ʹ�ò�����,   BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 9600ul;			//������, һ�� 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//�ж�����,   ENABLE��DISABLE
	COMx_InitStructure.UART_Polity    = PolityLow;			//�ж����ȼ�, PolityLow,PolityHigh
	COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(����ʹ���ڲ�ʱ��)
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;		//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE
	USART_Configuration(USART1, &COMx_InitStructure);		//��ʼ������1 USART1,USART2

	PrintString1("STC15F2K60S2 UART1 Test Prgramme!\r\n");	//SUART1����һ���ַ���
}

void Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ָ��ʱ��Դ, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (50*12));		//��ֵ,
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer1,&TIM_InitStructure);				//��ʼ��Timer1	  Timer0,Timer1,Timer2
}

/******************** IO���ú��� **************************/
//void	GPIO_config(void)
//{
//	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
//	GPIO_InitStructure.Pin  = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_5;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
//	GPIO_InitStructure.Mode = GPIO_HighZ;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//��ʼ��
//}

/********************* Timer1�жϺ���************************/
void timer1_int (void) interrupt TIMER1_VECTOR //20ms
{
 if(start==1)
 {
	   times++;
	   if(times>50)
	   {
		 times=0;
		 tim++;
		 P6= DSY_CODE[tim];
		 if((tim==9)||(off==1))
			 {start=0;
			  tim=0;
			  off=0;}
			 
	   }
 }

}