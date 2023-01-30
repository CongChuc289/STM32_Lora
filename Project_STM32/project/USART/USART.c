#include "USART.h"
#include "SystemTick.h"

void Config_USART1(void){
// 1. Enable RCC
	RCC->APB2ENR |= (1<<14); //Enable USART CLOCK
	RCC->APB2ENR |= (1<<2); // Enable CLOCK PORTA	
	RCC->APB2ENR |= (1<<0); // Enable CLOCK Alternate Function I/O 
// 2. Config Tx	
	GPIOA->CRH |= (1<<7);
	GPIOA->CRH &= ~(1<<6);
	GPIOA->CRH |= (1<<5)|(1<<4);
// 3. Config Rx
  GPIOA->CRH &= ~((1<<8)|(1<<9));
  GPIOA->CRH |=  (1<<11);
  GPIOA->CRH &= ~(1<<10);
  GPIOA->ODR |=  (1<<10);
//	Config UART
	USART1->CR1 |= (1<<13); // Enable USART
	USART1->CR1 &= ~(1<<12); // word lenght_8b
	
	USART1->CR2 &= ~((1<<13)|(1<<12)); // Stop_bit 1
	
	//USART1->BRR (f =72M)
	USART1->BRR |= 0x1D4C; //(468 = 1D4 , 12 = C)
	//USART1->BRR = (468<<4)|(12<<0); // baurd 9600 (Mass 468 ,Frac (0,75*16)  = 12)
	//115200 => Div = 39.0625
	//USART1->BRR = (39<<4)|(1<<0);
	
	USART1->CR1 |= (1<<3) | (1<<2); // Tx | Rx
	
}
void Config_USART1_Std(void){
	USART_InitTypeDef         USART_InitStructure;
	GPIO_InitTypeDef 					GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
//Tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
//Rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	USART_Cmd(USART1, ENABLE);
		
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART1, &USART_InitStructure);
}
void Config_USART1_IT(void){
// 1. Enable RCC
	RCC->APB2ENR |= (1<<14); //Enable USART CLOCK
	RCC->APB2ENR |= (1<<2); // Enable CLOCK PORTA	
	RCC->APB2ENR |= (1<<0); // Enable CLOCK Alternate Function I/O 
// 2. Config Tx	
	GPIOA->CRH |= (1<<7);
	GPIOA->CRH &= ~(1<<6);
	GPIOA->CRH |= (1<<5)|(1<<4);
// 3. Config Rx
  GPIOA->CRH &= ~((1<<8)|(1<<9));
  GPIOA->CRH |=  (1<<11);
  GPIOA->CRH &= ~(1<<10);
  GPIOA->ODR |=  (1<<10);
//	Config UART
	USART1->CR1 |= (1<<13); // Enable USART
	USART1->CR1 &= ~(1<<12); // word lenght_8b
	
	USART1->CR2 &= ~((1<<13)|(1<<12)); // Stop_bit 1
	
	//USART1->BRR (f =72M)
	USART1->BRR |= 0x1D4C; //(486 = 1D4 , 12 = C)
	//USART1->BRR = (468<<4)|(12<<0); // baurd 9600 (Mass 468 ,Frac (0,75*16)  = 12)
	//115200 => Div = 39.0625
	//USART1->BRR = (39<<4)|(1<<0);
	
	USART1->CR1 |= (1<<3) | (1<<2); // Tx | Rx
	USART1->CR1 |= (1<<5);
	
	NVIC_EnableIRQ(USART1_IRQn);
}
void Config_USART1_IT_Std(void){
	USART_DeInit(USART1);
	
	USART_InitTypeDef         USART_InitStructure;
	GPIO_InitTypeDef 					GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
//Tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
//Rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
		
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART1, &USART_InitStructure);
	USART_ClearFlag(USART1, USART_IT_RXNE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
	
	/* Enable USART1 global interrupt */
	NVIC_EnableIRQ(USART1_IRQn);
}
void Config_USART2_Std(void){
	USART_DeInit(USART2);
	
	USART_InitTypeDef         USART_2;
  GPIO_InitTypeDef 					GPIO_USART2;	
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
//Tx
	GPIO_USART2.GPIO_Pin = GPIO_Pin_2;
	GPIO_USART2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_USART2.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_USART2);
//Rx
	GPIO_USART2.GPIO_Pin = GPIO_Pin_3;
	GPIO_USART2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_USART2.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_USART2);	
  
	USART_2.USART_BaudRate = 9600;
	USART_2.USART_WordLength = USART_WordLength_8b;
	USART_2.USART_StopBits = USART_StopBits_1;
	USART_2.USART_Parity = USART_Parity_No;
	USART_2.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART2, &USART_2);	
	USART_Cmd(USART2, ENABLE);
}
void Config_USART2_IT_Std(void){
	USART_DeInit(USART2);
	
	USART_InitTypeDef         USART_2;
  GPIO_InitTypeDef 					GPIO_USART2;	
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
//Tx
	GPIO_USART2.GPIO_Pin = GPIO_Pin_2;
	GPIO_USART2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_USART2.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_USART2);
//Rx
	GPIO_USART2.GPIO_Pin = GPIO_Pin_3;
	GPIO_USART2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_USART2.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_USART2);	
  
	USART_2.USART_BaudRate = 9600;
	USART_2.USART_WordLength = USART_WordLength_8b;
	USART_2.USART_StopBits = USART_StopBits_1;
	USART_2.USART_Parity = USART_Parity_No;
	USART_2.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART2, &USART_2);	
	USART_ClearFlag(USART2, USART_IT_RXNE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
	/* Enable USART1 global interrupt */
	NVIC_EnableIRQ(USART2_IRQn);
}
void Config_USART3_Std(void){
	USART_DeInit(USART3);
	
	USART_InitTypeDef         USART_InitStructure;
	GPIO_InitTypeDef 					GPIO_InitStructure;	
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
	USART_Cmd(USART3, ENABLE);
  
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART3, &USART_InitStructure);	
}
void USART1_Send_data_Std(unsigned char *data, unsigned int lenght){
	for(unsigned int i = 0; i < lenght; i ++){
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1, data[i]);
	}
}
void USART2_Send_data_Std(unsigned char *data, unsigned int lenght){
	for(unsigned int i = 0; i < lenght; i ++){
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
		USART_SendData(USART2, data[i]);
	}
}
void USART1_Send_data(unsigned char *data, unsigned int lenght){
	for(unsigned int  i = 0; i < lenght; i++){
	  while (!(USART1->SR & (1<<6))); // Transmission complete
		USART1->DR = data[i];   
	}
}
void USART2_Send_data(unsigned char *data, unsigned int lenght){
	for(unsigned int  i = 0; i < lenght; i++){
	  while (!(USART2->SR & (1<<6))); // Transmission complete
		USART2->DR = data[i];   
	}
}
unsigned char USART1_Get_data(void){
	unsigned char data;
	while (!(USART1->SR & (1<<5)));  // Wait for RXNE to SET.. This indicates that the data has been Received
	data = USART1->DR;  // Read the data. 
	return data;
}
void Send_RS485(unsigned char *data, unsigned int length){
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	for(unsigned int i = 0; i < length; i ++){		
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1, data[i]);
	}
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);	
}
