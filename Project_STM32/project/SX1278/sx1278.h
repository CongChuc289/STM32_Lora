#ifndef SX1278_H_
#define SX1278_H_
#include "stm32f10x.h"

#define SX1278_MAX_PACKET	256

#define SPREADING_FACTOR	SF_7
#define CODING_RATE				CR_4_5
#define BANDWIDTH				  BW_125kHz
#define FREQUENCY				  433E6

//  Registers Summary
#define RegFifo               0x00
#define RegOpMode             0x01
#define RegFrfMsb             0x06
#define RegFrMid              0x07
#define RegFrLsb							0x08
#define RegPaConfig						0x09
#define RegPaRamp             0x0A
#define RegOcp								0x0B
#define RegLna								0x0C
#define RegFiFoAddPtr					0x0D
#define RegFiFoTxBaseAddr			0x0E
#define RegFiFoRxBaseAddr			0x0F
#define RegFiFoRxCurrentAddr	0x10
#define RegIrqFlags						0x12
#define RegRxNbBytes					0x13
#define RegRxHeaderCntValueMsb 0x14
#define RegRxHeaderCntValueLsb 0x15
#define RegRxPacketCntValueMsb 0x16
#define RegRxPacketCntValueLsb 0x17
#define RegModemStat          0x18
#define RegPktSnrValue        0x19
#define RegPktRssiValue				0x1A
#define RegRssiValue          0x1B
#define RegHopChannel         0x1C
#define	RegModemConfig1				0x1D
#define RegModemConfig2				0x1E
#define RegSymbTimeoutL				0x1F
#define RegPreambleMsb				0x20
#define RegPreambleLsb				0x21
#define RegPayloadLength			0x22
#define RegMaxPayloadLength   0x23
#define RegHopPeriod          0x24
#define LR_RegFifoRxByteAddr  0x25
#define RegModemConfig3				0x26

#define RegFeiMsb     				0x28
#define RegFeiMid     				0x29
#define RegFeiLsb     				0x2A

#define RegRssiWideband      	0x2C
#define RegDetectOptimize     0x31

#define RegInvertIQ           0x33
#define RegDetectionThreshold 0x37
#define RegSyncWord           0x39
#define RegDioMapping1				0x40
#define RegDioMapping2				0x41
#define RegVersion						0x42
#define RegTcxo					     	0x4B
#define RegPaDac				     	0x4D
#define RegFormerTemp				  0x5B
#define RegAgcRef				      0x61
#define RegAgcThresh1				  0x62
#define RegAgcThresh2				  0x63
#define RegAgcThresh3				  0x64
#define RegPll			      	  0x70

// RegOpMode - Mode
#define SLEEP_Mode            0x00
#define STDBY_Mode            0x01
#define FSTX_Mode             0x02
#define TX_Mode               0x03
#define FSRX_Mode             0x04
#define RXCONTINUOUS_Mode     0x05
#define RXSINGLE_Mode         0x06

// RegOpMode - LongRangeMode
#define LORA_Mode             0x80
#define FCK_OOK_Mode          0x00

// RegModemConfig - Bandwidth
#define BW_7_8kHz             0x00
#define BW_10_4kHz            0x01
#define BW_15_6kHz            0x02
#define BW_20_8kHz            0x03
#define BW_31_25kHz           0x04
#define BW_41_7kHz            0x05
#define BW_62_5kHz            0x06
#define BW_125kHz             0x07
#define BW_250kHz             0x08
#define BW_500kHz             0x09

// RegModemConfig - CodingRate
#define CR_4_5                0x01
#define CR_4_6                0x02
#define CR_4_7                0x03
#define CR_4_8                0x04

// RegPaConfig - PaSelect
#define PA_RFO                0x00
#define PA_BOOST              0x80

// RegModemConfig2 - SpreadingFactor
#define SF_6                   6
#define SF_7                   7
#define SF_8                   8
#define SF_9                   9
#define SF_10                  10
#define SF_11                  11
#define SF_12                  12

//------ POWER GAIN ------//
#define POWER_11db				0xF6
#define POWER_14db				0xF9
#define POWER_17db				0xFC
#define POWER_20db				0xFF


//RegIrqFlags
#define IRQ_TX_DONE_MASK			      0x08
#define IRQ_PAYLOAD_CRC_ERROR_MASK	0x20
#define IRQ_RX_DONE_MASK			      0x40

extern volatile uint8_t Rx_Done_Flag;

uint8_t SX1278_Read_Register(uint8_t addr);
void SX1278_Write_Register(uint8_t addr, uint8_t cmd);
void SX1278_Set_Freq(uint32_t freq);
void SX1278_Sleep(void);
void SX1278_Standby(void);
uint8_t SX1278_Init(void);

uint8_t ReadRegister(uint8_t addr);
uint8_t SX1278_Read(uint8_t addr);
void SX1278_Write(uint8_t addr, uint8_t cmd);
void SX1278_Set_Bandwidth(uint8_t mode);
void SX1278_Set_SpreadingFactor(uint8_t SF);
void SX1278_Reset(void);
#endif
