#include "key.h"
#include "led.h"
#include "timer2.h"
#include "buzz.h"
#include "timer3.h"
#include "timer4.h"
#include "uart1.h"
#include "uart3.h"
#include "lcd1602.h"
#include  "stdio.h"
//简谱C语言表示方法(M5,50)为(音调，音长) 100表示为一个音长(节拍)，50位半个音长(节拍)，25位四分之一音长  //25 代表一个四音符
// 一节 2节拍  
//4分符为一拍

const u16 music1[]={  //团结就是力量
  H1,100,H1,100, M5,100,M3,50,M2,50, M1,100,M5,100, M3,100,L1,100,
  H1,100,H1,100, M5,100,M3,50,M2,50, M1,100,M6,100, M5,100,L1,50,M3,50, H1,100,L1,50,M3,50, H1,100,M6,50,M5,50,
  M6,100,L1,50,M3,50,H1,100,M6,100,M5,100,M3,100,H1,150,M6,50,H1,100,H1,100,
  //朝着法西斯
  H1,100,M5,100,M3,75,M6,25,M5,50,M3,50,M2,100,M1,100,M3,100,L1,50,M3,50,
  H1,100,M5,100, M6,75,H1,25,M6,50,M5,50,M3,100,M3,50,M1,50,M6,100,M6,100,M6,100,
  H1,75,H1,25,M5,50,M5,50,M2,75,M3,25,M5,50,M5,50,M6,150,M5,50,M6,100,H2,100,H1,100,M6,50,M5,50,
  H1,100.,M6,50,M5,50, M3,100,M3,100,M3,100, M3,100,M3,100,H1,100,H1,100,H1,100,	
};

const u16 music2[]={  //挥着翅膀的女孩
  M6,50,M6,50,M6,50,M7,50,M7,50,M6,50,M5,50,
  M5,100,M3,50,M1,50,M1,50,M2,50,M3,50,
  M4,50,M4,25,M4,25,M4,50,M3,25,M4,25,M4,150,M3,50,
  M4,50,M3,50,M4,50,H2,50,H2,100,H1,50,M7,50,
  H1,150,H1,25,M7,25,M7,50,M5,50,M5,50,M1,50,
  M6,150,M6,50,M5,50,M1,50,M1,50,M3,50,
  M2,150,M3,25,M4,25,M4,25,M4,50,M5,50,H1,50,M7,50,
  H1,150,H2,50,H3,50,H2,50,H1,50,H7,50,
  H1,150,H1,50,M7,50,M5,50,M5,50,M1,50,
  M6,150,M6,50,M5,100,H1,50,M7,50,
  H1,400,
  M4,100,M4,50,M6,50,M5,50,M1,50,M1,100,
  M4,150,M1,50,H2,100,M3,100,
  M1,400,
};
const u16 music3[]={
  M3,100,M3,100,M4,100,M5,100,M5,100,M4,100,M3,100,M2,100,M1,100,M1,100,M2,100,M3,100,M3,150,M2,50,M2,200,
  M3,100,M3,100,M4,100,M5,100,M5,100,M4,100,M3,100,M2,100,M1,100,M1,100,M2,100,M3,100,M2,150,M1,50,M1,200,
  M2,100,M2,100,M3,100,M1,100,M2,100,M3,50,M4,50,M3,100,M1,100,M2,100,M3,50,M4,50,M3,100,M2,100,M1,100,M2,100,L5,100,M3,100,
  M3,100,M3,100,M4,100,M5,100,M5,100,M4,100,M3,100,M4,50,M2,50,M1,100,M1,100,M2,100,M3,100,M2,150,M1,50,M1,200,
  M2,100,M2,100,M3,100,M1,100,M2,100,M3,50,M4,50,M3,100,M1,100,M2,100,M3,50,M4,50,M3,100,M2,100,M1,100,M2,100,L5,100,M3,100,
  M3,100,M3,100,M4,100,M5,100,M5,100,M4,100,M3,100,M4,50,M2,50,M1,100,M1,100,M2,100,M3,100,M2,150,M1,50,M1,200
};

u16 length = sizeof(music3)/sizeof(music3[0]);//计算数组长度
u8 Music_i=0;
u16 Fre,ms,li=0;
u8 second=0, minute=0,hour=0,secondflag=0;              
u8 time[9]={0};
extern u8 RecvData;

void uart1_rev(void);
void times_dispaly(void);

int main(void)
{
   
   Clk_Tran_HSE();
   Key_Init();
   Led_Init();
   TIM2_Init();
   TIM3_Init();
   TIM4_Init();
   Uart1_Init();
   UART3_init();
   Buzz_Init();
   LCD1602_Init();
   asm("rim"); //打开总中断
   
      printf("程序准备就绪......\r\n");
      delay(10);
      TIM3_ARRH = 0;     //频率
      TIM3_ARRL = 0;                  
      TIM3_CNTRH= 0;;    //初始值   50%占空比
      TIM3_CNTRL= 0;    //初始值
      TTS1();
   while(1)
   {
    LCD1602_DIS_CHAR(1,0,'m');
    LCD1602_DIS_CHAR(1,1,'u');
    LCD1602_DIS_CHAR(1,2,'s');
    LCD1602_DIS_CHAR(1,3,'i');
    LCD1602_DIS_CHAR(1,4,'c');
    LCD1602_DIS_CHAR(1,5,'-');
    LCD1602_DIS_CHAR(1,6,'>');
    
    uart1_rev();
     times_dispaly();   
    if(Key_Read()==1)
    {
        TIM3_ARRH = 0;     //频率
        TIM3_ARRL = 0;                  
        TIM3_CNTRH= 0;;    //初始值   50%占空比
        TIM3_CNTRL= 0;    //初始值
        LCD1602_DIS_CHAR(1,7,'0');
        li=0;
    }
    if(Key_Read()==2)
    {
        li=1;
    }
    
     if(Key_Read()==3)
    {
        li=0;
        musics();
        LCD1602_DIS_CHAR(1,7,'6'); 
    }
    
  }
   
}

