#include "uart_init.h"
#include <ADLX345.h>
#include <GPS.h>
sbit k1=P3^3;	 //����P33����wifi
sbit k2=P3^2;	 //����P31����k2
sbit Le= P3^4;   //����Arduino
void main()
{
    uart1_init();
    uart2_init();
	 
    while(1)
		{  
			//ADXL345_deal();
			Le=1;
			if(k1==0)		  //��ⰴ��K1�Ƿ���
			{
			    //ADXL345_deal(); 					 
                GPS_deal();
				Le=0;
      		    
		}
		}
}