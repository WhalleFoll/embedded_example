#ifndef __GSM_H_
#define __GSM_H_

//---包含头文件---//
#include "stc12c5a60s2.h"
#include <absacc.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <intrins.h>
#include "uart_init.h"
//---重定义关键词---//
#define uint unsigned int
#define uchar unsigned char	




//---定义使用的IO口---//


//---定义全局函数---//
void GSM_TEXT();//设置发送数据为TXET格式     入口参数:无     出口参数  ：无
          
void GSM_TEXT_SMS();//发送数据为TXET格式的短信内容     入口参数:无     出口参数：无     
        
void delay(uint ms);

#endif