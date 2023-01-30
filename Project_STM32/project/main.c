#include "stm32f10x.h"
#include "main.h"
unsigned char version1 = 0;
typedef struct{
	unsigned int LED[MAX_PORT_LED];
}firmware;
firmware default_firmware = {
	99999, 99999, 99999, 99999, 99999, 99999, 99999, 99999
};
char N[120];
int main(void)
{
	Config_CLOCK_HSE_Std();
  Config_IWDG();
  Config_GPIO_OUTPUT_PortA();
	Config_GPIO_OUTPUT_PortB();
	Config_GPIO_OUTPUT_PortC();
	GPIO_ResetBits(GPIOA, GPIO_Pin_11| GPIO_Pin_12);	// M1 M0 Lora
	
	//SPI2_Master_Config();
	//SPI2_Master_Config_Res(); // oke
	//SPI1_Master_Config_Res(); // oke
	SPI1_Master_Config(); // oke
	SPI2_Slave_Config();
	//SPI2_Slave_Config_Res();
	SPI2_Enable();
	SPI1_Enable();
	
  Config_USART1_IT_Std();
	Config_USART2_IT_Std();
	
  Read_FLASH_Buff_Std(0x08000000 + (60 * 1024), (unsigned char *) &default_firmware, sizeof(default_firmware));
	if(default_firmware.LED[0] > 99999)default_firmware.LED[0] = 99999;
	if(default_firmware.LED[1] > 99999)default_firmware.LED[1] = 99999;
	if(default_firmware.LED[2] > 99999)default_firmware.LED[2] = 99999;
	if(default_firmware.LED[3] > 99999)default_firmware.LED[3] = 99999;
	SX1278_Init();
	Display7SEG();
	
  //Config_Timer2_IT_Std();
	Config_Timer2_Std();
	Config_Timer1_IT_Std();
  while (1)
  {		
		IWDG_ReloadCounter();
		//SX1278_Write_Register(0x42, 0x03);
    version1 = SX1278_Read_Register(0x42);
		sprintf(N, "%d", version1);
		USART1_Send_data_Std((unsigned char*) N, 2);
		Delay_Timer2_Ms_Std(100);
		
		//SPI_I2S_SendData(SPI1, 0x80);
		//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
	  //CS1_Disable();
		//SX1278_Write(0x09, 1);
		//dt = SX1278_Read(0x42);
		//CS1_Enable(); // low
		//SPI1_Send(0xFF);
		//dt = SPI1_Read();
		//CS1_Disable(); // high
		//GPIO_TOGGLE_LED();
		//dt = SPI1_Read();

//		checkRxBuffer();	
//		if(counter1ms >= 500){ 
//			GPIO_TOGGLE_LED();
//			counter1ms = 0;
//			ScanLed();
//		}
  }
}
//unsigned char Check_ADC(void){
//	value_ADC = ADC_GetConversionValue(ADC1);
//}
void Check_Flash(void){
	if((Arr_Data[0] <= 99999) && (Arr_Data[0] > 0) && (Arr_Data[1] <= 99999) && (Arr_Data[1] > 0) && 
		 (Arr_Data[2] <= 99999) && (Arr_Data[2] > 0) && (Arr_Data[3] <= 99999) && (Arr_Data[3] > 0)){
		if(default_firmware.LED[0] != Arr_Data[0] || default_firmware.LED[1] != Arr_Data[1] || default_firmware.LED[2] != Arr_Data[2] || default_firmware.LED[3] != Arr_Data[3]){
			default_firmware.LED[0] = Arr_Data[0];
			default_firmware.LED[1] = Arr_Data[1];
			default_firmware.LED[2] = Arr_Data[2];
			default_firmware.LED[3] = Arr_Data[3];
			Earse_FLASH_Std(0x08000000 + (60 * 1024));
			Write1byte_FLASH_Buff_Std(0x08000000 + (60 * 1024),(uint8_t *) &default_firmware, sizeof(default_firmware));
		}
	}
}
void Display7SEG(void){
	 sprintf(LED7SEG, "%.05d%.05d%.05d%.05d\r\n",default_firmware.LED[0], default_firmware.LED[1], default_firmware.LED[2], default_firmware.LED[3]);
}
void EXTI9_5_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line8) != 0){
		//GPIO_TOGGLE();
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	if(EXTI_GetITStatus(EXTI_Line7) != 0){
		Rx_Done_Flag = 1;
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}
void TIM1_UP_IRQHandler(void){
	if(TIM_GetITStatus(TIM1, TIM_IT_Update)){
		//Handle
		counter1ms++;
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)){
		//GPIO_TOGGLE_LED();
		//handle
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){	
		data_Rx = USART_ReceiveData(USART1);
		//USART_SendData(USART1,data_Rx);
		Send_RS485(&data_Rx, sizeof(data_Rx));
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){	
		RxBuffer[Index_In_RxBuffer] = USART_ReceiveData(USART2);
		Index_In_RxBuffer++;
		if(Index_In_RxBuffer >= MAX_INDEX_RXBUFF) Index_In_RxBuffer = 0;
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}