void times_dispaly(void)
{
      sprintf(time,"%02d:%02d:%02d",hour,minute,second);
     //printf("time = %s\n", time);
    
      for(int i=0;i<8;i++)
      {
         LCD1602_DIS_CHAR(2,i+4,time[i]);
      }

}

void uart1_rev(void)
{
  
       switch(RecvData)
      {
          case 1:{ printf("收到命令0X0%d\r\n",RecvData);
                   LED1=0;delay(400);LED1=1;
                   LCD1602_DIS_CHAR(1,7,'1');
                   
                    TIM3_ARRH = M1>>8;     //频率
                    TIM3_ARRL = M1&0x00ff;                  
                    TIM3_CNTRH= (M1/2)>>8;;    //初始值   50%占空比
                    TIM3_CNTRL= (M1/2)&0x00ff;    //初始值                    
                    RecvData=0;
                   
                  }break;
           case 2:{ printf("收到命令%0X0d\r\n",RecvData);
                    LED2=0;delay(400);LED2=1;
                    LCD1602_DIS_CHAR(1,7,'2');
                    
                    TIM3_ARRH = M2>>8;     //频率
                    TIM3_ARRL = M2&0x00ff;                  
                    TIM3_CNTRH= (M2/2)>>8;;    //初始值   50%占空比
                    TIM3_CNTRL= (M2/2)&0x00ff;    //初始值   
                    RecvData=0;
                    }break;
          case 3:{  printf("收到命令0X0%d\r\n",RecvData);
                    LED3=0;delay(400);LED3=1;
                    LCD1602_DIS_CHAR(1,7,'3');
                    
                    TIM3_ARRH = M3>>8;     //频率
                    TIM3_ARRL = M3&0x00ff;                  
                    TIM3_CNTRH= (M3/2)>>8;;    //初始值   50%占空比
                    TIM3_CNTRL= (M3/2)&0x00ff;    //初始值
                    RecvData=0;
          }break;
          case 4:{  printf("收到命令0X0%d\r\n",RecvData);
                    LED4=0;delay(400);LED4=1;
                    LCD1602_DIS_CHAR(1,7,'4');
                    
                    TIM3_ARRH = M4>>8;      //频率
                    TIM3_ARRL = M4&0x00ff;                  
                    TIM3_CNTRH= (M4/2)>>8;;    //初始值   50%占空比
                    TIM3_CNTRL= (M4/2)&0x00ff;   //初始值
                    RecvData=0;
          }break; 
          case 5:{printf("收到命令0X0%d\r\n",RecvData);
                  LED4=0;delay(400);LED4=1;
                  LCD1602_DIS_CHAR(1,7,'5'); 
                  li=1;
                  RecvData=0;
                  
           }break; 
           case 6:{printf("收到命令0X0%d\r\n",RecvData);
                  LED4=0;delay(400);LED4=1;
                  LCD1602_DIS_CHAR(1,7,'6'); 
                  musics();
                  RecvData=0;
                  
           }break;
          default:break;          
     
    }
    

}


#pragma vector=0x0F
__interrupt void TIM2_UPD_OVF_IRQHandler(void)  //定时器2   //定时1ms
{
  if(li==1)
  {
       if(ms)
         ms--;
       if(!ms)
       {      
          if(Music_i<(length/2))  
          {
              Fre = music3[2*Music_i];
              TIM3_ARRH = Fre>>8;     //频率
              TIM3_ARRL = Fre&0x00ff;  
           
              TIM3_CNTRH= (Fre/2)>>8;;    //初始值   50%占空比
              TIM3_CNTRL= (Fre/2)&0x00ff;    //初始值
                              
              ms =6*music3[2*Music_i+1];//音长的时间都乘以5即一拍为500微秒，此值"5"可调整，只是播放的整个快慢而已，有点类似于视频快进和后退
              // while(ms);
              Music_i++;
          }
          else  
            Music_i=0;
        
   
      }
  }
   TIM2_SR1 = 0;

}



#pragma vector=0x11
__interrupt void TIM3_UPD_OVF_IRQHandler(void)  //定时器3   //频率调节
{
   BUZZ = !BUZZ;
   TIM3_SR1 = 0;
}

#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)  //定时器4   1ms
{
  static u16  num=0;
  num++;
  TIM4_SR = 0;
  if(num == 1000)
   {
      num = 0;
      second++;
      secondflag=1;
       if(second==60)
      {
        second = 0;
        minute++;
        if(minute==60)
          {
          minute=0;
          hour++;
          }
      }
     
   }
}