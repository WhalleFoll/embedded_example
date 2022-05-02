#include "keyscan.h"
sfr P4   = 0xC0;   

//ÐÐ
sbit R1 = P3^0;  
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;

//ÁÐ
sbit C1 = P4^4;
sbit C2 = P4^2;
sbit C3 = P3^5;
sbit C4 = P3^4;

unsigned char keyNum = 0;

void delay_ms(unsigned int ms)
{
	 unsigned int i;
	 while(ms--)
		{
			for(i=120;i>0;i--);
		}
}
/*
  0--3
  4--7
  8--11
  12-15
*/
void ScanKeys(void)
{
        keyNum = 20;
       
        R3 = 0;
        R2 = R1 = R4 = 1;
        C1 = C2 = C3 = C4 = 1;
         if(C3 == 0)				//s13
        {
		        delay_ms(400);
                if(C3 == 0)
				{
				  keyNum = 13;
				}
                
               
        }
        else if(C4 == 0)			  // s17
        {
		       delay_ms(400);
                if(C4 == 0)
				{
				  keyNum = 17;
				}
                
                
        }
        
        R4 = 0;
        R2 = R3 = R1 = 1;
        C1 = C2 = C3 = C4 = 1;
        if(C1 == 0)					  // 13
        {
                delay_ms(400);
				while(C1 == 0);
                keyNum = 13;
                
        }
        
        else if(C3 == 0)		   // s 12
        {
	        	delay_ms(400);
                if(C3 == 0)
				{
				 keyNum = 12;
				}
                
               
        }
        else if(C4 == 0)		   // s16
        {		
	         	delay_ms(400);
                if(C4 == 0)
				{
                keyNum = 16;
				}
               
        }
}

