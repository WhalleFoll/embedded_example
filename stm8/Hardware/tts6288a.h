#ifndef _TTS6288A_H_
#define _TTS6288A_H_

#include "sys.h"

/*
<G> �����ϳ�       <V> ��������0-8        <N>�ʶ�ģʽ0 :����   1:��Ȼ�ʶ�
<M>0�رգ� 1:����1  2:����2       <W>0-8 ��������       ת���ַ� \x16  \x13  
*/
void TTS6288A_Init(void);
void TTS6288A_Send(u8* str);

#endif