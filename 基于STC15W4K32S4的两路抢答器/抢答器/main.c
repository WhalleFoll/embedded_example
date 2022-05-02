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

		
		if(COM1.RX_TimeOut > 0)		//超时计数
		{
			if(--COM1.RX_TimeOut == 0)
			{
				if(COM1.RX_Cnt > 0)
				{
					for(i=0; i<COM1.RX_Cnt; i++)	TX1_write2buff(RX1_Buffer[i]);	//收到的数据原样返回
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
				PrintString1("游戏开始!开始抢答\r\n");
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
			PrintString1("A组抢答成功...\r\n");
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
			PrintString1("B组抢答成功...\r\n");
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
/*************  串口1初始化函数 *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//结构定义
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,       UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//使用波特率,   BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 9600ul;			//波特率, 一般 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
	COMx_InitStructure.UART_Interrupt = ENABLE;				//中断允许,   ENABLE或DISABLE
	COMx_InitStructure.UART_Polity    = PolityLow;			//中断优先级, PolityLow,PolityHigh
	COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;		//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
	USART_Configuration(USART1, &COMx_InitStructure);		//初始化串口1 USART1,USART2

	PrintString1("STC15F2K60S2 UART1 Test Prgramme!\r\n");	//SUART1发送一个字符串
}

void Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//结构定义
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//指定中断优先级, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE或DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//指定时钟源, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (50*12));		//初值,
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer1,&TIM_InitStructure);				//初始化Timer1	  Timer0,Timer1,Timer2
}

/******************** IO配置函数 **************************/
//void	GPIO_config(void)
//{
//	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
//	GPIO_InitStructure.Pin  = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_5;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
//	GPIO_InitStructure.Mode = GPIO_HighZ;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//初始化
//}

/********************* Timer1中断函数************************/
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