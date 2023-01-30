#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "stm32f10x.h"
#include "USART.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INDEX_RXBUFF        1024
#define MAX_SIZE_CMD_BUFF       128
#define SIZE_DATA               128
#define SIZE_ARR_DATA           8
void checkRxBuffer(void);
void workCmdBuffer(unsigned char *cmdBuffer);
extern void Display7SEG(void);
extern void Check_Flash(void);

#endif
