#include <GSM.h>

uchar code SMS_send[]= "AT+CSCS=";
uchar code SMS_send1[]= "UCS2";//����Ϊ 16 λͨ�� 8 �ֽڱ��������ַ���
uchar code SMS_send2[]= "AT+CSMP=17,167,0,8";//ʹ�� UCS2 ��ʽ�������Ķ���
uchar code SMS_send3[]= "AT+CMGS=";
uchar code PhoneCall[]="17104945750";	//�û��ֻ���
//uchar code PhoneCall[]="13781811373";	//�û��ֻ���
uchar code SMS_TXET[]= "AT+CMGF=1";//��������ΪTXET��ʽ 

uchar code Sms[]="Σ��"; 

void delay(uint ms)// ��ʱ�ӳ���
{      
uchar i;
while(ms--)
{
  for(i=0;i<120;i++);
}
}

/*********************************************************** 
�������ƣ�GSM_TEXT 
�������ܣ����÷�������ΪTXET��ʽ       
          ��ڲ���:��     ���ڲ������� 
***********************************************************/ 
 
void GSM_TEXT()   //����GSMΪTEXT��ʽ
{    
	   SendString2(SMS_send);
	   SendString2(SMS_send1);
     SendString2("\r\n");   //���ͻس�
     delay(6000);
     SendString2(SMS_send2);	 
     SendString2("\r\n");   //���ͻس�
     delay(6000);	
     SendString2(SMS_TXET);   //��������ָ��
     SendString2("\r\n");   //���ͻس�
     ES=0;
     delay(6000); 
	    SendString2(SMS_send3);
	    SendString2(PhoneCall);
      SendString2("\r\n");   //���ͻس�
      delay(6000);
}

/*********************************************************** 
�������ƣ�GSM_TEXT_SMS 
�������ܣ���������ΪTXET��ʽ�Ķ�������       
          ��ڲ���:��     ���ڲ������� 
***********************************************************/ 
 
void GSM_TEXT_SMS()  //����TEXT��ʽ����
{   
     
     SendString2(SMS_send3);
	   SendString2(PhoneCall);
     SendString2("\r\n");   //���ͻس�
     delay(3000); 
     SendString2(Sms);
     SendData2(0x1a);  //���Ͷ�Ϣ���ݽ�������Ӧ��ASCIIΪ0x1a
     ES=1;
     delay(1000);
     delay(5000);   
} 
