#ifndef HC595_H_
#define HC595_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


#define DATA1_HIGH GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define DATA1_LOW  GPIO_ResetBits(GPIOB, GPIO_Pin_0)

#define DATA2_HIGH GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define DATA2_LOW  GPIO_ResetBits(GPIOA, GPIO_Pin_7)

#define DATA3_HIGH GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define DATA3_LOW  GPIO_ResetBits(GPIOA, GPIO_Pin_6)

#define DATA4_HIGH GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define DATA4_LOW  GPIO_ResetBits(GPIOA, GPIO_Pin_5)

#define DATA5_HIGH GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define DATA5_LOW  GPIO_ResetBits(GPIOA, GPIO_Pin_4)

#define DATA6_HIGH GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define DATA6_LOW  GPIO_ResetBits(GPIOA, GPIO_Pin_1)

#define DATA7_HIGH GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define DATA7_LOW  GPIO_ResetBits(GPIOB, GPIO_Pin_8)

#define DATA8_HIGH GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define DATA8_LOW  GPIO_ResetBits(GPIOB, GPIO_Pin_7)

#define CLK_HIGH  GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define CLK_LOW   GPIO_ResetBits(GPIOB, GPIO_Pin_1)

#define LAT_HIGH  GPIO_SetBits(GPIOB, GPIO_Pin_10)
#define LAT_LOW   GPIO_ResetBits(GPIOB, GPIO_Pin_10)

#define SIZE_ARR  32 
#define SIZE_LED  5

void ShiftByte_1(unsigned char byte);
void ShiftByte_2(unsigned char byte);
void ShiftByte_3(unsigned char byte);
void ShiftByte_4(unsigned char byte);
void ShiftByte_5(unsigned char byte);
void ShiftByte_6(unsigned char byte);
void ShiftByte_7(unsigned char byte);
void ShiftByte_8(unsigned char byte);

void ShiftByte(register unsigned char P1, register  unsigned char P2, register  unsigned char P3, 
	register  unsigned char P4, register  unsigned char P5, register  unsigned char P6, 
	register  unsigned char P7, register  unsigned char P8);
extern char LED7SEG[SIZE_ARR];
void ScanLed(void);
#endif
