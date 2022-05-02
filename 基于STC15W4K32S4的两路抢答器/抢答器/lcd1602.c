#include "lcd1602.h"





void LCD_init(void)
{
delay_n10us(10);
LCD_write_command(0x38);//设置8位格式，2行，5x7
delay_n10us(10);
LCD_write_command(0x0c);//整体显示，关光标，不闪烁
delay_n10us(10);
LCD_write_command(0x06);//设定输入方式，增量不移位
delay_n10us(10);
LCD_write_command(0x01);//清除屏幕显示
delay_n10us(100);       //延时清屏，延时函数，延时约n个10us
}


void LCD_write_command(uchar dat)
{
delay_n10us(10);
LCD_RS=0;         //指令
LCD_RW=0;         //写入
LCD_E=1;          //允许
LCD_DB=dat;
delay_n10us(10);  //
LCD_E=0;
delay_n10us(10);  //。
}


void LCD_write_data(uchar dat)
{
delay_n10us(10);
LCD_RS=1;          //数据
LCD_RW=0;          //写入
LCD_E=1;           //允许
LCD_DB=dat;
delay_n10us(10);
LCD_E=0;
delay_n10us(10);
}



void LCD_disp_char(uchar x,uchar y,uchar dat)
{
  uchar address;
  if(y==1)
         address=0x80+x;
  else
         address=0xc0+x;
  LCD_write_command(address);
  LCD_write_data(dat);
}



void LCD_disp_str(uchar x,uchar y,uchar *str)
{
  uchar address;
  if(y==1)
         address=0x80+x;
  else
         address=0xc0+x;
  LCD_write_command(address);
  while(*str!='\0')
  { 
    LCD_write_data(*str);   
    str++;
  }
}



void delay_n10us(uint n)  //延时n个10us@12M晶振
{       
        uint i;           
        for(i=n;i>0;i--)    
        {
        _nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); 
		}
}                                    




typedef union  
{ unsigned int i;      //定义了两个共用体
  float f; 
} value; 

enum {TEMP,HUMI};      //TEMP=0,HUMI=1
 




void s_transstart(void) 

{   
   DATA=1; SCK=0;                   //Initial state 
   _nop_(); 
   SCK=1; 
   _nop_(); 
   DATA=0; 
   _nop_(); 
   SCK=0;   
   _nop_();_nop_();_nop_(); 
   SCK=1; 
   _nop_(); 
   DATA=1;        
   _nop_(); 
   SCK=0;        
} 


void s_connectionreset(void) 

{   
  unsigned char i;  
  DATA=1; SCK=0;                    //Initial state 
  for(i=0;i<9;i++)                  //9 SCK cycles 
  { 
    SCK=1;
    SCK=0; 
  } 
  s_transstart();                   //transmission start 
} 



char s_write_byte(unsigned char value) 
//---------------------------------------------------------------------------------- 
// writes a byte on the Sensibus and checks the acknowledge  
{  
  unsigned char i,error=0;   
  for (i=0x80;i>0;i/=2)             //shift bit for masking 
  {  
    if (i & value) DATA=1;          //masking value with i , write to SENSI-BUS 
    else DATA=0;                         
    SCK=1;                          //clk for SENSI-BUS 
    _nop_();_nop_();_nop_();        //pulswith approx. 3 us     
    SCK=0; 
  } 
  DATA=1;                           //release DATA-line 
  SCK=1;                            //clk #9 for ack  
  error=DATA;                       //check ack (DATA will be pulled down by DHT90),DATA在第9个上升沿将被DHT90自动下拉为低电平。 
  _nop_();_nop_();_nop_();
  SCK=0;
  DATA=1;                           //release DATA-line 
  return error;                     //error=1 in case of no acknowledge //返回：0成功，1失败
} 
 


char s_read_byte(unsigned char ack)  
// reads a byte form the Sensibus and gives an acknowledge in case of "ack=1"  
{  
  unsigned char i,val=0; 
  DATA=1;                           //release DATA-line 
  for (i=0x80;i>0;i/=2)             //shift bit for masking 
  { SCK=1;                          //clk for SENSI-BUS 
    if (DATA) val=(val | i);        //read bit   
	_nop_();_nop_();_nop_();        //pulswith approx. 3 us
    SCK=0;              
  } 
  if(ack==1)DATA=0;                 //in case of "ack==1" pull down DATA-Line 
  else DATA=1;                      //如果是校验(ack==0)，读取完后结束通讯
  _nop_();_nop_();_nop_();          //pulswith approx. 3 us 
  SCK=1;                            //clk #9 for ack 
  _nop_();_nop_();_nop_();          //pulswith approx. 3 us  
  SCK=0;                 
  _nop_();_nop_();_nop_();          //pulswith approx. 3 us 
  DATA=1;                           //release DATA-line 
  return val; 
} 
 

 


