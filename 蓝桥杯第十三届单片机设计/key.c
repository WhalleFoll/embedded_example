#include "key.h"

sbit S7=P3^0;
sbit S6=P3^1;
sbit S5=P3^2;
sbit S4=P3^3;
//unsigned char key_l=0;
//void keypros()
//{
//	if(S7==0)		  //��ⰴ��K1�Ƿ���
//	{	
//		delay(1000);   //�������� һ���Լ10ms
//		if(S7==0)	 //�ٴ��жϰ����Ƿ���
//		{
//			//L1=~L1;	  //ִ�д����
//		}
//		while(!S7);	    //��ⰴ���Ƿ��ɿ� //���̷�����while(!s1)=while(!0)������ѭ������ʱ��סΪ���̹��״̬
//		                //������ͣ��TR=0������s1Ϊ0��Ϊ1ʱ��ʵ��Ϊ���̴ӱ�����״̬������״̬�ı仯��while(!S7)=while(!1)��������ѭ����
//	}		
//	
//	if(S6==0)		//  
//	{	
//		delay(1000);  
//		if(S6==0)	 
//		{
//			
//			//P0=0xff;
//			//P0=~(0x80>>i);i++;   //���� ��1000 0000 ���0100 0000
//			//L2=~L2;	
//			
//		}
//		while(!S6);	    	                
//	}		
//	
//}

u16 keypros2(void)
{
	if(S7==0)		  //��ⰴ��K1�Ƿ���
	{			
		while(!S7);	    //��ⰴ���Ƿ��ɿ� //���̷�����while(!s1)=while(!0)������ѭ������ʱ��סΪ���̹��״̬
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
