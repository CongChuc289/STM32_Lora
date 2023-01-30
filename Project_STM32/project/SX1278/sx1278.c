#include "sx1278.h"
#include "SPI.h"
#include "TIMER.h"
#include "USART.h"
#include <stdio.h>

uint8_t buf[SX1278_MAX_PACKET];

uint8_t SX1278_Read_Register(uint8_t addr){
	uint8_t value;
	CS1_Enable();
	SPI1_Send(addr & 0x7f);
	value = SPI1_Read();
	CS1_Disable();
	return value;
}
void SX1278_Write_Register(uint8_t addr, uint8_t cmd){
	CS1_Enable();
	SPI1_Send(addr | 0x80); // bit1 : which is 1 for write access and 0 for read access.
	SPI1_Send(cmd);
	CS1_Disable();
}		
void SX1278_BurstRead(uint8_t addr, uint8_t *cmd, uint8_t length){
	uint8_t i = 0;
	if(length <= 1) return;
	else {
		CS1_Enable();
		SPI1_Send(addr & 0x7f);
		for(i = 0; i < length; i++){
			cmd[i] = SPI1_Read();
		}
		CS1_Disable();
	}
}
void SX1278_BurstWrite(uint8_t addr, uint8_t *cmd, uint8_t length){
	unsigned char i = 0;
	if(length <= 1) return;
	else {					
		CS1_Enable();
		SPI1_Send(addr | 0x80);
		for(i = 0; i < length; i++){
			SPI1_Send(cmd[i]);
		}
	CS1_Disable();	
	}
}
void SX1278_Set_Freq(uint32_t freq) {
	//Datasheet page 37
	#define F_XOSC 32000000UL
	uint64_t f_Rf = ( (uint64_t)(freq) << 19 ) / F_XOSC;

	SX1278_Write_Register( RegFrfMsb,(f_Rf >> 16) & 0xFF );
	SX1278_Write_Register( RegFrMid, (f_Rf >> 8) & 0xFF );
	SX1278_Write_Register( RegFrLsb, (f_Rf >> 0) & 0xFF );
}
void SX1278_Sleep(void){
	SX1278_Write_Register(RegOpMode, SLEEP_Mode | LORA_Mode);
}
void SX1278_Standby(void){
	SX1278_Write_Register(RegOpMode, STDBY_Mode | LORA_Mode);
}
//OverCurrentProtection(bao ve qua dong)
void SX1278_Set_Ocp( uint8_t max_current ) {
	//Datasheet page 85
	uint8_t ocp_trim;

	if( max_current > 240 ) max_current = 240;

	if( max_current <= 120 ) {
		//max_current = 45 + 5 * ocp_trim;
		ocp_trim = (max_current - 45) / 5;
	} else if( max_current <= 240 ) {
		//max_current = 10 * ocp_trim - 30;
		ocp_trim = (max_current + 30) / 10;
	} else {
		ocp_trim = 27;
	}
	SX1278_Write_Register( RegOcp, (1<<5) | ( ocp_trim & 0x1F) );
}
void SX1278_Set_Bandwidth(uint8_t mode ) {
	//Datasheet page 112
	SX1278_Write_Register(RegModemConfig1, ((SX1278_Read_Register(RegModemConfig1) & 0x0F) | (mode << 4)));
}
void SX1278_Set_SpreadingFactor(uint8_t SF){
	//DataSheet page 113
	SX1278_Write_Register(RegModemConfig2, ((SX1278_Read_Register(RegModemConfig2) & 0x0F) | (SF << 4)));
}
void SX1278_Set_CodingRate(uint8_t rate){
	SX1278_Write_Register(RegModemConfig1, ((SX1278_Read_Register(RegModemConfig1) & 0xF1) | (rate << 1)));
}
void SX1278_Set_LnAGain(void){
	SX1278_Write_Register(RegLna, 0x23);
}
void SX1278_Set_Power(uint8_t db){
	//Datasheet page 84

	//RegPaDac: 7-3 reserved with 0x10 default value, which has to be ratained (!), 2-0 pa dac
	//Note: 0x10 << 3 = 0x80

	//RegPaConfig -> datasheet page 109
	//RegPaConfig: 7 PaSelect, 6-4 MaxPower, 3-0 OutputPower

	//db = 17-(15-OutputPower) = 2+OutputPower
	//OutputPower = db - 2

	//Set max current as 150mA
	SX1278_Set_Ocp(150);

	if( db > 17 )  {
		if( db > 20 ) db = 20; //Clamp max power to 20
		SX1278_Write_Register( RegPaDac, (0x10 << 3) | 0x07 );
		SX1278_Write_Register( RegPaConfig, PA_BOOST | ( (db - 2) - 3 ) );
	} else {
		if( db < 2 ) db = 2; //Clamp min power to 2
		SX1278_Write_Register( RegPaDac, (0x10 << 3) | 0x04 );
		SX1278_Write_Register( RegPaConfig, PA_BOOST | (db - 2) );
	}	
}
int SX1278_Get_RSSI(void){
	//LF
	//return (-164 + (SX1278_Read_Register(RegPktRssiValue)));
	//HF
	return (-157 + (SX1278_Read_Register(RegPktRssiValue)));
} 
void SX1278_Explicit_Header(void){
	//Datasheet page 29 && 112 
	//Explicit mode: preamble + header + crc + payload + payload_crc
	register uint8_t reg_modem_config_1 = SX1278_Read_Register(RegModemConfig1);
	//RegModemConfig1: 7-4 signal bandwith, 3-1 error coding rate, 0 header type
	SX1278_Write_Register(RegModemConfig1, RegModemConfig1 & 0xFE );
}	
void SX1278_RX_Continuous(void){
	SX1278_Write_Register(RegOpMode, RXCONTINUOUS_Mode | LORA_Mode);
}
uint8_t SX1278_Init(void){
	CS1_Disable(); // high
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	
	
	
	uint8_t version = SX1278_Read_Register(RegVersion);
	if( version != 0x12 ) return 0;
	
	SX1278_Sleep();
	SX1278_Write_Register(RegOpMode, LORA_Mode);
	
	// 433Mhz
//	SX1278_Write_Register( RegFrfMsb,0x6C );
//	SX1278_Write_Register( RegFrMid, 0x40 );
 //	SX1278_Write_Register( RegFrLsb, 0x00 );
	SX1278_Set_Freq(433E6);
	 // Reset FIFO addresses
	SX1278_Write_Register(RegFiFoTxBaseAddr, 0x00);
	SX1278_Write_Register(RegFiFoRxBaseAddr, 0x00);
	
	//Datasheet page: 95
	SX1278_Set_LnAGain();
	
	//Map DIO0 to RX_DONE irq
	SX1278_Write_Register(RegDioMapping1, 0x00); // DIO0-3 Mapping1/ DIO45 Mapping2	
	
	SX1278_Set_Bandwidth(BANDWIDTH);
	SX1278_Set_SpreadingFactor(SPREADING_FACTOR);
	SX1278_Set_CodingRate(CODING_RATE);
	
	SX1278_Set_Power(20);
	
	SX1278_Explicit_Header();
	SX1278_Standby();
	Delay_Timer2_Ms_Std(50);
	SX1278_RX_Continuous();
	return 1;
}
void SX1278_Transmission(uint8_t* buff, uint8_t length){
	//Datasheet page 38
	if(length == 0) return;
	//1. Mode request STAND-BY
	SX1278_Standby();
	//2. Tx Init
	//SX1278_Write_Register(RegOpMode, TX_Mode | LORA_Mode);
	//3. Write data to FIFO
	//3.1 Set FifoPtrAddr to FifoTxPtrBase
	SX1278_Write_Register(RegFiFoAddPtr, 0x00);
	//3.2 Write PayloadLength bytes to the FIFO (RegFifo)
	for(uint8_t i = 0; i < length; i++) // 256byte
		SX1278_Write_Register(RegFifo, buff[i]);
		SX1278_Write_Register(RegPayloadLength, length);
	//4. Mode request TX
	SX1278_Write_Register(RegOpMode, TX_Mode | LORA_Mode);
	//5. Wait for IRQ TxDone
	while( (SX1278_Read_Register(RegIrqFlags) & IRQ_TX_DONE_MASK) == 0 );
	SX1278_Write_Register(RegIrqFlags, (SX1278_Read_Register(RegIrqFlags) & IRQ_TX_DONE_MASK));
	//6. Auto mode change to STAND-BY
	SX1278_RX_Continuous();
	//7. If new tx, go to 3
	//8. New mode request
}
void SX1278_Receive(void){
	//Datasheet page 39
	//1. Mode request STAND-BY
	SX1278_Standby();
	//2. RX init
	//3. Request mode rx continues
	if(Rx_Done_Flag){
		uint8_t length;
		uint8_t IRQ = SX1278_Read_Register(RegIrqFlags);
		// Check if CRC Error Occur
		if((IRQ & IRQ_PAYLOAD_CRC_ERROR_MASK)){
			//If yes, run callback with crc error status and none data
			//if()
			if((IRQ & IRQ_RX_DONE_MASK)){
			//Check how many data arrived
			length = SX1278_Read_Register(RegRxNbBytes);
			//Set FIFO address to begining of the last received packet.
		  SX1278_Write_Register(RegFiFoAddPtr, SX1278_Read_Register(RegFiFoRxCurrentAddr));
			//Read FIFO to buffer
      for( uint8_t i = 0; i < length; i++ ){
				buf[i] = SX1278_Read_Register(RegFifo);
      }		
			//Run callback with data
			}
		}
	}			
}
void SX1278_Reset(void){
	CS1_Disable();
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	Delay_Timer2_Ms_Std(1);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	Delay_Timer2_Ms_Std(100);
}