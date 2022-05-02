
/*------------------------------------------------------------------*/
/* --- STC MCU Limited ---------------------------------------------*/
/* --- STC12C5Axx Series MCU UART (8-bit/9-bit)Demo ----------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966----------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/
#include "uart_init.h"
#include <ADLX345.h>
#include <GPS.h>
sbit bit9 = P2^2;           //P2.2 show UART data bit9
bit busy;
void uart2_init()
{
  #if (PARITYBIT == NONE_PARITY)
    S2CON = 0x50;           //8-bit variable UART
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    S2CON = 0xda;           //9-bit variable UART, parity bit initial to 1
#elif (PARITYBIT == SPACE_PARITY)
    S2CON = 0xd2;           //9-bit variable UART, parity bit initial to 0
#endif

    BRT = -(FOSC/32/BAUD);  //Set auto-reload vaule of baudrate generator
    AUXR = 0x14;            //Baudrate generator work in 1T mode
    IE2 = 0x01;             //Enable UART2 interrupt
    EA = 1;                 //Open master interrupt switch


}
void uart1_init()
{

    SCON = 0x50;            //8-bit variable UART

    PCON=0X00;
    TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode
    TH1 = TL1 = -(FOSC/12/32/BAUD1); //Set auto-reload vaule
    TR1 = 1;                //Timer1 start run
    ES = 1;                 //Enable UART interrupt
    EA = 1;                 //Open master interrupt switch

}	



/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData1(uchar dat)
{
    while (busy);           //Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    if (P)                  //Set the parity bit according to P
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;            //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;            //Set parity bit to 1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;            //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;            //Set parity bit to 0
#endif
    }
    busy = 1;
    SBUF = ACC;             //Send data to UART buffer
}



/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendString1(char *s)
{
    while (*s)              //Check the end of the string
    {
        SendData1(*s++);     //Send current char and increment string ptr
    }
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData2(uchar dat)
{
    while (busy);           //Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    if (P)                  //Set the parity bit according to P
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON &= ~S2TB8;    //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
        S2CON |= S2TB8;     //Set parity bit to 1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON |= S2TB8;     //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
        S2CON &= ~S2TB8;    //Set parity bit to 0
#endif
    }
    busy = 1;
    S2BUF = ACC;            //Send data to UART2 buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendString2(char *s)
{
    while (*s)              //Check the end of the string
    {
        SendData2(*s++);     //Send current char and increment string ptr
    }
}




/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr() interrupt 4 using 3
{ 
	unsigned char temp = 0;
	if(RI)
	{	
	ES=0;
	temp = SBUF;

	RI = 0;
	
	if(temp == '$')
	{ P2=0X00;
		RX_Count = 0;
		Flag_GPS_OK = 0;		
	}

	RX_Buffer[RX_Count++] = temp;
	
	if(RX_Count >= 70)
	{
		 	
		RX_Count = 70;
	}

	if(temp == '*')
	{
		Flag_GPS_OK = 1;		
	}

	ES=1; 
  P2=0XFF;
  }
	if(TI)
	{
	  TI=0;
		busy=0;
	
	}
		   
		 
}

/*----------------------------
UART2 interrupt service routine
----------------------------*/
void Uart2() interrupt 8 using 1
{
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;     //Clear receive interrupt flag
        P0 = S2BUF;         //P0 show UART data
        P2 = (S2CON & S2RB8);//P2.2 show parity bit
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;     //Clear transmit interrupt flag
        busy = 0;           //Clear transmit busy flag
    }
}


