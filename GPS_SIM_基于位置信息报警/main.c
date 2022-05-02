#include "uart_init.h"
#include <ADLX345.h>
#include <GPS.h>
sbit k1=P3^3;	 //定义P33口是wifi
sbit k2=P3^2;	 //定义P31口是k2
sbit Le= P3^4;   //返回Arduino
void main()
{
    uart1_init();
    uart2_init();
	 
    while(1)
		{  
			//ADXL345_deal();
			Le=1;
			if(k1==0)		  //检测按键K1是否按下
			{
			    //ADXL345_deal(); 					 
                GPS_deal();
				Le=0;
      		    
		}
		}
}