#include "pwm.h"
/*
void Init_Timer0()
{
        TMOD = 0x01;                    //16λ��ʱģʽ
        TH0 = (65536 - 100) / 256;      //��ʱ50ms
        TL0 = (65536 - 100) % 256;
        ET0 = 1;                       //ʹ�ܶ�ʱ��T0�ж�
        EA = 1;                       //ʹ�����ж�        
        //TR0 = 1;                    //������ʱ��T0
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

/*������*/
/*
void Timer0Init(void)		//100΢��@11.0592MHz pwmƵ��100hz ����0.01s 10ms 10000us=100us*100
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xAE;		//���ö�ʱ��ֵ
	TH0 = 0xFB;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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