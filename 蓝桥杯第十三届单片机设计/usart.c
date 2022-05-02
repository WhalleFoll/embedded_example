#include "usart.h"
u8 tmpRecv;
void Init_Uart()
{
    TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	
	TCON=0x50;
	TR1=1;
	ES=1;
	EA=1;
}

void PutString(u8 *TXStr)  
{                
   
     //while(*TXStr!=0) 
       while(*TXStr!='\0') 
    {                      
        SBUF=*TXStr;
        while(TI==0);
        TI=0;    
        TXStr++;
    }

} 

void SendByte(unsigned char dat)  //SendByte(0x5a)
{
        SBUF = dat;
        while(TI == 0);
        TI = 0;
}

//---------------接收
void service_Uart() interrupt 4
{
	if(RI==1)
        {
                RI = 0;//清除接收标志
                switch(SBUF)
                {
                        case 'a':  break;											
                        case 'b':  break;                                 
                }

        }
}