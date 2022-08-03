#ifndef  sub_Funct_H_
#define  sub_Funct_H_



#include "cmsis_os.h"
#include "fatfs.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdint.h"
#include "stm32h7xx_hal.h"
#include "Define.h"

uint32_t run_Count_Pos_Total[20000];
uint16_t run_Pos_Index;
uint16_t run_Point_Count;
uint8_t Mode;
uint8_t temp_ID;
uint8_t temp_Speed;
uint8_t temp_PosX;
uint8_t temp_PosY;
uint8_t temp_PosZ;
uint8_t temp_PosA;
uint8_t temp_PosB;
uint8_t temp_PosC;
uint8_t temp_Output;
int32_t run_PosX;
int32_t run_PosY;
int32_t run_PosZ;
int32_t run_PosA;
int32_t run_PosB;
int32_t run_PosC;
uint32_t run_ID;
uint32_t run_Speed;
uint8_t sd_Process;
uint8_t run_Process;




char move_Data_Buffer[200];
char data_ID[20];
char data_Speed[20];
char data_PosX[20];
char data_PosY[20];
char data_PosZ[20];
char data_PosA[20];
char data_PosB[20];
char data_PosC[20];
char data_Output[50];



void count_Total_Point(void);
void sd_Data_Handle(void);
void output_Display(void);
void reset_Value(void);


#endif
