#ifndef _UART3_H_
#define _UART3_H_

#include "sys.h"


void UART3_init(void);
void UART3_sendstring(u8 *p,u16 len);
void UART3_sendbyte(u8 data);
void musics();
void TTS1();//�밴��������LED�����ȣ�
void TTS2();//������ǿ
void TTS3();//���ȼ���

#endif