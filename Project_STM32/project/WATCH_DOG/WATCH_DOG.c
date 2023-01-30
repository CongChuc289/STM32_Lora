#include "WATCH_DOG.h"
void Config_IWDG(void){
	IWDG_Enable();
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	IWDG_SetReload(312); // 2s
}
