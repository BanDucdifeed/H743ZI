#ifndef  sub_Funct_H_
#define  sub_Funct_H_

#include "sub_Funct.h"
#include "Define.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
uint32_t run_Count_Pos_Total[20000];
uint16_t run_Pos_Index = 0;
uint16_t run_Point_Count = 0;
uint8_t Mode = 0;

uint8_t temp_ID = 0;
uint8_t temp_Speed = 0;
uint8_t temp_PosX = 0;
uint8_t temp_PosY = 0;
uint8_t temp_PosZ = 0;
uint8_t temp_PosA = 0;
uint8_t temp_PosB = 0;
uint8_t temp_PosC = 0;
uint8_t temp_Output = 0;
int32_t run_PosX = 0;
int32_t run_PosY = 0;
int32_t run_PosZ = 0;
int32_t run_PosA = 0;
int32_t run_PosB = 0;
int32_t run_PosC = 0;
uint32_t run_ID = 0;
uint32_t run_Speed = 0;
uint8_t sd_Process = 0;
uint8_t run_Process = 0;




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






void count_Total_Point()
{
	run_Pos_Index = 0;
	for(uint32_t i = 0;i<=20000;i++)
	{
	  if(SD_All_Point[i] == 0x0D)
	  {
		  run_Count_Pos_Total[run_Pos_Index] = i;
		  run_Pos_Index++;
	  }
	  if(SD_All_Point[i] == 0x00)
	  {
		  break;
	  }
	}
}
void sd_Data_Handle()
{
	  if(run_Point_Count == 0)
	  {
		  for(uint32_t i = 0;i<=run_Count_Pos_Total[run_Point_Count];i++)
		  {
			  move_Data_Buffer[i] = SD_All_Point[i];
			  if(move_Data_Buffer[i] == 0x45)	// Ki tu 'E'
			  {
				  Mode = 0;
				  break;
			  }
		  }
	  }
	  else if(run_Point_Count > 0)
	  {
		  for(uint32_t i = 0 + run_Count_Pos_Total[run_Point_Count - 1];i <= run_Count_Pos_Total[run_Point_Count] - 1;i++)
		  {
			  move_Data_Buffer[i - run_Count_Pos_Total[run_Point_Count - 1]] = SD_All_Point[i + 1];
			  if(move_Data_Buffer[i - run_Count_Pos_Total[run_Point_Count - 1]] == 0x45)
			  {
				  Mode = 0;
				  break;
			  }
		  }
	  }
	  for(uint8_t i = 0;i<6;i++)
	  {
		  data_ID[i] = move_Data_Buffer[i+1];
		  temp_ID++;
		  if(data_ID[i] == 0x53)		// Ki tu 'S'
		  {
			  data_ID[temp_ID - 1] = 0x00;
			  break;
		  }
	  }
	  for(uint8_t i = temp_ID;i<12;i++)
	  {
		  data_Speed[i - temp_ID] = move_Data_Buffer[i+1];
		  temp_Speed++;
		  if(data_Speed[i - temp_ID] == 0x58)	// Ki tu 'X'
		  {
			  data_Speed[i - temp_ID] = 0x00;
			  break;
		  }
	  }
	  for(uint8_t i = temp_ID + temp_Speed;i<26;i++)
	  {
		  data_PosX[i - temp_ID - temp_Speed] = move_Data_Buffer[i+1];
		  temp_PosX++;
		  if(data_PosX[i - temp_ID - temp_Speed] == 0x59)	// Ki tu 'Y'
		  {
			  data_PosX[i - temp_ID - temp_Speed] = 0x00;
			  break;
		  }
	  }
	  for(uint8_t i = temp_ID + temp_Speed + temp_PosX;i<40;i++)
	  {
		  data_PosY[i - temp_ID - temp_Speed - temp_PosX] = move_Data_Buffer[i+1];
		  temp_PosY++;
		  if(data_PosY[i - temp_ID - temp_Speed - temp_PosX] == 0x5A)	// Ki tu 'Z'
		  {
			  data_PosY[i - temp_ID - temp_Speed - temp_PosX] = 0x00;
			  break;
		  }
	  }
	  for(uint8_t i = temp_ID + temp_Speed + temp_PosX + temp_PosY;i<54;i++)
	  {
		  data_PosZ[i - temp_ID - temp_Speed - temp_PosX - temp_PosY] = move_Data_Buffer[i+1];
		  temp_PosZ++;
		  if(data_PosZ[i - temp_ID - temp_Speed - temp_PosX - temp_PosY] == 0x41)	// Ki tu 'A'
		  {
			  data_PosZ[i - temp_ID - temp_Speed - temp_PosX - temp_PosY] = 0x00;
			  break;
		  }
	  }
	  for(uint8_t i = temp_ID + temp_Speed + temp_PosX + temp_PosY + temp_PosZ;i<67;i++)
	  {
		  data_PosA[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ] = move_Data_Buffer[i+1];
		  temp_PosA++;
		  if(data_PosA[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ] == 0x42)	// Ki tu 'B'
		  {
			  data_PosA[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ] = 0x00;
			  break;
		  }
	  }
	  for(uint8_t i = temp_ID + temp_Speed + temp_PosX + temp_PosY + temp_PosZ + temp_PosA;i<80;i++)
	  {
		  data_PosB[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ - temp_PosA] = move_Data_Buffer[i+1];
		  temp_PosB++;
		  if(data_PosB[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ - temp_PosA] == 0x43)	// Ki tu 'C'
		  {
			  data_PosB[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ - temp_PosA] = 0x00;
			  break;
		  }
	  }
	  for(uint8_t i = temp_ID + temp_Speed + temp_PosX + temp_PosY + temp_PosZ + temp_PosA + temp_PosB;i<93;i++)
	  {
		  data_PosC[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ - temp_PosA - temp_PosB] = move_Data_Buffer[i+1];
		  temp_PosC++;
		  if(data_PosC[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ - temp_PosA - temp_PosB] == 0x4F)	// Ki tu 'O'
		  {
			  data_PosC[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ - temp_PosA - temp_PosB] = 0x00;
			  break;
		  }
	  }
	  for(uint8_t i = temp_ID + temp_Speed + temp_PosX + temp_PosY + temp_PosZ + temp_PosA + temp_PosB + temp_PosC;i<93;i++)
	  {
		  data_Output[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ - temp_PosA - temp_PosB - temp_PosC] = move_Data_Buffer[i+1];
		  temp_Output++;
		  if(data_Output[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ - temp_PosA - temp_PosB - temp_PosC] == 0x45)	// Ki tu 'E'
		  {
			  data_Output[i - temp_ID - temp_Speed - temp_PosX - temp_PosY - temp_PosZ - temp_PosA - temp_PosB - temp_PosC] = 0x00;
			  break;
		  }
	  }

	  for(uint8_t i = 0 ;i<6;i++)
	  {
		  if(data_ID[i] == 0)
		  {
			  break;
		  }
		  run_ID = 10*run_ID + data_ID[i]-'0';

	  }
	  for(uint8_t i = 0 ;i<6;i++)
	  {
		  if(data_Speed[i] == 0)
		  {
			  break;
		  }
		  run_Speed = 10*run_Speed + data_Speed[i]-'0';

	  }
	  for(uint8_t i = 0 ;i<20;i++)
	  {
		  if(data_PosX[i] == 0)
		  {
			  break;
		  }
		  run_PosX = 10*run_PosX + data_PosX[i]-'0';
	  }
	  for(uint8_t i = 0 ;i<20;i++)
	  {
		  if(data_PosY[i] == 0)
		  {
			  break;
		  }
		  run_PosY = 10*run_PosY + data_PosY[i]-'0';
	  }
	  for(uint8_t i = 0 ;i<20;i++)
	  {
		  if(data_PosZ[i] == 0)
		  {
			  break;
		  }
		  run_PosZ = 10*run_PosZ + data_PosZ[i]-'0';
	  }
	  for(uint8_t i = 0 ;i<20;i++)
	  {
		  if(data_PosA[i] == 0)
		  {
			  break;
		  }
		  run_PosA = 10*run_PosA + data_PosA[i]-'0';
	  }
	  for(uint8_t i = 0 ;i<20;i++)
	  {
		  if(data_PosB[i] == 0)
		  {
			  break;
		  }
		  run_PosB = 10*run_PosB + data_PosB[i]-'0';
	  }
	  for(uint8_t i = 0 ;i<20;i++)
	  {
		  if(data_PosC[i] == 0)
		  {
			  break;
		  }
		  run_PosC = 10*run_PosC + data_PosC[i]-'0';
	  }
}

