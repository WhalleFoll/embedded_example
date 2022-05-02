#include "adc2.h"

void Adc2_Init(void)
{
  ADC_CSR  = 0x09;  // 通道9 ， 禁止中断
  ADC_CR1  = 0x00;  //2分频，单次转换模式
  ADC_CR2  = 0x08;  //禁止外部触发，数据右对齐
  
  //PE6 无中断悬浮输入    通道9
  PE_DDR_DDR6 = 0;
  PE_CR1_C16  = 0;
  PE_CR2_C26  = 0;
  
  ADC_TDRL = 0x00;  //使能施密特触发器
  ADC_CR1 |= 0x01;  //首次将ADON位置1用于唤醒
}
u16 Adc_Read(void)
{
  u16 Adc_Val;
  
  ADC_CR2 &= 0x08;          //禁止外部触发，数据右对齐
  ADC_CR1  = 0x00;  //2分频，单次转换模式
  ADC_CSR  = 0x09;  // 通道9 ， 禁止中断
  ADC_CR1 |= 0x01;  //首次将ADON位置1用于唤醒
  ADC_CR1 |= 0x01;  //再次将ADON位置1用于启动ADC转换
  
  while(!(ADC_CSR & 0x80));  //等待转换完成
  Adc_Val  = ((u16)ADC_DRH<<8);
  Adc_Val |= (u16)ADC_DRL;
  ADC_CSR &= 0x7F;           //清除标志位
  
  return Adc_Val;
}
