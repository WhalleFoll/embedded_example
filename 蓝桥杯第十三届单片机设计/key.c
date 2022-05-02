#include "key.h"

sbit S7=P3^0;
sbit S6=P3^1;
sbit S5=P3^2;
sbit S4=P3^3;
//unsigned char key_l=0;
//void keypros()
//{
//	if(S7==0)		  //检测按键K1是否按下
//	{	
//		delay(1000);   //消除抖动 一般大约10ms
//		if(S7==0)	 //再次判断按键是否按下
//		{
//			//L1=~L1;	  //执行此语句
//		}
//		while(!S7);	    //检测按键是否松开 //键盘非零检测while(!s1)=while(!0)进入死循环，此时卡住为键盘光标状态
//		                //秒针暂停（TR=0），当s1为0变为1时，实际为键盘从被按下状态到弹起状态的变化，while(!S7)=while(!1)跳出了死循环。
//	}		
//	
//	if(S6==0)		//  
//	{	
//		delay(1000);  
//		if(S6==0)	 
//		{
//			
//			//P0=0xff;
//			//P0=~(0x80>>i);i++;   //右移 由1000 0000 变成0100 0000
//			//L2=~L2;	
//			
//		}
//		while(!S6);	    	                
//	}		
//	
//}

u16 keypros2(void)
{
	if(S7==0)		  //检测按键K1是否按下
	{			
		while(!S7);	    //检测按键是否松开 //键盘非零检测while(!s1)=while(!0)进入死循环，此时卡住为键盘光标状态
        return 7;		
	}			
	else if(S6==0)		//  
	{	
		while(!S6);
        return 6;		
	}
	else if(S5==0)		//  
	{	
		while(!S5);
        return 5;		
	}	
	else if(S4==0)		//  
	{	
		while(!S4);
        return 4;		
	}		
	else
		return 0;
}