void output_Display()
{
	Run_ID_Value = run_ID;
	Run_X_Axis_Value = run_PosX;
	Run_Y_Axis_Value = run_PosY;
	Run_Z_Axis_Value = run_PosZ;
	Run_A_Axis_Value = run_PosA;
	Run_B_Axis_Value = run_PosB;
	Run_C_Axis_Value = run_PosC;
	Run_Speed_Value  = run_Speed;
	Run_Point_Count = run_Point_Count;
	Run_Out0 = data_Output[0] 	- '0';
	if(Run_Out0 == 1)
	{
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
	}
	else
	{
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
	}
	Run_Out1 = data_Output[1] 	- '0';
	if(Run_Out1 == 1)
	{
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	}
	else
	{
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	}
	Run_Out2 = data_Output[2] 	- '0';
	Run_Out3 = data_Output[3] 	- '0';
	Run_Out4 = data_Output[4] 	- '0';
	Run_Out5 = data_Output[5] 	- '0';
	Run_Out6 = data_Output[6] 	- '0';
	Run_Out7 = data_Output[7] 	- '0';
	Run_Out8 = data_Output[8] 	- '0';
	Run_Out9 = data_Output[9] 	- '0';
	Run_Out10 = data_Output[10] - '0';
	Run_Out11 = data_Output[11] - '0';
	Run_Out12 = data_Output[12] - '0';
	Run_Out13 = data_Output[13] - '0';
	Run_Out14 = data_Output[14] - '0';
	Run_Out15 = data_Output[15] - '0';
	Run_Out16 = data_Output[16] - '0';
	Run_Out17 = data_Output[17] - '0';
	Run_Out18 = data_Output[18] - '0';
	Run_Out19 = data_Output[19] - '0';
	Run_Out20 = data_Output[20] - '0';
	Run_Out21 = data_Output[21] - '0';
	Run_Out22 = data_Output[22] - '0';
	Run_Out23 = data_Output[23] - '0';
	Run_Out24 = data_Output[24] - '0';
	Run_Out25 = data_Output[25] - '0';
	Run_Out26 = data_Output[26] - '0';
	Run_Out27 = data_Output[27] - '0';
	Run_Out28 = data_Output[28] - '0';
	Run_Out29 = data_Output[29] - '0';
	Run_Out30 = data_Output[30] - '0';
	Run_Out31 = data_Output[31] - '0';
}