char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode) 
// makes a measurement (humidity/temperature) with checksum 
{  
  unsigned error=0; 
  unsigned int i; 
 
  s_transstart();                   //transmission start 
  switch(mode){                     //send command to sensor 
    case TEMP  : error+=s_write_byte(MEASURE_TEMP); break; 
    case HUMI  : error+=s_write_byte(MEASURE_HUMI); break; 
    default     : break;    
  } 
  for (i=0;i<65535;i++) if(DATA==0) break; //wait until sensor has finished the measurement 
  if(DATA) error+=1;                // or timeout (~2 sec.) is reached 
  *(p_value)  =s_read_byte(ACK);    //read the first byte (MSB) 
  *(p_value+1)=s_read_byte(ACK);    //read the second byte (LSB) 
  *p_checksum =s_read_byte(noACK);  //read checksum 
  return error; 
} 
 


void calc_dht90(float *p_humidity ,float *p_temperature)
// calculates temperature [C] and humidity [%RH] 
// input :  humi [Ticks] (12 bit) 
//          temp [Ticks] (14 bit)
// output:  humi [%RH]
//          temp [C]
{ const float C1=-4.0;              // for 12 Bit
  const float C2=+0.0405;           // for 12 Bit
  const float C3=-0.0000028;        // for 12 Bit
  const float T1=+0.01;             // for 14 Bit @ 5V
  const float T2=+0.00008;           // for 14 Bit @ 5V 

  float rh=*p_humidity;             // rh:      Humidity [Ticks] 12 Bit 
  float t=*p_temperature;           // t:       Temperature [Ticks] 14 Bit
  float rh_lin;                     // rh_lin:  Humidity linear
  float rh_true;                    // rh_true: Temperature compensated humidity
  float t_C;                        // t_C   :  Temperature [C]

  t_C=t*0.01 - 40;                  //calc. temperature from ticks to [C]
  rh_lin=C3*rh*rh + C2*rh + C1;     //calc. humidity from ticks to [%RH]
  rh_true=(t_C-25)*(T1+T2*rh)+rh_lin-3;   //calc. temperature compensated humidity [%RH]
  if(rh_true>100)rh_true=100;       //cut if the value is outside of
  if(rh_true<0.1)rh_true=0.1;       //the physical possible range

  *p_temperature=t_C;               //return temperature [C]
  *p_humidity=rh_true;              //return humidity[%RH]
}


//value humi_val,temp_val;
//	    unsigned char error,checksum; 
//        unsigned int wendu,shidu;
//void dht(void)
//{
//        
//	      error=0; 
//          error+=s_measure((unsigned char*) &humi_val.i,&checksum,HUMI);  //measure humidity 
//          error+=s_measure((unsigned char*) &temp_val.i,&checksum,TEMP);  //measure temperature 
//          if(error!=0) s_connectionreset();                 //in case of an error: connection reset 
//          else 
//          { humi_val.f=(float)humi_val.i;                   //converts integer to float
//            temp_val.f=(float)temp_val.i;                   //converts integer to float
//            calc_dht90(&humi_val.f,&temp_val.f);            //calculate humidity, temperature
//			wendu=10*temp_val.f;
//			//LCD_disp_char(2,1,wendu/1000+'0');              //显示温度百位
//            LCD_disp_char(3,1,(wendu%1000)/100+'0');        //显示温度十位
//            LCD_disp_char(4,1,(wendu%100)/10+'0');          //显示温度个位
//			LCD_disp_char(6,1,(wendu%10)+'0');              //显示温度小数点后第一位

//			shidu=10*humi_val.f;
//			//LCD_disp_char(2,2,shidu/1000+'0');               //显示湿度百位
//            LCD_disp_char(3,2,(shidu%1000)/100+'0');         //显示湿度十位
//            LCD_disp_char(4,2,(shidu%100)/10+'0');           //显示湿度个位
//			LCD_disp_char(6,2,(shidu%10)+'0');               //显示湿度小数点后第一位
//          } 
//          //----------wait approx. 0.8s to avoid heating up SHTxx------------------------------       
//		  delay_n10us(80000);                                //延时约0.8s
//}