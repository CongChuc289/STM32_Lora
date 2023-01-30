#include "FLASH.h"
void Earse_FLASH_Std(unsigned int Addr){
	if(FLASH->CR&FLASH_CR_LOCK){
		FLASH->KEYR = ((uint32_t)0x45670123);
		FLASH->KEYR = ((uint32_t)0xCDEF89AB);
	}
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = Addr;
	FLASH->CR |= FLASH_CR_STRT;
	while(FLASH->SR & FLASH_SR_BSY);
	FLASH->CR &= ~FLASH_CR_PER;
	FLASH->CR &= ~FLASH_CR_STRT;
}	
void Read_FLASH_Buff_Std(unsigned int Addr, unsigned char *data, unsigned short lenght){
	for(unsigned short i = 0; i < lenght; i+= 2){
		unsigned short data_buff = *(volatile unsigned int *)(Addr + i);
		data[i] = data_buff;
		data[i+1] = data_buff>>8;
		/*
		*(data + i) = data_buff;
		*(data + i + 1) = data_temp>>8;
		*/
	}
}	
void Write1byte_FLASH_Std(unsigned int Addr, unsigned int data){
	if(FLASH->CR & FLASH_CR_LOCK){
		FLASH->KEYR = ((uint32_t)0x45670123);
		FLASH->KEYR = ((uint32_t)0xCDEF89AB);
	}
	FLASH->CR |= FLASH_CR_PG;
	*(uint16_t*)Addr = data;
	while(FLASH->SR&FLASH_SR_BSY);
	FLASH->CR &= ~FLASH_CR_PG;
}
void Write1byte_FLASH_Buff_Std(unsigned int Addr, unsigned char *data, unsigned short lenght){
	for(unsigned short i = 0; i < lenght; i+= 2){
		Write1byte_FLASH_Std(Addr + i , data[i]|((unsigned short)data[i+1]<<8));
	}
}

