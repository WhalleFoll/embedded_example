#include "timer1.h"

void TIM1_Init(void)
{
  TIM1_PSCRH = 0;// Set the Prescaler value
  TIM1_PSCRL = 19;// Set the Prescaler value
  TIM1_ARRH = 0;// 初始化自动装载寄存器，决定PWM 方波的频率 
  TIM1_ARRL = 99;// 初始化自动装载寄存器，决定PWM 方波的频率 
  TIM1_CR1&=0x8F;         //向上计数模式边沿对齐
  
  TIM1_CCMR1=0x60;//配置为PWM模式1
//  TIM1_CCER1&=0xFD;//配置CC1P=0，OC1信号高电平有效
  TIM1_CCER1|=0x02;//配置CC1P=1，OC1信号低电平有效
  TIM1_CCER1|=0x01;//配置CC1E=1，使能OC1输出
  TIM1_OISR|=0x01;//空闲状态时OC1为高电平

  TIM1_CCR1H=0;  //捕获比较值
  TIM1_CCR1L=0;

  TIM1_CR1|=0x01;//使能TIM1计数器功能“CEN=1”
  TIM1_BKR=0x80;//打开“主输出”开关输出PWM信号“MOE=1”
}
/****************************************************************/
//TIM1_CH1通道PWM信号输出配置函数CH1_PWM_SET()，有形参F_SET_CH1、
//Duty_CH1，F_SET_CH1用于配置捕获/比较寄存器1高低位，Duty_CH1用于
//配置PWM信号占空比，无返回值
/****************************************************************/
void CH1_PWM_SET(unsigned long F_SET_CH1,float Duty_CH1)
{
  float a;//变量用于占空比计算
  a=Duty_CH1*F_SET_CH1;//计算占空比参数
  TIM1_CCR1H=((u16)(a))/256;//配置捕获/比较寄存器1高位“CCR1H”
  TIM1_CCR1L=((u16)(a))%256;//配置捕获/比较寄存器1低位“CCR1L”
  
}
///****************************************************************/
////TIM1_CH2通道PWM信号输出配置函数CH2_PWM_SET()，有形参F_SET_CH2、
////Duty_CH2，F_SET_CH2用于配置捕获/比较寄存器2高低位，Duty_CH2用于
////配置PWM信号占空比，无返回值
///****************************************************************/
//void CH2_PWM_SET(unsigned long F_SET_CH2,float Duty_CH2)
//{
//  float b;//变量用于占空比计算
//  b=Duty_CH2*F_SET_CH2;//计算占空比参数
//  TIM1_CCR2H=((u16)(b))/256;//配置捕获/比较寄存器2高位“CCR2H”
//  TIM1_CCR2L=((u16)(b))%256;//配置捕获/比较寄存器2低位“CCR2L”
//  TIM1_CCMR2=0x60;//配置为PWM模式1
//  TIM1_CCER1&=0xDF;//配置CC2P=0，OC2信号高电平有效
//  TIM1_CCER1|=0x10;//配置CC2E=1，使能OC2输出
//  TIM1_OISR|=0x04;//空闲状态时OC2为高电平
//}
///****************************************************************/
////TIM1_CH3通道PWM信号输出配置函数CH3_PWM_SET()，有形参F_SET_CH3、
////Duty_CH3，F_SET_CH3用于配置捕获/比较寄存器3高低位，Duty_CH3用于
////配置PWM信号占空比，无返回值
///****************************************************************/
//void CH3_PWM_SET(unsigned long F_SET_CH3,float Duty_CH3)
//{
//  float c;//变量用于占空比计算
//  c=Duty_CH3*F_SET_CH3;//计算占空比参数
//  TIM1_CCR3H=((u16)(c))/256;//配置捕获/比较寄存器3高位“CCR3H”
//  TIM1_CCR3L=((u16)(c))%256;//配置捕获/比较寄存器3低位“CCR3L”
//  TIM1_CCMR3=0x60;//配置为PWM模式1
//  TIM1_CCER2&=0x3D;//配置CC3P=0，OC3信号高电平有效
//  TIM1_CCER2|=0x01;//配置CC3E=1，使能OC3输出
//  TIM1_OISR|=0x10;//空闲状态时OC3为高电平
//}
///****************************************************************/
////TIM1_CH4通道PWM信号输出配置函数CH4_PWM_SET()，有形参F_SET_CH4、
////Duty_CH4，F_SET_CH4用于配置捕获/比较寄存器4高低位，Duty_CH4用于
////配置PWM信号占空比，无返回值
///****************************************************************/
//void CH4_PWM_SET(unsigned long F_SET_CH4,float Duty_CH4)
//{
//  float d;//变量用于占空比计算
//  d=Duty_CH4*F_SET_CH4;//计算占空比参数
//  TIM1_CCR4H=((u16)(d))/256;//配置捕获/比较寄存器4高位“CCR4H”
//  TIM1_CCR4L=((u16)(d))%256;//配置捕获/比较寄存器4低位“CCR4L”
//  TIM1_CCMR4=0x60;//配置为PWM模式1
//  TIM1_CCER2&=0x1F;//配置CC4P=0，OC4信号高电平有效
//  TIM1_CCER2|=0x10;//配置CC4E=1，使能OC4输出
//  TIM1_OISR|=0x40;//空闲状态时OC4为高电平
//}


