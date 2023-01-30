#include "EXTI.h"
void Config_EXTI_Std(void){
	EXTI_InitTypeDef 					EXTI_InitStructure; // EXTI struct
	NVIC_InitTypeDef 					NVIC_InitStructure; // NVIC struct
	GPIO_InitTypeDef 					GPIO_InitStructure;	//GPIO struct
// 1. RCC Config	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
// 2. GPIO Config
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_8;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
// 3. Config EXTI	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
// 4. Config NVIC	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void Config_EXTI(void){
	RCC->APB2ENR |= (1<<14);
	
	EXTI->IMR &= ~(1<<0); //  Interrupt request from Line 0 is masked

	
}
