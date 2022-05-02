#ifndef _TTS6288A_H_
#define _TTS6288A_H_

#include "sys.h"

/*
<G> 语音合成       <V> 语音声量0-8        <N>朗读模式0 :单字   1:自然朗读
<M>0关闭， 1:音乐1  2:音乐2       <W>0-8 音乐声量       转义字符 \x16  \x13  
*/
void TTS6288A_Init(void);
void TTS6288A_Send(u8* str);

#endif