#include "GPIO.h"

/************** STEPS TO FOLLOW *****************
1. Enable GPIOA clock
2. Set the PIN  as output/input
3. Configure the output mode i.e state, speed, and pull
************************************************/
void GPIO_init(void){
	RCC->APB2ENR |= (1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2); // port
}
void GPIO_OUTPUT(void){
	GPIOC->CRH |= (1<<21) | (1<<20); // Output mode, max speed 50 MHz.
  GPIOC->CRH |= (1<<22);	
}
void GPIO_HIGH(void){
	GPIOC->ODR |= (1<<13);
}
void GPIO_LOW(void){
	GPIOC->ODR &= ~(1<<13);
}
void GPIO_TOGGLE(void){
	GPIOC->ODR ^= (1<<13);
}
void GPIO_TOGGLE_LED(void){
	GPIOB->ODR ^= (1<<11);
  GPIOC->ODR ^= (1<<13);
}
void GPIO_H_LED(void){
	GPIOB->ODR |= (1<<11);
}
void GPIO_L_LED(void){
	GPIOB->ODR &= ~(1<<11);
}
void GPIO_INPUT(void){
  GPIOB->CRH |= (1<<3); //Input Pull_up
	GPIOB->CRH &= ~((1<<2)|(1<<1)|(1<<0));		
  GPIOB->ODR |= (1<<8);
}
unsigned char GPIO_READ(void){
	return GPIOB->IDR & (1<<8);
}
void GPIO_OUTPUT_Std(void){
	GPIO_InitTypeDef 					GPIO_InitStructure;	//GPIO struct
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void Config_GPIO_INPUT_PortB(void){
	GPIO_InitTypeDef 					GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_8;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}	
void Config_GPIO_OUTPUT_PortA(void){
	GPIO_InitTypeDef 					GPIO_Port_A;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_Port_A.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Port_A.GPIO_Pin |= GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Port_A.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Port_A);	
}
void Config_GPIO_OUTPUT_PortB(void){
	GPIO_InitTypeDef 					GPIO_Port_B;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_Port_B.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Port_B.GPIO_Pin |= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Port_B.GPIO_Pin |= GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Port_B.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_Port_B);	
}
void Config_GPIO_OUTPUT_PortC(void){
	GPIO_InitTypeDef 					GPIO_Port_C;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_Port_C.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Port_C.GPIO_Pin |= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Port_C.GPIO_Pin |= GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Port_C.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_Port_C);	
}
void Config_GPIO_ADC_PortA(void){
	GPIO_InitTypeDef 					GPIO_ADC_Port_A;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_ADC_Port_A.GPIO_Pin = GPIO_Pin_0;
	GPIO_ADC_Port_A.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_ADC_Port_A.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_ADC_Port_A);
}