void reset_Value()
{
	  Teach_X_Axis_Value = 0;
	  Teach_Y_Axis_Value = 0;
	  Teach_Z_Axis_Value = 0;
	  Teach_A_Axis_Value = 0;
	  Teach_B_Axis_Value = 0;
	  Teach_C_Axis_Value = 0;
	  Teach_Move_Process = 0xFF;
	  Teach_ID_Value = 0;
	  Teach_Speed_Value = 0;
	  Teach_Point_Count = 0;
		temp_ID = 0;
		temp_Speed = 0;
		temp_PosX = 0;
		temp_PosY = 0;
		temp_PosZ = 0;
		temp_PosA = 0;
		temp_PosB = 0;
		temp_PosC = 0;
		run_ID = 0;
		run_Speed = 0;
		run_PosX = 0;
		run_PosY = 0;
		run_PosZ = 0;
		run_PosA = 0;
		run_PosB = 0;
		run_PosC = 0;
		run_Point_Count = 0;
		Run_File_No = 0;
		Run_Out0 = 0x00;
		Run_Out1 = 0x00;
		Run_Out2 = 0x00;
		Run_Out3 = 0x00;
		Run_Out4 = 0x00;
		Run_Out5 = 0x00;
		Run_Out6 = 0x00;
		Run_Out7 = 0x00;
		Run_Out8 = 0x00;
		Run_Out9 = 0x00;
		Run_Out10 = 0x00;
		Run_Out11 = 0x00;
		Run_Out12 = 0x00;
		Run_Out13 = 0x00;
		Run_Out14 = 0x00;
		Run_Out15 = 0x00;
		Run_Out16 = 0x00;
		Run_Out17 = 0x00;
		Run_Out18 = 0x00;
		Run_Out19 = 0x00;
		Run_Out20 = 0x00;
		Run_Out21 = 0x00;
		Run_Out22 = 0x00;
		Run_Out23 = 0x00;
		Run_Out24 = 0x00;
		Run_Out25 = 0x00;
		Run_Out26 = 0x00;
		Run_Out27 = 0x00;
		Run_Out28 = 0x00;
		Run_Out29 = 0x00;
		Run_Out30 = 0x00;
		Run_Out31 = 0x00;
		Run_ID_Value = 0x00;
		Run_X_Axis_Value = 0x00;
		Run_Y_Axis_Value = 0x00;
		Run_Z_Axis_Value = 0x00;
		Run_A_Axis_Value = 0x00;
		Run_B_Axis_Value = 0x00;
		Run_C_Axis_Value = 0x00;
		Run_Speed_Value  = 0x00;
		Run_Point_Count = run_Point_Count;
		for(uint8_t i = 0;i<20;i++)
		{
			data_ID[i] = 0x00;
			data_Speed[i] = 0x00;
			data_PosX[i]   = 0x00;
			data_PosY[i]   = 0x00;
			data_PosZ[i]   = 0x00;
			data_PosA[i]   = 0x00;
			data_PosB[i]   = 0x00;
			data_PosC[i]   = 0x00;
		}
		for(uint8_t i=0;i<50;i++)
		{
			data_Output[i] = 0x00;
		}
		for(uint8_t i =0;i<200;i++)
		{
			move_Data_Buffer[i] = 0x00;
		}
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
}


#endif
