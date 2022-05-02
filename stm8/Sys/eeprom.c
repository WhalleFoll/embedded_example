#include  "eeprom.h"

u8 disnum_EEPROM @0x4000;//EEPROM起始地址

u8 unlock_EEPROM(void)
{
  //写入MASS密钥，解锁EEPROM
  FLASH_DUKR = 0xAE;
  FLASH_DUKR = 0x56;
  //判断是否解锁成功
  if(FLASH_IAPSR&0x08)
    return 0; //成功
  else
    return 1; //失败
}

void EEPROM_Write(u8* pucBuf, u8 addr, u8 num)
{
    while(num--)
    {
      *(&disnum_EEPROM + addr++) = *pucBuf++;
      while(!(FLASH_IAPSR & 0x40)); //等待写入成功
    }
}

void EEPROM_Read(u8* pucBuf, u8 addr, u8 num)
{
    while(num--)
    {
      *pucBuf++ = *(&disnum_EEPROM + addr++);
    }
}