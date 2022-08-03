#ifndef  Define_H_
#define  Define_H_



#include "cmsis_os.h"
#include "fatfs.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdint.h"
#include "stm32h7xx_hal.h"
#define GPIO12 GPIO_PIN_12



/* ----------- SD Card variable -------------*/
FATFS fs; 			//file system
FIL myfile; 		//file
FRESULT fresult; 	// file result
UINT br,bw;   		//byte read,byte write

uint32_t bien_Count;

uint32_t displayValue;

uint32_t Rx_H1;
uint32_t Rx_H2;
uint32_t Rx_L1;
uint32_t Rx_L2;
uint32_t std_H;
uint32_t std_L;
/* ---- Run Mode variable ---- */


int32_t Run_File_No;
int32_t Run_Point_Count;
int32_t  Run_X_Axis_Value;
int32_t  Run_Y_Axis_Value;
int32_t  Run_Z_Axis_Value;
int32_t  Run_A_Axis_Value;
int32_t  Run_B_Axis_Value;
int32_t  Run_C_Axis_Value;
int32_t Run_ID_Value;
int32_t Run_Speed_Value;
uint32_t current_Millis;

uint8_t Run_Out0,Run_Out1,Run_Out2,Run_Out3,Run_Out4,Run_Out5,Run_Out6,Run_Out7,
Run_Out8,Run_Out9,Run_Out10,Run_Out11,Run_Out12,Run_Out13,Run_Out14,Run_Out15,Run_Out16,Run_Out17,
Run_Out18,Run_Out19,Run_Out20,Run_Out21,Run_Out22,Run_Out23,Run_Out24,Run_Out25,Run_Out26,Run_Out27,
Run_Out28,Run_Out29,Run_Out30,Run_Out31;


/*----- Teach Mode variable  -----*/

uint8_t  Teach_Move_Process;
uint32_t Teach_Point_Count;
uint32_t Teach_ID_Value;
uint32_t Teach_Speed_Value;

int32_t Teach_X_Axis_Value;
int32_t Teach_Y_Axis_Value;
int32_t Teach_Z_Axis_Value;
int32_t Teach_A_Axis_Value;
int32_t Teach_B_Axis_Value;
int32_t Teach_C_Axis_Value;
int32_t Teach_Velocity_Value;
int32_t Teach_Accel_Value;


uint32_t Temp_Coor_count;
uint32_t Main_Coor_count;
uint16_t Pos_Index;
uint8_t Main_process;


uint8_t Ouput0,Ouput2,Ouput3,Ouput4,Ouput5,Ouput6,Ouput7,Ouput8,Ouput9,Ouput10,Ouput11,
	Ouput13,Ouput15,Ouput18,Ouput20,Ouput22,Ouput23,Ouput25,
	Ouput26,Ouput27,Ouput28,Ouput29,Ouput30,Ouput31;

char PosX_data[50]; //Anh Duc Bop Dai, ban dau la 6
char PosY_data[50];//Anh Duc Bop Dai, ban dau la 6
char Posz_data[50];//Anh Duc Bop Dai, ban dau la 6     // Bi mat du lieu neu dat mang la PosZ_data ?? :D ??

char PosA_data[50];
char PosB_data[50];
char PosC_data[50];

char ID_data[50];
char Speed_data[50];


uint8_t Ouput32;
uint8_t Ouput33;
uint8_t Ouput34;
uint8_t Ouput35;
uint8_t Ouput36;
uint8_t Ouput37;
uint8_t Ouput38;
uint8_t Ouput39;



char SD_All_Point[30000];
char SD_Coordinates[30000];

char Out0[8],Out1[8],Out2[8],Out3[8],Out4[8],Out5[8],Out6[8],Out7[8],Out8[8],
Out9[8],Out10[8],Out11[8],Out12[8],Out13[8],Out14[8],Out15[8],Out16[8],Out17[8],Out18[8],Out19[8],
Out20[8],Out21[8],Out22[8],Out23[8],Out24[8],Out25[8],Out26[8],Out27[8],Out28[8],Out29[8],Out30[8],Out31[8];

char Out32[8],Out33[8],Out34[8],Out35[8],Out36[8],Out37[8],Out38[8],Out39[8];


 void HMI_Ini(void);


#endif    // DefineGPIO_H_
