#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include "ADC.h"
#include "CLOCK.h"
#include "EXTI.h"
#include "GPIO.h"
#include "HC595.h"
#include "SystemTick.h"
#include "USART.h"
#include "TIMER.h"
#include "FLASH.h"
#include "RING_BUFFER.h"
#include "WATCH_DOG.h"
#include "SPI.h"
#include "sx1278.h"

extern unsigned char Arr_Data_Led[];
extern unsigned int Arr_Data[SIZE_ARR_DATA];
extern unsigned char RxBuffer[MAX_INDEX_RXBUFF];
extern unsigned short Index_In_RxBuffer;
volatile uint8_t Rx_Done_Flag;
#define MAX_PORT_LED 8

void Display7SEG(void);
void Check_Flash(void);

volatile unsigned short counter1ms = 0;
unsigned char data_Rx;
unsigned short value_ADC = 0;
#endif
