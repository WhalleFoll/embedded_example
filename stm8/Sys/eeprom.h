#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "sys.h"

u8 unlock_EEPROM(void);
void EEPROM_Read(u8* pucBuf, u8 addr, u8 num);
void EEPROM_Write(u8* pucBuf, u8 addr, u8 num);

#endif