#ifndef SPI_H_
#define SPI_H_
#include "stm32f10x.h"
#include "GPIO.h"
void SPI1_Master_Config_Res(void);
void SPI2_Master_Config_Res(void);
void SPI1_Slave_Config_Res(void);
void SPI2_Slave_Config_Res(void);

void SPI1_Transmit (uint8_t *data, int lenght);
void SPI1_Receive (uint8_t *data, int lenght);
void SPI2_Transmit (uint8_t *data, int lenght);
void SPI2_Receive (uint8_t *data, int lenght);

void SPI1_Enable (void);
void SPI1_Disable (void);
void CS1_Enable (void);
void CS1_Disable (void);

void SPI2_Enable (void);
void SPI2_Disable (void);
void CS2_Enable (void);
void CS2_Disable (void);

unsigned char SPI1_Read(void);
void SPI1_Send(unsigned char data);
unsigned char SPI2_Read(void);
void SPI2_Send(unsigned char data);
uint8_t SPI1_Exchange(unsigned char data);

void SPI1_Master_Config(void);
void SPI2_Master_Config(void);
void SPI1_Slave_Config(void);
void SPI2_Slave_Config(void);

void ConfigGPIO_SPI(void);


#endif
