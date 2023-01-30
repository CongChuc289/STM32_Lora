#ifndef FLASH_H_
#define FLASH_H_

#include "stm32f10x.h"
void Read_FLASH_Std(unsigned int Addr);
void Read_FLASH_Buff_Std(unsigned int Addr, unsigned char *data, unsigned short lenght);
void Write1byte_FLASH_Std(unsigned int Addr, unsigned int data);
void Earse_FLASH_Std(unsigned int Addr);
void Write1byte_FLASH_Buff_Std(unsigned int Addr, unsigned char *data, unsigned short lenght);
void Read_FLASH_Read_Buff_Std(unsigned int Addr, unsigned char *data, unsigned short lenght);
#endif
