#include "HC595.h"

unsigned char Arr_Data_Led[] = {
  0xFC, 0x61, 0xDB, 0xF2, 0x67, 0xB7, 0xBE, 0xE0, 0xFF, 0xF7,  // 0 -> 9
};
char LED7SEG[SIZE_ARR];

void ShiftByte(register unsigned char P1, register  unsigned char P2, register  unsigned char P3, 
	register  unsigned char P4, register  unsigned char P5, register  unsigned char P6, 
	register  unsigned char P7, register  unsigned char P8)
{
	for(register unsigned char i = 0; i < 8; i++)
	{
		if(P1 & 0x80) DATA1_HIGH;
		else DATA1_LOW;
		if(P2 & 0x80) DATA2_HIGH;
		else DATA2_LOW;
		if(P3 & 0x80) DATA3_HIGH;
		else DATA3_LOW;		
		if(P4 & 0x80) DATA4_HIGH;
		else DATA4_LOW;	
		if(P5 & 0x80) DATA5_HIGH;
		else DATA5_LOW;		
		if(P6 & 0x80) DATA6_HIGH;
		else DATA6_LOW;	
		if(P7 & 0x80) DATA7_HIGH;
		else DATA7_LOW;
		if(P8 & 0x80) DATA8_HIGH;
		else DATA8_LOW;
		
		CLK_HIGH;		
		P1 = P1 << 1;
		P2 = P2 << 1;
		P3 = P3 << 1;
		P4 = P4 << 1;
		P5 = P5 << 1;
		P6 = P6 << 1;
		P7 = P7 << 1;
		P8 = P8 << 1;
		CLK_LOW;
	}	
}
void ScanLed(void)
{
		register unsigned char i;
		for(i = 0; i < 5; i++){
		  ShiftByte(Arr_Data_Led[LED7SEG[i]-0x30], Arr_Data_Led[LED7SEG[5 + i]-0x30], Arr_Data_Led[LED7SEG[10+i]-0x30],
			Arr_Data_Led[LED7SEG[15+i]-0x30],Arr_Data_Led[0], Arr_Data_Led[1], Arr_Data_Led[2], Arr_Data_Led[3]);			
		}
		LAT_LOW;
		LAT_HIGH;
}
