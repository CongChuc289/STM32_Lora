#include "ADC.h"

void Init_ADC(void){
	ADC_InitTypeDef       ADC1_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
	Config_GPIO_ADC_PortA();
	
	ADC1_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC1_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC1_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC1_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC1_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC1_InitStruct.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC1_InitStruct);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

