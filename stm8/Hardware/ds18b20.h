#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "sys.h"

#define DS18B20_DQ  PI_ODR_ODR4 //单总线引脚
#define DS18B20_IQ  PI_IDR_IDR4

int DS18B20_Get_Temp(void);

#endif