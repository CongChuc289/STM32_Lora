#include "RING_BUFFER.h"

unsigned char  RxByte;
unsigned char  RxBuffer[MAX_INDEX_RXBUFF];
unsigned char  cmdBuffer[MAX_SIZE_CMD_BUFF];
unsigned short Index_In_RxBuffer = 0;
unsigned short Index_Out_RxBuffer = 0;
unsigned char  Index_cmdBuff = 0;

char Buffer_Money[SIZE_DATA];
unsigned int Arr_Data[SIZE_ARR_DATA];

char M[128];

void checkRxBuffer(void){
	if(Index_Out_RxBuffer != Index_In_RxBuffer){
		RxByte = RxBuffer[Index_Out_RxBuffer];
		if(RxByte == '*'){
			if(Index_cmdBuff > 8 ) Index_cmdBuff = 0;
		}
		cmdBuffer[Index_cmdBuff] = RxByte;
		if(Index_cmdBuff < MAX_SIZE_CMD_BUFF - 1) Index_cmdBuff++; 
		if(RxByte == '\n'){
			cmdBuffer[Index_cmdBuff] = 0;
			if(cmdBuffer[0] == '*' && cmdBuffer[1] == '1' && cmdBuffer[2] == '0' && cmdBuffer[3] == '0' && cmdBuffer[4] == '*'){
				workCmdBuffer(cmdBuffer);
			}
			cmdBuffer[0] = 0;
			cmdBuffer[1] = 0;
			cmdBuffer[Index_cmdBuff - 1] = 0;
			Index_cmdBuff = 0;
		}			
		//------------------------------
		Index_Out_RxBuffer++;
		if(Index_Out_RxBuffer >= MAX_INDEX_RXBUFF) Index_Out_RxBuffer = 0;	
	}
}
void workCmdBuffer(unsigned char *cmdBuffer_t){
	unsigned char Index_arr = 0;
	if(cmdBuffer_t[5] == '|'){
		if(strncmp((char*)cmdBuffer_t, "*100*" , 5) == 0){
			char *ptr = NULL;
			ptr = strtok((char*)cmdBuffer_t + 6, "||"); 
			while(ptr != NULL){
				//strcpy((char *)Arr_Data, ptr);	
				Arr_Data[Index_arr++] = atoi(ptr);
				ptr = strtok(NULL, "||");
				if(Index_arr >= SIZE_ARR_DATA) break;
			}
			Display7SEG();
			Check_Flash();
			sprintf(M, "%d, %d, %d, %d, %d, %d", Arr_Data[0], Arr_Data[1], Arr_Data[2], Arr_Data[3], Arr_Data[4], Arr_Data[5]);
			Send_RS485((unsigned char *)M, strlen(M));
			Send_RS485((unsigned char*)"\r\n", strlen("\r\n"));
			Index_arr = 0;
		}
	}
}
