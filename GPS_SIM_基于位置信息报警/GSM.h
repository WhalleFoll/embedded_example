#ifndef __GSM_H_
#define __GSM_H_

//---����ͷ�ļ�---//
#include "stc12c5a60s2.h"
#include <absacc.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <intrins.h>
#include "uart_init.h"
//---�ض���ؼ���---//
#define uint unsigned int
#define uchar unsigned char	




//---����ʹ�õ�IO��---//


//---����ȫ�ֺ���---//
void GSM_TEXT();//���÷�������ΪTXET��ʽ     ��ڲ���:��     ���ڲ���  ����
          
void GSM_TEXT_SMS();//��������ΪTXET��ʽ�Ķ�������     ��ڲ���:��     ���ڲ�������     
        
void delay(uint ms);

#endif