#include "SystemTick.h"
void Delay_1ms(void){
	SysTick->LOAD = (72 * 1000000)/ 1000 - 1; // bo chia 1000
	SysTick->VAL = 0;
	SysTick->CTRL = 5; //0101 enable it, no interrupt, use system clock
	while(!(SysTick -> CTRL & (1 << 16))){ // wait count flag set
	}
}
void Delay_1us(void){
	SysTick->LOAD = (72 * 1000000)/ 1000000 - 1; // bo chia 1000 000
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	while(!(SysTick -> CTRL & (1 << 16))){
	}	
}
void Delay_ms(unsigned int ms){
	while(ms--){
		Delay_1ms();
	}
}
void Delay_us(unsigned int us){
	while(us--){
		Delay_1us();
	}
}
