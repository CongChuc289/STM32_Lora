#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f10x.h"
void GPIO_init(void);

void Config_GPIO_OUTPUT_PortA(void);
void Config_GPIO_OUTPUT_PortB(void);
void Config_GPIO_OUTPUT_PortC(void);
void Config_GPIO_INPUT_PortB(void);
void Config_GPIO_ADC_PortA(void);

void GPIO_OUTPUT(void);
void GPIO_LOW(void);
void GPIO_HIGH(void);
void GPIO_TOGGLE(void);
void GPIO_H_LED(void);
void GPIO_L_LED(void);

void GPIO_INPUT(void);
unsigned char GPIO_READ(void);


void GPIO_TOGGLE_LED(void);
#endif
