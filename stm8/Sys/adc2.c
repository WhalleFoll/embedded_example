#include "adc2.h"

void Adc2_Init(void)
{
  ADC_CSR  = 0x09;  // ͨ��9 �� ��ֹ�ж�
  ADC_CR1  = 0x00;  //2��Ƶ������ת��ģʽ
  ADC_CR2  = 0x08;  //��ֹ�ⲿ�����������Ҷ���
  
  //PE6 ���ж���������    ͨ��9
  PE_DDR_DDR6 = 0;
  PE_CR1_C16  = 0;
  PE_CR2_C26  = 0;
  
  ADC_TDRL = 0x00;  //ʹ��ʩ���ش�����
  ADC_CR1 |= 0x01;  //�״ν�ADONλ��1���ڻ���
}
u16 Adc_Read(void)
{
  u16 Adc_Val;
  
  ADC_CR2 &= 0x08;          //��ֹ�ⲿ�����������Ҷ���
  ADC_CR1  = 0x00;  //2��Ƶ������ת��ģʽ
  ADC_CSR  = 0x09;  // ͨ��9 �� ��ֹ�ж�
  ADC_CR1 |= 0x01;  //�״ν�ADONλ��1���ڻ���
  ADC_CR1 |= 0x01;  //�ٴν�ADONλ��1��������ADCת��
  
  while(!(ADC_CSR & 0x80));  //�ȴ�ת�����
  Adc_Val  = ((u16)ADC_DRH<<8);
  Adc_Val |= (u16)ADC_DRL;
  ADC_CSR &= 0x7F;           //�����־λ
  
  return Adc_Val;
}
