#ifndef _UART3_H_
#define _UART3_H_

#include "sys.h"


void UART3_init(void);
void UART3_sendstring(u8 *p,u16 len);
void UART3_sendbyte(u8 data);
void musics();
void TTS1();//请按按键调节LED灯亮度！
void TTS2();//亮度增强
void TTS3();//亮度减弱

#endif