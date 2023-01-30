#include "SPI.h"
void SPI1_Master_Config_Res(void){
  RCC->APB2ENR |= (1<<12);  // Enable SPI1 CLock
	
  SPI1->CR1 |= (1<<0)|(1<<1);   // CPOL=1, CPHA=1(mode 4)
	
  SPI1->CR1 |= (1<<2);  // Master Mode
	
  SPI1->CR1 |= (1<<4);  // BR[2:0] = 010: fPCLK/8, PCLK2 = 72MHz, SPI clk = 9MHz
	SPI1->CR1 &= ~((1<<5)|(1<<3));
	
  SPI1->CR1 &= ~(1<<7);  // LSBFIRST = 0, MSB first
	
  SPI1->CR1 |= (1<<8) | (1<<9);  // SSM=1, SSi=1 -> Software Slave Management
	
  SPI1->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex
	
  SPI1->CR1 &= ~(1<<11);  // DFF=0, 8 bit data (Data frame format 8 or 16 bit)
	
  SPI1->CR2 = 0;
// Config GPIO
  RCC->APB2ENR |=  (1<<2);  // Enable GPIOA clock
	
	GPIOA->CRL = 0;
	
	GPIOA->CRL |= (1<<23)|(1<<21)|(1<<20); // PA5 (SCK) AF output Push Pull
	GPIOA->CRL &= ~(1<<22);
	
	GPIOA->CRL |= (1U<<31)|(1U<<29)|(1U<<28); // PA7 (MOSI) AF output Push Pull
	GPIOA->CRL &= ~(1<<30);
	
	GPIOA->CRL &= ~((1<<25)|(1<<24)|(1<<27)); // PA6 (MISO) Input mode (floating)
	GPIOA->CRL |= (1<<26);

	GPIOA->CRL &= ~((1<<19)|(1<<18)); // PA4 used for CS, GPIO Output 
	GPIOA->CRL |= (1<<17)|(1<<16);
	
}
void SPI1_Slave_Config_Res(void){
  RCC->APB2ENR |= (1<<12);  // Enable SPI1 CLock
	
  SPI1->CR1 |= (1<<0)|(1<<1);   // CPOL=1, CPHA=1
	
  SPI1->CR1 &= ~(1<<2);  // Slave Mode
	
  SPI1->CR1 |= (1<<4);  // BR[2:0] = 010: fPCLK/8, PCLK2 = 72MHz, SPI clk = 9MHz
	SPI1->CR1 &= ~((1<<5)|(1<<3));
	
  SPI1->CR1 &= ~(1<<7);  // LSBFIRST = 0, MSB first
	
  SPI1->CR1 |= (1<<8) | (1<<9);  // SSM=1, SSi=1 -> Software Slave Management
	
  SPI1->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex
	
  SPI1->CR1 &= ~(1<<11);  // DFF=0, 8 bit data (Data frame format 8 or 16 bit)
	
  SPI1->CR2 = 0;
// Config GPIO
  RCC->APB2ENR |=  (1<<2);  // Enable GPIOA clock
	
	GPIOA->CRL = 0;
	
	GPIOA->CRL |= (1<<23)|(1<<21)|(1<<20); // PA5 (SCK) AF output Push Pull
	GPIOA->CRL &= ~(1<<22);
	
	GPIOA->CRL |= (1U<<31)|(1U<<29)|(1U<<28); // PA7 (MOSI) AF output Push Pull
	GPIOA->CRL &= ~(1<<30);
	
	GPIOA->CRL &= ~((1<<25)|(1<<24)); // PA6 (MISO) Input mode (floating)
	GPIOA->CRL &= ~(1<<27);
	GPIOA->CRL |= (1<<26);

	GPIOA->CRL &= ~((1<<19)|(1<<18)); // PA4 used for CS, GPIO Output 
	GPIOA->CRL |= (1<<17)|(1<<16);
	
	GPIOA->CRL |= (11U<<20);   // PA5 (SCK) AF output Push Pull
	GPIOA->CRL |= (11U<<28);   // PA7 (MOSI) AF output Push Pull
	GPIOA->CRL |= (1<<26);    // PA6 (MISO) Input mode (floating)
	GPIOA->CRL |= (3<<16);    // PA4 used for CS, GPIO Output 
}
void SPI2_Master_Config_Res(void){
  RCC->APB1ENR |= (1<<14);  // Enable SPI2 CLock
	
  SPI2->CR1 |= (1<<0)|(1<<1);   // CPOL=1, CPHA=1
	
  SPI2->CR1 |= (1<<2);  // Master Mode
	
  SPI2->CR1 |= (1<<3);  // BR[2:0] = 001: fPCLK/4, PCLK2 = 36MHz, SPI clk = 9MHz
	SPI2->CR1 &= ~((1<<5)|(1<<4));
	
  SPI2->CR1 &= ~(1<<7);  // LSBFIRST = 0, MSB first
	
  SPI2->CR1 |= (1<<8) | (1<<9);  // SSM=1, SSi=1 -> Software Slave Management
	
  SPI2->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex
	
  SPI2->CR1 &= ~(1<<11);  // DFF=0, 8 bit data (Data frame format 8 or 16 bit)
	
  SPI2->CR2 = 0;
// Config GPIO
  RCC->APB2ENR |=  (1<<3);  // Enable GPIOB clock
	
	GPIOB->CRH = 0;
	
	GPIOB->CRH |= (1<<23)|(1<<21)|(1<<20); // PB13 (SCK) AF output Push Pull
	GPIOB->CRH &= ~(1<<22);
	
	GPIOB->CRH |= (1U<<31)|(1U<<29)|(1U<<28); // PB15 (MOSI) AF output Push Pull
	GPIOB->CRH &= ~(1<<30);
	
	GPIOB->CRH &= ~((1<<25)|(1<<24)|(1<<27)); // PB14 (MISO) Input mode (floating)
	GPIOB->CRH |= (1<<26);

	GPIOB->CRH &= ~((1<<19)|(1<<18)); // PB15 used for CS, GPIO Output 
	GPIOB->CRH |= (1<<17)|(1<<16);
	
	GPIOB->CRH |= (11U<<20);   // PB13 (SCK) AF output Push Pull
	GPIOB->CRH |= (11U<<28);   // PB15 (MOSI) AF output Push Pull
	GPIOB->CRH |= (1<<26);    // PB14 (MISO) Input mode (floating)
	GPIOB->CRH |= (3<<16);    // PB12 used for CS, GPIO Output 
}
void SPI2_Slave_Config_Res(void){
  RCC->APB1ENR |= (1<<14);  // Enable SPI2 CLock
	
  SPI2->CR1 |= (1<<0)|(1<<1);   // CPOL=1, CPHA=1
	
  SPI2->CR1 &= ~(1<<2);  // Slave Mode
	
  SPI2->CR1 |= (1<<3);  // BR[2:0] = 001: fPCLK/4, PCLK2 = 36MHz, SPI clk = 9MHz
	SPI2->CR1 &= ~((1<<5)|(1<<4));
	
  SPI2->CR1 &= ~(1<<7);  // LSBFIRST = 0, MSB first
	
  SPI2->CR1 |= (1<<8) | (1<<9);  // SSM=1, SSi=1 -> Software Slave Management
	
  SPI2->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex
	
  SPI2->CR1 &= ~(1<<11);  // DFF=0, 8 bit data (Data frame format 8 or 16 bit)
	
  SPI2->CR2 = 0;
// Config GPIO
  RCC->APB2ENR |=  (1<<3);  // Enable GPIOB clock
	
	GPIOB->CRH = 0;
	
	GPIOB->CRH |= (1<<23)|(1<<21)|(1<<20); // PB13 (SCK) AF output Push Pull
	GPIOB->CRH &= ~(1<<22);
	
	GPIOB->CRH |= (1U<<31)|(1U<<29)|(1U<<28); // PB15 (MOSI) AF output Push Pull
	GPIOB->CRH &= ~(1<<30);
	
	GPIOB->CRH &= ~((1<<25)|(1<<24)|(1<<27)); // PB14 (MISO) Input mode (floating)
	GPIOB->CRH |= (1<<26);

	GPIOB->CRH &= ~((1<<19)|(1<<18)); // PB15 used for CS, GPIO Output 
	GPIOB->CRH |= (1<<17)|(1<<16);
	
	GPIOB->CRH |= (11U<<20);   // PB13 (SCK) AF output Push Pull
	GPIOB->CRH |= (11U<<28);   // PB15 (MOSI) AF output Push Pull
	GPIOB->CRH |= (1<<26);    // PB14 (MISO) Input mode (floating)
	GPIOB->CRH |= (3<<16);    // PB12 used for CS, GPIO Output 
}
void SPI1_Enable (void){
	SPI1->CR1 |= (1<<6);   // SPE=1, Peripheral enabled
}
void SPI1_Disable (void){
	SPI1->CR1 &= ~(1<<6);   // SPE=0, Peripheral Disabled
}
void CS1_Enable (void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}
void CS1_Disable (void){
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}
void SPI2_Enable (void){
	SPI2->CR1 |= (1<<6);   // SPE=1, Peripheral enabled
}
void SPI2_Disable (void){
	SPI2->CR1 &= ~(1<<6);   // SPE=0, Peripheral Disabled
}
void CS2_Enable (void){
	GPIOB->BSRR |= (1<<28);
}
void CS2_Disable (void){
	GPIOB->BSRR |= (1<<12); // PB12
}
void SPI1_Transmit (uint8_t *data, int lenght){
	
	/************** STEPS TO FOLLOW *****************
	1. Wait for the TXE bit to set in the Status Register
	2. Write the data to the Data Register
	3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
	4. Clear the Overrun flag by reading DR and SR
	************************************************/		
	int i=0;
	while (i<lenght)
	{
	   while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	   SPI1->DR = data[i];  // load the data into the Data Register
	   i++;
	}	
	while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (((SPI1->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	
	
	//  Clear the Overrun flag by reading DR and SR
	uint8_t temp = SPI1->DR;
					temp = SPI1->SR;
	
}
void SPI1_Receive (uint8_t *data, int lenght){
	/************** STEPS TO FOLLOW *****************
	1. Wait for the BSY bit to reset in Status Register
	2. Send some Dummy data before reading the DATA
	3. Wait for the RXNE bit to Set in the status Register
	4. Read data from Data Register
	************************************************/		

	while (lenght)
	{
		while (((SPI1->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication
		SPI1->DR = 0;  // send dummy data
		while (!((SPI1->SR) &(1<<0))){};  // Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
	  *data++ = (SPI1->DR);
		lenght--;
	}	
}
void SPI2_Transmit (uint8_t *data, int lenght){
	
	/************** STEPS TO FOLLOW *****************
	1. Wait for the TXE bit to set in the Status Register
	2. Write the data to the Data Register
	3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
	4. Clear the Overrun flag by reading DR and SR
	************************************************/		
	int i=0;
	while (i<lenght)
	{
	   while (!((SPI2->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	   SPI2->DR = data[i];  // load the data into the Data Register
	   i++;
	}	
	while (!((SPI2->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (((SPI2->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	
	
	//  Clear the Overrun flag by reading DR and SR
	uint8_t temp = SPI2->DR;
					temp = SPI2->SR;
	
}
void SPI2_Receive (uint8_t *data, int lenght){
	/************** STEPS TO FOLLOW *****************
	1. Wait for the BSY bit to reset in Status Register
	2. Send some Dummy data before reading the DATA
	3. Wait for the RXNE bit to Set in the status Register
	4. Read data from Data Register
	************************************************/		

	while (lenght)
	{
		while (((SPI2->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication
		SPI2->DR = 0;  // send dummy data
		while (!((SPI2->SR) &(1<<0))){};  // Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
	  *data++ = (SPI2->DR);
		lenght--;
	}	
}
void SPI1_Master_Config(void){
	GPIO_InitTypeDef 					GPIO_InitStructure;
	SPI_InitTypeDef           SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1|RCC_APB2Periph_GPIOA, ENABLE);
	// config SCLK & MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// config MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// config NSS || CS
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// config RST
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}
void SPI2_Master_Config(void){
	GPIO_InitTypeDef 					GPIO_InitStructure;
	SPI_InitTypeDef           SPI_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // 36/4 = 9M
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);
}
void SPI2_Slave_Config(void){
	GPIO_InitTypeDef 					GPIO_InitStructure;
	SPI_InitTypeDef           SPI_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// Config SCLK && MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// Config MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// Config NSS || CE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	SPI_Cmd(SPI2, ENABLE);
}
unsigned char SPI1_Read(void){
	unsigned char data;
	while(!(SPI1->SR & SPI_SR_RXNE));
	while(SPI1->SR & SPI_SR_BSY);
	data = SPI1->DR;
	return data;
}
void SPI1_Send(unsigned char data){
	SPI1->DR = data;
	while(!(SPI1->SR & SPI_SR_TXE));
	while(SPI1->SR & SPI_SR_BSY);
}
unsigned char SPI2_Read(void){
	unsigned char data;
	while(!(SPI2->SR & SPI_SR_RXNE));
	while(SPI2->SR & SPI_SR_BSY);
	data = SPI2->DR;
	return data;
}
void SPI2_Send(unsigned char data){
	SPI2->DR = data;
	while(!(SPI2->SR & SPI_SR_TXE));
	while(SPI2->SR & SPI_SR_BSY);
}
uint8_t SPI1_Exchange(unsigned char data){
	SPI_I2S_SendData(SPI1, data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET){}
	return SPI_I2S_ReceiveData(SPI1);
}