#include  "eeprom.h"

u8 disnum_EEPROM @0x4000;//EEPROM��ʼ��ַ

u8 unlock_EEPROM(void)
{
  //д��MASS��Կ������EEPROM
  FLASH_DUKR = 0xAE;
  FLASH_DUKR = 0x56;
  //�ж��Ƿ�����ɹ�
  if(FLASH_IAPSR&0x08)
    return 0; //�ɹ�
  else
    return 1; //ʧ��
}

void EEPROM_Write(u8* pucBuf, u8 addr, u8 num)
{
    while(num--)
    {
      *(&disnum_EEPROM + addr++) = *pucBuf++;
      while(!(FLASH_IAPSR & 0x40)); //�ȴ�д��ɹ�
    }
}

void EEPROM_Read(u8* pucBuf, u8 addr, u8 num)
{
    while(num--)
    {
      *pucBuf++ = *(&disnum_EEPROM + addr++);
    }
}