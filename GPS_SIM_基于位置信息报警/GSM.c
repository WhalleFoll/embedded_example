#include <GSM.h>

uchar code SMS_send[]= "AT+CSCS=";
uchar code SMS_send1[]= "UCS2";//设置为 16 位通用 8 字节倍数编码字符集
uchar code SMS_send2[]= "AT+CSMP=17,167,0,8";//使用 UCS2 方式发送中文短信
uchar code SMS_send3[]= "AT+CMGS=";
uchar code PhoneCall[]="17104945750";	//用户手机号
//uchar code PhoneCall[]="13781811373";	//用户手机号
uchar code SMS_TXET[]= "AT+CMGF=1";//发送数据为TXET格式 

uchar code Sms[]="危险"; 

void delay(uint ms)// 延时子程序
{      
uchar i;
while(ms--)
{
  for(i=0;i<120;i++);
}
}

/*********************************************************** 
函数名称：GSM_TEXT 
函数功能：设置发送数据为TXET格式       
          入口参数:无     出口参数：无 
***********************************************************/ 
 
void GSM_TEXT()   //设置GSM为TEXT格式
{    
	   SendString2(SMS_send);
	   SendString2(SMS_send1);
     SendString2("\r\n");   //发送回车
     delay(6000);
     SendString2(SMS_send2);	 
     SendString2("\r\n");   //发送回车
     delay(6000);	
     SendString2(SMS_TXET);   //发送设置指令
     SendString2("\r\n");   //发送回车
     ES=0;
     delay(6000); 
	    SendString2(SMS_send3);
	    SendString2(PhoneCall);
      SendString2("\r\n");   //发送回车
      delay(6000);
}

/*********************************************************** 
函数名称：GSM_TEXT_SMS 
函数功能：发送数据为TXET格式的短信内容       
          入口参数:无     出口参数：无 
***********************************************************/ 
 
void GSM_TEXT_SMS()  //发送TEXT格式内容
{   
     
     SendString2(SMS_send3);
	   SendString2(PhoneCall);
     SendString2("\r\n");   //发送回车
     delay(3000); 
     SendString2(Sms);
     SendData2(0x1a);  //发送短息内容结束符对应的ASCII为0x1a
     ES=1;
     delay(1000);
     delay(5000);   
} 
