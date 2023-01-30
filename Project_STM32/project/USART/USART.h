#ifndef USART_H_
#define USART_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define BUFFER_SIZE 100


void Config_USART1(void);
void Config_USART1_Std(void);
void Config_USART1_IT_Std(void);
void Config_USART1_IT(void);

void Config_USART2_Std(void);
void Config_USART2_IT_Std(void);
void Config_USART3_Std(void);

void USART1_Send_data_Std(unsigned char *data, unsigned int lenght);
void USART1_Send_data(unsigned char *data, unsigned int lenght);

void USART2_Send_data_Std(unsigned char *data, unsigned int lenght);
void USART2_Send_data(unsigned char *data, unsigned int lenght);

unsigned char USART1_Get_data(void);

void Send_RS485(unsigned char *data, unsigned int length);
void Config_USART1_DMA_Std(void);
#endif
