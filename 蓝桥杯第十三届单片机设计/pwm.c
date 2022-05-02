#include "pwm.h"
/*
void Init_Timer0()
{
        TMOD = 0x01;                    //16位定时模式
        TH0 = (65536 - 100) / 256;      //定时50ms
        TL0 = (65536 - 100) % 256;
        ET0 = 1;                       //使能定时器T0中断
        EA = 1;                       //使能总中断        
        //TR0 = 1;                    //启动定时器T0
}

void SeviceTimer0() interrupt 1
{
        TH0 = (65536 - 100) / 256;
        TL0 = (65536 - 100) % 256;
        n++;
	      if(n<=pwm){ 
           led=0;
				}
				else if(pwm<n) {
				  led=1;
				 
				}
			else if(n>100)
			{
			 n=0;
			}
				
}

*/

/*方法二*/
/*
void Timer0Init(void)		//100微秒@11.0592MHz pwm频率100hz 周期0.01s 10ms 10000us=100us*100
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xAE;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void Timer0()	interrupt 1
{
	tt++;
	if(tt==pwm_num)
	{
	  P00=1;
	}
	else if(tt==100)
	{
		P00=0;
	  tt=0;
	}
}


*/