/*
 * Control_Step_Motor.c
 *
 *  Created on: Mar 6, 2020
 *      Author: TL-APRO-NPC 16
 *
 *	Modify By N.K.Dinh / 18/Nov/2021
 *      x<------------------------------0.0
 *      								l
 *      								l
 *      								l
 *      								l
 *      								l
 *      								l
 *      								l
 *      								↓
 *      								y
 *
 */

#ifndef CONTROL_STEP_MOTOR_C_
#define CONTROL_STEP_MOTOR_C_

//==============================================

#include "Control_Step_Motor.h"
#include "stm32h7xx_it.h"
#include <stdio.h>
#include <stdlib.h>

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim17;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim15;

//==============================================

#define Angle   0.036                           //  Angle of 1 step
#define Z_Speed    1
#define Origin_Timer   10
#define Circle_Timer  50

uint32_t Accel_Edge = 0;                         //  Step to Accel
uint32_t Decel_Edge = 0;                         //  Step to Decel

float Accel = 500000;   // Set gia toc, cang lon gia toc cang lon-700,000
float Limit_Timer = 70; // Set Speed  10 -> 100 ,Cang nho toc do cang lon

float C0;
float Cn;
uint16_t Step[66000];
float Limit_Timer;
uint32_t n;

uint32_t Check_count = 0;
uint32_t Check_timer = 0;
uint32_t Check_count1 = 0;



//==============================================


uint32_t Set_Edge_X = 0;           //Number of Edge
uint32_t Current_Edge_X = 0;

uint32_t Set_Edge_Y = 0;           //Number of Edge
uint32_t Current_Edge_Y = 0;

uint32_t Set_Edge_Z = 0;           //Number of Edge
uint32_t Current_Edge_Z = 0;

uint32_t X_index=0;
uint32_t Y_index=0;
uint32_t Z_index=0;

uint8_t T5X_index = 0;
uint8_t T5Y_index = 0;

//==============================================

uint8_t Busy_Flag_X = 0;
uint8_t Busy_Flag_Y = 0;
uint8_t Busy_Flag_Z = 0;
uint8_t Busy_Flag_XY = 0;
uint8_t Busy_Flag_XYZ = 0;

uint8_t Origin_Flag_X = 0;
uint8_t Origin_Flag_Y = 0;

uint8_t Origin_Flag_Z = 0;
uint8_t Origin_Flag   = 0;


uint8_t Check_EMG = 0;

/*---Synchronization XY Parameter---*/

//LINE

int32_t dx = 0;
int32_t dy = 0;
int32_t dz = 0;
float m = 0;
int32_t P = 0;

//CIRCLE

uint16_t Radius = 0;
int32_t R2 = 0;
uint16_t vR = 0;
float X = 0;
float Y = 0;
int32_t Pre_X = 0;
int32_t Pre_Y = 0;
uint8_t status = 0;
int flag_org_x = 0,flag_org_y = 0, flag_org_z = 0 ;

//For generating points on a 3-D line 
//using Bresenham's Algorithm 

uint8_t process_move=0;
int32_t P1_value, P2_value;
int8_t flag_stop_xyz = 0;
int32_t Current_PosXYZ = 0 ;
uint32_t Set_Edge_XYZ = 0;           //Number of Edge
uint32_t Current_Edge_XYZ = 0;
uint32_t XYZ_index=0;


/////////////////////MOTOR A - MOTOR B ///////////////
uint32_t A_index=0;
uint32_t B_index=0;


uint32_t Set_Edge_A = 0;           //Number of Edge
uint32_t Current_Edge_A = 0;

uint32_t Set_Edge_B = 0;           //Number of Edge
uint32_t Current_Edge_B = 0;

uint32_t Set_Edge_C = 0;           //Number of Edge
uint32_t Current_Edge_C = 0;

uint8_t process_origin_A =0;
uint8_t process_origin_B =0;
uint8_t Busy_Flag_Origin_A=0 ,Busy_Flag_Origin_B= 0 ;

// Syn 6 Axis  // dkn
int32_t denta[6];
int32_t d_max = 0;
int32_t P3_value, P4_value, P5_value;
int32_t P_value[6];

void Motor_Init(void)
{
   HAL_GPIO_WritePin(MotorX_ENA, SET);
   HAL_GPIO_WritePin(MotorY_ENA, SET);
   HAL_GPIO_WritePin(MotorZ_ENA, SET);
	HAL_GPIO_WritePin(MotorA_ENA, SET);
	HAL_GPIO_WritePin(MotorB_ENA, SET);
	HAL_GPIO_WritePin(MotorC_ENA, SET);
   C0 = 10000000*sqrt(2*Angle/Accel)*0.676;
      Step[0] = C0;
      Cn = C0;
      Accel_Edge = 1;
      for(uint16_t i=0; i<65535; i++)
      {
          if(Cn >= Limit_Timer)
          {
    	      n++;
   	      Cn = Step[n-1]-2*Step[n-1]/(4*n+1);
   	      if(Cn >= Limit_Timer)
   	         Step[n] = Cn;
          }
          if(Cn < Limit_Timer)
             break;
          Accel_Edge++;
          Decel_Edge = Accel_Edge;
      }
}



void Origin_Motor(void)
{

	HAL_GPIO_WritePin(MotorX_DIR, SET);
	HAL_GPIO_WritePin(MotorY_DIR, SET);
	HAL_GPIO_WritePin(MotorZ_DIR, RESET);

	Origin_Flag   = 1;
	Origin_Flag_X = 1;
	Origin_Flag_Y = 1;
	Origin_Flag_Z = 1;

	HAL_TIM_Base_Start_IT(&htim5);
	htim5.Init.Period = Origin_Timer;

}
void TIM5_IRQHandler(void)
{

	T5X_index++;
	T5Y_index++;


	if(!HAL_GPIO_ReadPin(SensorX) && T5X_index > 6 && flag_org_x == 0 && flag_org_z ==1)
	//if(!HAL_GPIO_ReadPin(SensorX)  && flag_org_x == 0 && flag_org_z ==1)
	{
		HAL_GPIO_TogglePin(MotorX_PUL);
		T5X_index = 0;
	}
	else if(HAL_GPIO_ReadPin(SensorX))
	{
		Origin_Flag_X = 0;
		flag_org_x = 1;
	}

	if(!HAL_GPIO_ReadPin(SensorY) && T5Y_index > 6 && flag_org_y == 0  && flag_org_z ==1)
	//if(!HAL_GPIO_ReadPin(SensorY) && flag_org_y == 0  && flag_org_z ==1)
	{
		HAL_GPIO_TogglePin(MotorY_PUL);
		T5Y_index = 0;
	}
	else if(HAL_GPIO_ReadPin(SensorY))
	{
		Origin_Flag_Y = 0;
		flag_org_y = 1;
	}




	if(!HAL_GPIO_ReadPin(SensorZ) && flag_org_z == 0)
	{
		HAL_GPIO_TogglePin(MotorZ_PUL);
		flag_org_z = 0;
	}

	else
	{
		Origin_Flag_Z = 0;
		flag_org_z = 1;
	}


	if(!Origin_Flag_X && !Origin_Flag_Y && !Origin_Flag_Z )
	{
		HAL_TIM_Base_Stop_IT(&htim5);
		HAL_GPIO_WritePin(MotorX_PUL, RESET);
		HAL_GPIO_WritePin(MotorY_PUL, RESET);
		HAL_GPIO_WritePin(MotorZ_PUL, RESET);
		flag_org_x = 0 ;
		flag_org_y = 0 ;
		flag_org_z = 0 ;
		Origin_Flag = 0;
		Current_PosX = 0;
		Current_PosY = 0;
		Current_PosZ = 0;

	}
	TIM5->ARR = Origin_Timer;
	 HAL_TIM_IRQHandler(&htim5);
}



/*void Draw_Circle_XY(int32_t Ox, int32_t Oy, uint16_t R,float speed_value,float Accel_value)
{
	if (speed_value < 1 )speed_value = 1 ;
	if (speed_value > 1000)speed_value = 1000;

	if (Accel_value < 1 )Accel_value = 1 ;
	if (Accel_value > 100)Accel_value = 100;
	Accel = Accel_value * 100000;
	Limit_Timer = 1010 - speed_value ;
	C0 = 10000000*sqrt(2*Angle/Accel)*0.676;
	   Step[0] = C0;
	   Cn = C0;
	   n = 0 ;
	   Accel_Edge = 1;
	   for(uint32_t count_i=0; count_i<65535; count_i++)
	   {
	       if(Cn >= Limit_Timer)
	       {
	 	      n++;
		      Cn = Step[n-1]-2*Step[n-1]/(4*n+1);
		      if(Cn >= Limit_Timer)
		         Step[n] = Cn;
	       }
	       if(Cn < Limit_Timer)
	          break;
	       Accel_Edge++;
	       Decel_Edge = Accel_Edge;
	       Check_count = count_i;
	   }



   R2 = (R*R);
   vR = R/(sqrt(2));
   Radius = R;
   Y = 0;
   Pre_X = R;
   Pre_Y = 0;
   //Move_MotorXY(Ox,Oy,speed_value,Accel_value);
   Move_MotorXYZ(Ox, Oy,Current_PosZ,1990,10);
   while(Busy_Flag_XYZ);
   Move_MotorXYZ(Ox+R, Current_PosY,Current_PosZ,speed_value,Accel_value);
 //  Move_MotorX(Ox+R,speed_value,Accel_value);
   while(Busy_Flag_XYZ);

   Busy_Flag_XY = 1;

   Current_PosX = Ox+R;
   Current_PosY = Oy;
   Current_Edge_X = 0;
   Current_Edge_Y = 0;

   HAL_GPIO_WritePin(MotorX_DIR, RESET);
   HAL_GPIO_WritePin(MotorY_DIR, SET);
   status = 1;
   HAL_TIM_Base_Start_IT(&htim16);
   htim16.Init.Period = Circle_Timer;

}

void TIM16_IRQHandler(void)
{
   USER CODE BEGIN TIM16_IRQn 0


	 CHECK EMERGENCY
//	if(!HAL_GPIO_ReadPin(EMG_Button))
//	{

   switch(status)
   {

       case 0:
       {
    	   HAL_TIM_Base_Stop_IT(&htim16);
    	   Busy_Flag_XY = 0;
    	   break;
       }
	   case 1:
	   {
		   Current_Edge_Y++;
		   HAL_GPIO_TogglePin(MotorY_PUL);
		   if(Current_Edge_Y % 2)
		   {
			   Y++;
			   X = sqrt(R2 - Y*Y);

			   if((Pre_X - X) >= 0.5)
			   {
				   HAL_GPIO_WritePin(MotorX_PUL,SET);
				   Pre_X--;
			   }
			   else
			   {
				   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   }
		   }
		   else
		   {
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
		   }

		   if(Y > vR)
		   {
			   Y = (int)vR;
			   X = Y;
			   Pre_X = X;
			   Pre_Y = Y;
			   status = 2;
			   Current_Edge_X = 0;
			   Current_Edge_Y = 0;
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   TIM16->ARR= Circle_Timer;
		   break;

	   }

	   case 2:
	   {
		   Current_Edge_X++;
		   HAL_GPIO_TogglePin(MotorX_PUL);
		   if(Current_Edge_X % 2)
		   {
			   X--;
			   Y = sqrt(R2 - X*X);

			   if((Y - Pre_Y) >= 0.5)
			   {
				   HAL_GPIO_WritePin(MotorY_PUL,SET);
				   Pre_Y++;
			   }
			   else
			   {
				   HAL_GPIO_WritePin(MotorY_PUL,RESET);
			   }
		   }
		   else
		   {
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   if(X == 0)
		   {
			   Y = Radius;
			   X = 0;
			   Pre_X = X;
			   Pre_Y = Y;
			   status = 3;
			   Current_Edge_X = 0;
			   Current_Edge_Y = 0;
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   TIM16->ARR= Circle_Timer;
		   break;

	   }

	   case 3:
	   {
		   HAL_GPIO_WritePin(MotorY_DIR, RESET);
		   Current_Edge_X++;
		   HAL_GPIO_TogglePin(MotorX_PUL);
		   if(Current_Edge_X % 2)
		   {
			   X++;
			   Y = sqrt(R2 - X*X);

			   if((Pre_Y - Y) >= 0.5)
			   {
				   HAL_GPIO_WritePin(MotorY_PUL,SET);
				   Pre_Y--;
			   }
			   else
			   {
				   HAL_GPIO_WritePin(MotorY_PUL,RESET);
			   }
		   }
		   else
		   {
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   if(X > vR)
		   {
			   Y = (int)vR;
			   X = Y;
			   Pre_X = X;
			   Pre_Y = Y;
			   status = 4;
			   Current_Edge_X = 0;
			   Current_Edge_Y = 0;
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   TIM16->ARR= Circle_Timer;
		   break;

	   }

	   case 4:
	   {
		   Current_Edge_Y++;
		   HAL_GPIO_TogglePin(MotorY_PUL);
		   if(Current_Edge_Y % 2)
		   {
			   Y--;
			   X = sqrt(R2 - Y*Y);

			   if((X - Pre_X) >= 0.5)
			   {
				   HAL_GPIO_WritePin(MotorX_PUL,SET);
				   Pre_X++;
			   }
			   else
			   {
				   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   }
		   }
		   else
		   {
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
		   }
		   if(Y == 0)
		   {
			   Y = 0;
			   X = Radius;
			   Pre_X = X;
			   Pre_Y = Y;
			   status = 5;
			   Current_Edge_X = 0;
			   Current_Edge_Y = 0;
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   TIM16->ARR= Circle_Timer;
		   break;

	   }

	   case 5:
	   {
		   HAL_GPIO_WritePin(MotorX_DIR, SET);
		   Current_Edge_Y++;
		   HAL_GPIO_TogglePin(MotorY_PUL);
		   if(Current_Edge_Y % 2)
		   {
			   Y++;
			   X = sqrt(R2 - Y*Y);

			   if((Pre_X - X) >= 0.5)
			   {
				   HAL_GPIO_WritePin(MotorX_PUL,SET);
				   Pre_X--;
			   }
			   else
			   {
				   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   }
		   }

		   else
		   {
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
		   }

		   if(Y > vR)
		   {
			   Y = (int)vR;
			   X = Y;
			   Pre_X = X;
			   Pre_Y = Y;
			   status = 6;
			   Current_Edge_X = 0;
			   Current_Edge_Y = 0;
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   TIM16->ARR= Circle_Timer;
		   break;

	   }

	   case 6:
	   {
		   Current_Edge_X++;
		   HAL_GPIO_TogglePin(MotorX_PUL);
		   if(Current_Edge_X % 2)
		   {
			   X--;
			   Y = sqrt(R2 - X*X);

			   if((Y - Pre_Y) >= 0.5)
			   {
				   HAL_GPIO_WritePin(MotorY_PUL,SET);
				   Pre_Y++;
			   }
			   else
			   {
				   HAL_GPIO_WritePin(MotorY_PUL,RESET);
			   }
		   }
		   else
		   {
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   if(X == 0)
		   {

			   Y = Radius;
			   X = 0;
			   Pre_X = X;
			   Pre_Y = Y;
			   status = 7;
			   Current_Edge_X = 0;
			   Current_Edge_Y = 0;
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);

		   }

		   TIM16->ARR= Circle_Timer;
		   break;

	   }

	   case 7:
	   {
		   HAL_GPIO_WritePin(MotorY_DIR, SET);
		   Current_Edge_X++;
		   HAL_GPIO_TogglePin(MotorX_PUL);
		   if(Current_Edge_X % 2)
		   {
			   X++;
			   Y = sqrt(R2 - X*X);

			   if((Pre_Y - Y) >= 0.5)
			   {
				   HAL_GPIO_WritePin(MotorY_PUL,SET);
				   Pre_Y--;
			   }
			   else
			   {
				   HAL_GPIO_WritePin(MotorY_PUL,RESET);
			   }
		   }

		   else
		   {
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   if(X > vR)
		   {
			   Y = (int)vR;
			   X = Y;
			   Pre_X = X;
			   Pre_Y = Y;
			   status = 8;
			   Current_Edge_X = 0;
			   Current_Edge_Y = 0;
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
		   }

		   TIM16->ARR= Circle_Timer;
		   break;

	   }

	   case 8:
	   {
		   Current_Edge_Y++;
		   HAL_GPIO_TogglePin(MotorY_PUL);
		   if(Current_Edge_Y % 2)
		   {
			   Y--;
			   X = sqrt(R2 - Y*Y);

			   if((X - Pre_X) >= 0.5)
			   {
				   HAL_GPIO_WritePin(MotorX_PUL,SET);
				   Pre_X++;
			   }
			   else
			   {
				   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   }
		   }
		   else
		   {
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
		   }

		   if(Y == 0)
		   {

			   Y = 0;
			   X = Radius;
			   Pre_X = X;
			   Pre_Y = Y;
			   status = 0;
			   Current_Edge_X = 0;
			   Current_Edge_Y = 0;
			   HAL_GPIO_WritePin(MotorX_PUL,RESET);
			   HAL_GPIO_WritePin(MotorY_PUL,RESET);
			//   HAL_TIM_Base_Stop_IT(&htim16);
			  // Busy_Flag_XY = 0;

		   }

		   TIM16->ARR= Circle_Timer;
		   break;

	   }

   }



  USER CODE END TIM16_IRQn 0
 HAL_TIM_IRQHandler(&htim16);
  USER CODE BEGIN TIM16_IRQn 1

  USER CODE END TIM16_IRQn 1
}*/



/*void Move_MotorXYZ(int32_t Pos_X, int32_t Pos_Y,int32_t Pos_Z,float speed_value,float Accel_value)
{

	Set_Edge_XYZ=0;
	Current_Edge_XYZ=0;
	XYZ_index=0;
	Set_Edge_X=0;
	Current_Edge_X=0;
	Busy_Flag_XYZ = 0;
	Set_Edge_Y=0;
	Current_Edge_Y=0;
	Set_Edge_Z=0;
	Current_Edge_Z=0;
	flag_stop_xyz = 0;

	XYZ_index=0;
	dx = abs(Pos_X- Current_PosX);
	dy = abs(Pos_Y - Current_PosY);
	dz = abs(Pos_Z - Current_PosZ);
	Set_Edge_X = 2 * dx;
	Set_Edge_Y = 2 * dy;
	Set_Edge_Z = 2 * dz;
	if ( dx >= dy && dx >= dz ) //DX Max
	{
		Set_Edge_XYZ = Set_Edge_X;
		process_move = 1;
		P1_value = 2*dy -dx;
		P2_value = 2*dz -dx;		
	}
	else if ( dy >= dx && dy >= dz )//DY Max
	{
		Set_Edge_XYZ = Set_Edge_Y;
		process_move = 2;
		P1_value = 2*dx - dy;
		P2_value = 2*dz - dy;
	}
	else if ( dz >= dx && dz >= dx ) //DZ Max
	{
		Set_Edge_XYZ = Set_Edge_Z;
		process_move = 3;
		P1_value = 2*dy - dz;
		P2_value = 2*dx - dz;
	}
	

	if (Pos_X > Current_PosX)
	{
		HAL_GPIO_WritePin(MotorX_DIR, RESET);		
	}
	else
	{
		HAL_GPIO_WritePin(MotorX_DIR, SET);	
	}
	
	if (Pos_Y > Current_PosY)
	{
		HAL_GPIO_WritePin(MotorY_DIR, RESET);		
	}
	else
	{
		HAL_GPIO_WritePin(MotorY_DIR, SET);	
	}
	
	if (Pos_Z > Current_PosZ)
	{
		HAL_GPIO_WritePin(MotorZ_DIR, SET);
	}
	else
	{
		HAL_GPIO_WritePin(MotorZ_DIR, RESET);
	}

	Busy_Flag_XYZ = 1;
	Current_PosX = Pos_X;
	Current_PosY = Pos_Y;
	Current_PosZ = Pos_Z;
	
	if (speed_value < 3 )speed_value = 3 ;
	if (speed_value > 2000)speed_value = 2000;

	if (Accel_value < 1 )Accel_value = 1 ;
	if (Accel_value > 100)Accel_value = 100;
	Accel = Accel_value * 100000;
	Limit_Timer = 2004 - speed_value ;// khac123
	C0 = 10000000*sqrt(2*Angle/Accel)*0.676;
//	if (C0 < Limit_Timer)C0 = Limit_Timer;
	   Step[0] = C0;
	   Cn = C0;
	   n = 0 ;
	   Accel_Edge = 1;
	   for(uint32_t count_i=0; count_i<65536; count_i++)
	   {
	       if(Cn >= Limit_Timer)
	       {
	 	      n++;
		      //Cn = (Step[n-1]-2*Step[n-1]/(4*n+1));
	 	     Cn = Cn-2*Cn/(4*n+1);
		      if(Cn >= Limit_Timer)
		         Step[n] = Cn;
		      Check_n = n;
	       }
	       if(Cn < Limit_Timer)
	          break;
	       Accel_Edge++;
	       Decel_Edge = Accel_Edge;
	       Check_count = count_i;
	   }
	   check_Cn = Cn;

	check_pos_x =0;
	check_pos_y=0;
	check_pos_z =0;
	flag_check_syn = 1;
   htim17.Init.Period = Step[0];
   HAL_TIM_Base_Start_IT(&htim17);
	
}*/


void Move_XYZ_ABC(int32_t Pos_X, int32_t Pos_Y,int32_t Pos_Z,int32_t Pos_A, int32_t Pos_B,int32_t Pos_C,float speed_value,float Accel_value)
{
	Set_Edge_XYZ=0;
	Current_Edge_XYZ=0;
	XYZ_index=0;

	Set_Edge_X=0;
	Current_Edge_X=0;
	Busy_Flag_XYZ = 0;
	Set_Edge_Y=0;
	Current_Edge_Y=0;
	Set_Edge_Z=0;
	Current_Edge_Z=0;
	Set_Edge_A=0;
	Current_Edge_A=0;
	Set_Edge_B=0;
	Current_Edge_B=0;
	Set_Edge_C=0;
	Current_Edge_C=0;
	flag_stop_xyz = 0;

	XYZ_index=0;
	denta[0] = abs(Pos_X - Current_PosX);
	denta[1] = abs(Pos_Y - Current_PosY);
	denta[2] = abs(Pos_Z - Current_PosZ);
	denta[3] = abs(Pos_A - Current_PosA);
	denta[4] = abs(Pos_B - Current_PosB);
	denta[5] = abs(Pos_C - Current_PosC);
	Set_Edge_X = 2 * denta[0];
	Set_Edge_Y = 2 * denta[1];
	Set_Edge_Z = 2 * denta[2];
	Set_Edge_A = 2 * denta[3];
	Set_Edge_B = 2 * denta[4];
	Set_Edge_C = 2 * denta[5];
	d_max = denta[0];
	for (int i =0;i<6;i++)
	{
		if(denta[i] >= d_max)
		{
			d_max = denta[i] ;
		}
	}

	if (d_max == denta[0])//DX Max
	{
		Set_Edge_XYZ = Set_Edge_X;
		process_move = 1;

//		P_value[0] = 2*denta[1]- denta[0];
//		P_value[1] = 2*denta[2]- denta[0];
//		P_value[2] = 2*denta[3]- denta[0];
//		P_value[3] = 2*denta[4]- denta[0];
//		P_value[4] = 2*denta[5]- denta[0];

		for (int i =0;i<6;i++)
		{
			P_value[i] = 2*denta[i+1]- denta[0];
		}
	}

	else if (d_max == denta[1])//DY Max
	{
		Set_Edge_XYZ = Set_Edge_Y;
		process_move = 2;

		P_value[0] = 2*denta[0]- denta[1];
		P_value[1] = 2*denta[2]- denta[1];
		P_value[2] = 2*denta[3]- denta[1];
		P_value[3] = 2*denta[4]- denta[1];
		P_value[4] = 2*denta[5]- denta[1];
	}


	else if (d_max == denta[2])//DZ Max
	{
		Set_Edge_XYZ = Set_Edge_Z;
		process_move = 3;

		P_value[0] = 2*denta[0]- denta[2];
		P_value[1] = 2*denta[1]- denta[2];
		P_value[2] = 2*denta[3]- denta[2];
		P_value[3] = 2*denta[4]- denta[2];
		P_value[4] = 2*denta[5]- denta[2];
	}

	else if (d_max == denta[3])//DA Max
	{
		Set_Edge_XYZ = Set_Edge_A;
		process_move = 4;

		P_value[0] = 2*denta[0]- denta[3];
		P_value[1] = 2*denta[1]- denta[3];
		P_value[2] = 2*denta[2]- denta[3];
		P_value[3] = 2*denta[4]- denta[3];
		P_value[4] = 2*denta[5]- denta[3];
	}

	else if (d_max == denta[4])//DB Max
	{
		Set_Edge_XYZ = Set_Edge_B;
		process_move = 5;

		P_value[0] = 2*denta[0]- denta[4];
		P_value[1] = 2*denta[1]- denta[4];
		P_value[2] = 2*denta[2]- denta[4];
		P_value[3] = 2*denta[3]- denta[4];
		P_value[4] = 2*denta[5]- denta[4];
	}

	else if (d_max == denta[5])//DC Max
	{
		Set_Edge_XYZ = Set_Edge_C;
		process_move = 6;

		P_value[0] = 2*denta[0]- denta[5];
		P_value[1] = 2*denta[1]- denta[5];
		P_value[2] = 2*denta[2]- denta[5];
		P_value[3] = 2*denta[3]- denta[5];
		P_value[4] = 2*denta[4]- denta[5];
	}



	if (Pos_X > Current_PosX)
	{
		HAL_GPIO_WritePin(MotorX_DIR, RESET);
	}
	else
	{
		HAL_GPIO_WritePin(MotorX_DIR, SET);
	}

	if (Pos_Y > Current_PosY)
	{
		HAL_GPIO_WritePin(MotorY_DIR, RESET);
	}
	else
	{
		HAL_GPIO_WritePin(MotorY_DIR, SET);
	}

	if (Pos_Z > Current_PosZ)
	{
		HAL_GPIO_WritePin(MotorZ_DIR, SET);
	}
	else
	{
		HAL_GPIO_WritePin(MotorZ_DIR, RESET);
	}

	if (Pos_A > Current_PosA)
	{
		HAL_GPIO_WritePin(MotorA_DIR, SET);
	}
	else
	{
		HAL_GPIO_WritePin(MotorA_DIR, RESET);
	}

	if (Pos_B > Current_PosB)
	{
		HAL_GPIO_WritePin(MotorB_DIR, SET);
	}
	else
	{
		HAL_GPIO_WritePin(MotorB_DIR, RESET);
	}


	if (Pos_C > Current_PosC)
	{
		HAL_GPIO_WritePin(MotorC_DIR, SET);
	}
	else
	{
		HAL_GPIO_WritePin(MotorC_DIR, RESET);
	}




	Busy_Flag_XYZ = 1;
	Current_PosX = Pos_X;
	Current_PosY = Pos_Y;
	Current_PosZ = Pos_Z;
	Current_PosA = Pos_A;
	Current_PosB = Pos_B;
	Current_PosC = Pos_C;

	if (speed_value < 3 )speed_value = 3 ;
	if (speed_value > 2000)speed_value = 2000;

	if (Accel_value < 1 )Accel_value = 1 ;
	if (Accel_value > 100)Accel_value = 100;
	Accel = Accel_value * 100000;
	Limit_Timer = 2004 - speed_value ;// khac123
	C0 = 10000000*sqrt(2*Angle/Accel)*0.676;
//	if (C0 < Limit_Timer)C0 = Limit_Timer;
	   Step[0] = C0;
	   Cn = C0;
	   n = 0 ;
	   Accel_Edge = 1;
	   for(uint32_t count_i=0; count_i<65536; count_i++)
	   {
	       if(Cn >= Limit_Timer)
	       {
	 	      n++;
		      //Cn = (Step[n-1]-2*Step[n-1]/(4*n+1));
	 	     Cn = Cn-2*Cn/(4*n+1);
		      if(Cn >= Limit_Timer)
		         Step[n] = Cn;
		      Check_n = n;
	       }
	       if(Cn < Limit_Timer)
	          break;
	       Accel_Edge++;
	       Decel_Edge = Accel_Edge;
	       Check_count = count_i;
	   }
	   check_Cn = Cn;

	check_pos_x =0;
	check_pos_y=0;
	check_pos_z =0;
	check_pos_a =0;
	check_pos_b=0;
	check_pos_c =0;
	flag_check_syn = 2	;
   htim4.Init.Period = Step[0];
   HAL_TIM_Base_Start_IT(&htim4);


}
void TIM4_IRQHandler(void)
{
	if (flag_check_syn == 1)
	{
		if(Set_Edge_XYZ >= (2*Accel_Edge))
			{
				if(Current_Edge_XYZ <= Accel_Edge )
				{
					if(XYZ_index < (Accel_Edge-1))
					{
					   XYZ_index++;
					}
					TIM4->ARR=Step[XYZ_index];
				}
				else if(Current_Edge_XYZ > Accel_Edge && Current_Edge_XYZ < (Set_Edge_XYZ - Decel_Edge))
				{
					TIM4->ARR=Step[Accel_Edge-1];
				}

				else
				{
					TIM4->ARR=Step[XYZ_index];
						XYZ_index--;
				}

			}

		else
		{
			if(2*Current_Edge_XYZ < (Set_Edge_XYZ - 1))
			{
				XYZ_index++;
				TIM4->ARR=Step[XYZ_index];
			}
			else if(2*Current_Edge_XYZ > (Set_Edge_XYZ - 1))
			{
				TIM4->ARR=Step[XYZ_index];
				XYZ_index--;
			}
		}


		switch(process_move)
		{
			case 1: //DX MAX
			{
				if(Current_Edge_X == Set_Edge_X)
				{
					flag_stop_xyz = 1;
				}
				else
				{
					Current_Edge_XYZ =Current_Edge_X;
					Current_Edge_X++;
					HAL_GPIO_TogglePin(MotorX_PUL);
					check_pos_x++;
					if (P1_value >= 0)
					{
						HAL_GPIO_TogglePin(MotorY_PUL);
						P1_value = P1_value - 2*dx;
						check_pos_y++;
					}

					if (P2_value >= 0)
					{
						HAL_GPIO_TogglePin(MotorZ_PUL);
						check_pos_z++;
						P2_value = P2_value - 2*dx;
					}
					P1_value = P1_value + 2*dy;
					P2_value = P2_value + 2*dz;
					HAL_TIM_IRQHandler(&htim4);

				}
				break;
			}

			case 2: // DY MAX
			{
				if(Current_Edge_Y == Set_Edge_Y)
				{
					flag_stop_xyz = 1;
				}
				else
				{
					Current_Edge_XYZ =Current_Edge_Y;
					Current_Edge_Y++;
					HAL_GPIO_TogglePin(MotorY_PUL);
					check_pos_y++;
					if (P1_value >= 0)
					{
						HAL_GPIO_TogglePin(MotorX_PUL);
						P1_value = P1_value - 2*dy;
						check_pos_x++;
					}

					if (P2_value >= 0)
					{
						HAL_GPIO_TogglePin(MotorZ_PUL);
						P2_value = P2_value - 2*dy;
						check_pos_z++;
					}
					P1_value = P1_value + 2*dx;
					P2_value = P2_value + 2*dz;
					HAL_TIM_IRQHandler(&htim4);
				}
				break;
			}

			case 3: // DZ MAX
			{
				if(Current_Edge_Z == Set_Edge_Z)
				{
					flag_stop_xyz = 1;
				}
				else
				{
					Current_Edge_XYZ =Current_Edge_Z;
					Current_Edge_Z++;
					HAL_GPIO_TogglePin(MotorZ_PUL);
					check_pos_z++;
					if (P1_value >= 0)
					{
						HAL_GPIO_TogglePin(MotorY_PUL);
						P1_value = P1_value - 2*dz;
						check_pos_y++;
					}

					if (P2_value >= 0)
					{
						HAL_GPIO_TogglePin(MotorX_PUL);
						P2_value = P2_value - 2*dz;
						check_pos_x++;
					}
					P1_value = P1_value + 2*dy;
					P2_value = P2_value + 2*dx;
					HAL_TIM_IRQHandler(&htim4);
				}
				break;

			}
			default :
				HAL_TIM_Base_Stop_IT(&htim4);
				Busy_Flag_XYZ = 0;
				break;
		}

		if (flag_stop_xyz)
		{
			Set_Edge_XYZ=0;
			Current_Edge_XYZ=0;
			XYZ_index=0;
			Set_Edge_X=0;
			Current_Edge_X=0;
			Busy_Flag_XYZ = 0;
			Set_Edge_Y=0;
			Current_Edge_Y=0;
			Set_Edge_Z=0;
			Current_Edge_Z=0;
			flag_stop_xyz = 0;
			cur_pos_x = check_pos_x /2;
			cur_pos_y = check_pos_y /2;
			cur_pos_z = check_pos_z /2;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}



	// For syn 6 Axis
	if (flag_check_syn == 2)
	{
		if(Set_Edge_XYZ >= (2*Accel_Edge))
			{
				if(Current_Edge_XYZ <= Accel_Edge )
				{
					if(XYZ_index < (Accel_Edge-1))
					{
					   XYZ_index++;
					}
					TIM4->ARR=Step[XYZ_index];
				}
				else if(Current_Edge_XYZ > Accel_Edge && Current_Edge_XYZ < (Set_Edge_XYZ - Decel_Edge))
				{
					TIM4->ARR=Step[Accel_Edge-1];
				}

				else
				{
					TIM4->ARR=Step[XYZ_index];
						XYZ_index--;
				}

			}

		else
		{
			if(2*Current_Edge_XYZ < (Set_Edge_XYZ - 1))
			{
				XYZ_index++;
				TIM4->ARR=Step[XYZ_index];
			}
			else if(2*Current_Edge_XYZ > (Set_Edge_XYZ - 1))
			{
				TIM4->ARR=Step[XYZ_index];
				XYZ_index--;
			}
		}


		switch(process_move)  // ddd
		{
			case 1: //DX MAX
			{
				if(Current_Edge_X == Set_Edge_X)
				{
					flag_stop_xyz = 1;
				}
				else
				{
					Current_Edge_XYZ =Current_Edge_X;
					Current_Edge_X++;
					HAL_GPIO_TogglePin(MotorX_PUL);
					check_pos_x++;
					if (P_value[0] >= 0)
					{
						HAL_GPIO_TogglePin(MotorY_PUL);
						P_value[0] = P_value[0] - 2*denta[0];
						check_pos_y++;
					}

					if (P_value[1] >= 0)
					{
						HAL_GPIO_TogglePin(MotorZ_PUL);
						P_value[1] = P_value[1] - 2*denta[0];
						check_pos_z++;
					}

					if (P_value[2] >= 0)
					{
						HAL_GPIO_TogglePin(MotorA_PUL);
						P_value[2] = P_value[2] - 2*denta[0];
						check_pos_a++;
					}

					if (P_value[3] >= 0)
					{
						HAL_GPIO_TogglePin(MotorB_PUL);
						P_value[3] = P_value[3] - 2*denta[0];
						check_pos_b++;
					}

					if (P_value[4] >= 0)
					{
						HAL_GPIO_TogglePin(MotorC_PUL);
						P_value[4] = P_value[4] - 2*denta[0];
						check_pos_c++;
					}


					P_value[0] = P_value[0] + 2*denta[1];
					P_value[1] = P_value[1] + 2*denta[2];
					P_value[2] = P_value[2] + 2*denta[3];
					P_value[3] = P_value[3] + 2*denta[4];
					P_value[4] = P_value[4] + 2*denta[5];
					HAL_TIM_IRQHandler(&htim4);
				}
				break;
			}

			case 2: // DY MAX
			{
				if(Current_Edge_Y == Set_Edge_Y)
				{
					flag_stop_xyz = 1;
				}
				else
				{
					Current_Edge_XYZ =Current_Edge_Y;
						Current_Edge_Y++;
						HAL_GPIO_TogglePin(MotorY_PUL);
						check_pos_y++;
						if (P_value[0] >= 0)
						{
							HAL_GPIO_TogglePin(MotorX_PUL);
							P_value[0] = P_value[0] - 2*denta[1];
							check_pos_x++;
						}

						if (P_value[1] >= 0)
						{
							HAL_GPIO_TogglePin(MotorZ_PUL);
							P_value[1] = P_value[1] - 2*denta[1];
							check_pos_z++;
						}

						if (P_value[2] >= 0)
						{
							HAL_GPIO_TogglePin(MotorA_PUL);
							P_value[2] = P_value[2] - 2*denta[1];
							check_pos_a++;
						}

						if (P_value[3] >= 0)
						{
							HAL_GPIO_TogglePin(MotorB_PUL);
							P_value[3] = P_value[3] - 2*denta[1];
							check_pos_b++;
						}

						if (P_value[4] >= 0)
						{
							HAL_GPIO_TogglePin(MotorC_PUL);
							P_value[4] = P_value[4] - 2*denta[1];
							check_pos_c++;
						}


						P_value[0] = P_value[0] + 2*denta[0];
						P_value[1] = P_value[1] + 2*denta[2];
						P_value[2] = P_value[2] + 2*denta[3];
						P_value[3] = P_value[3] + 2*denta[4];
						P_value[4] = P_value[4] + 2*denta[5];
						HAL_TIM_IRQHandler(&htim4);


				}
				break;
			}

			case 3: // DZ MAX
			{
				if(Current_Edge_Z == Set_Edge_Z)
				{
					flag_stop_xyz = 1;
				}
				else
				{

						Current_Edge_XYZ =Current_Edge_Z;
						Current_Edge_Z++;
						HAL_GPIO_TogglePin(MotorZ_PUL);
						check_pos_z++;
						if (P_value[0] >= 0)
						{
							HAL_GPIO_TogglePin(MotorX_PUL);
							P_value[0] = P_value[0] - 2*denta[2];
							check_pos_x++;
						}

						if (P_value[1] >= 0)
						{
							HAL_GPIO_TogglePin(MotorY_PUL);
							P_value[1] = P_value[1] - 2*denta[2];
							check_pos_y++;
						}

						if (P_value[2] >= 0)
						{
							HAL_GPIO_TogglePin(MotorA_PUL);
							P_value[2] = P_value[2] - 2*denta[2];
							check_pos_a++;
						}

						if (P_value[3] >= 0)
						{
							HAL_GPIO_TogglePin(MotorB_PUL);
							P_value[3] = P_value[3] - 2*denta[2];
							check_pos_b++;
						}

						if (P_value[4] >= 0)
						{
							HAL_GPIO_TogglePin(MotorC_PUL);
							P_value[4] = P_value[4] - 2*denta[2];
							check_pos_c++;
						}


						P_value[0] = P_value[0] + 2*denta[0];
						P_value[1] = P_value[1] + 2*denta[1];
						P_value[2] = P_value[2] + 2*denta[3];
						P_value[3] = P_value[3] + 2*denta[4];
						P_value[4] = P_value[4] + 2*denta[5];
						HAL_TIM_IRQHandler(&htim4);
				}
				break;

			}

			case 4: // DA MAX
			{
				if(Current_Edge_A == Set_Edge_A)
				{
					flag_stop_xyz = 1;
				}
				else
				{

						Current_Edge_XYZ =Current_Edge_A;
						Current_Edge_A++;
						HAL_GPIO_TogglePin(MotorA_PUL);
						check_pos_a++;
						if (P_value[0] >= 0)
						{
							HAL_GPIO_TogglePin(MotorX_PUL);
							P_value[0] = P_value[0] - 2*denta[3];
							check_pos_x++;
						}

						if (P_value[1] >= 0)
						{
							HAL_GPIO_TogglePin(MotorY_PUL);
							P_value[1] = P_value[1] - 2*denta[3];
							check_pos_y++;
						}

						if (P_value[2] >= 0)
						{
							HAL_GPIO_TogglePin(MotorZ_PUL);
							P_value[2] = P_value[2] - 2*denta[3];
							check_pos_z++;
						}

						if (P_value[3] >= 0)
						{
							HAL_GPIO_TogglePin(MotorB_PUL);
							P_value[3] = P_value[3] - 2*denta[3];
							check_pos_b++;
						}

						if (P_value[4] >= 0)
						{
							HAL_GPIO_TogglePin(MotorC_PUL);
							P_value[4] = P_value[4] - 2*denta[3];
							check_pos_c++;
						}


						P_value[0] = P_value[0] + 2*denta[0];
						P_value[1] = P_value[1] + 2*denta[1];
						P_value[2] = P_value[2] + 2*denta[2];
						P_value[3] = P_value[3] + 2*denta[4];
						P_value[4] = P_value[4] + 2*denta[5];
						HAL_TIM_IRQHandler(&htim4);
				}
				break;

			}


			case 5: // DB MAX
			{
				if(Current_Edge_B == Set_Edge_B)
				{
					flag_stop_xyz = 1;
				}
				else
				{

						Current_Edge_XYZ =Current_Edge_B;
						Current_Edge_B++;
						HAL_GPIO_TogglePin(MotorB_PUL);
						check_pos_b++;
						if (P_value[0] >= 0)
						{
							HAL_GPIO_TogglePin(MotorX_PUL);
							P_value[0] = P_value[0] - 2*denta[4];
							check_pos_x++;
						}

						if (P_value[1] >= 0)
						{
							HAL_GPIO_TogglePin(MotorY_PUL);
							P_value[1] = P_value[1] - 2*denta[4];
							check_pos_y++;
						}

						if (P_value[2] >= 0)
						{
							HAL_GPIO_TogglePin(MotorZ_PUL);
							P_value[2] = P_value[2] - 2*denta[4];
							check_pos_z++;
						}

						if (P_value[3] >= 0)
						{
							HAL_GPIO_TogglePin(MotorA_PUL);
							P_value[3] = P_value[3] - 2*denta[4];
							check_pos_a++;
						}

						if (P_value[4] >= 0)
						{
							HAL_GPIO_TogglePin(MotorC_PUL);
							P_value[4] = P_value[4] - 2*denta[4];
							check_pos_c++;
						}

						P_value[0] = P_value[0] + 2*denta[0];
						P_value[1] = P_value[1] + 2*denta[1];
						P_value[2] = P_value[2] + 2*denta[2];
						P_value[3] = P_value[3] + 2*denta[3];
						P_value[4] = P_value[4] + 2*denta[5];
						HAL_TIM_IRQHandler(&htim4);
				}
				break;

			}
			case 6: // DC MAX
			{
				if(Current_Edge_C == Set_Edge_C)
				{
					flag_stop_xyz = 1;
				}
				else
				{

						Current_Edge_XYZ =Current_Edge_C;
						Current_Edge_C++;
						HAL_GPIO_TogglePin(MotorC_PUL);
						check_pos_c++;
						if (P_value[0] >= 0)
						{
							HAL_GPIO_TogglePin(MotorX_PUL);
							P_value[0] = P_value[0] - 2*denta[5];
							check_pos_x++;
						}

						if (P_value[1] >= 0)
						{
							HAL_GPIO_TogglePin(MotorY_PUL);
							P_value[1] = P_value[1] - 2*denta[5];
							check_pos_y++;
						}

						if (P_value[2] >= 0)
						{
							HAL_GPIO_TogglePin(MotorZ_PUL);
							P_value[2] = P_value[2] - 2*denta[5];
							check_pos_z++;
						}

						if (P_value[3] >= 0)
						{
							HAL_GPIO_TogglePin(MotorA_PUL);
							P_value[3] = P_value[3] - 2*denta[5];
							check_pos_a++;
						}

						if (P_value[4] >= 0)
						{
							HAL_GPIO_TogglePin(MotorB_PUL);
							P_value[4] = P_value[4] - 2*denta[5];
							check_pos_b++;
						}

						P_value[0] = P_value[0] + 2*denta[0];
						P_value[1] = P_value[1] + 2*denta[1];
						P_value[2] = P_value[2] + 2*denta[2];
						P_value[3] = P_value[3] + 2*denta[3];
						P_value[4] = P_value[4] + 2*denta[4];
						HAL_TIM_IRQHandler(&htim4);
				}
				break;

			}

			default :
				HAL_TIM_Base_Stop_IT(&htim4);
				Busy_Flag_XYZ = 0;
				break;
		}

		if (flag_stop_xyz)
		{
			Set_Edge_XYZ=0;
			Current_Edge_XYZ=0;
			XYZ_index=0;
			Set_Edge_X=0;
			Current_Edge_X=0;
			Busy_Flag_XYZ = 0;
			Set_Edge_Y=0;
			Current_Edge_Y=0;
			Set_Edge_Z=0;
			Current_Edge_Z=0;
			flag_stop_xyz = 0;
			cur_pos_x = check_pos_x /2;
			cur_pos_y = check_pos_y /2;
			cur_pos_z = check_pos_z /2;
			cur_pos_a = check_pos_a /2;
			cur_pos_b = check_pos_b /2;
			cur_pos_c = check_pos_c /2;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
		
		

	}
	

}

void Origin_Motor_A()
{
	if (HAL_GPIO_ReadPin(SensorA)== 1)
	{
		process_origin_A = 4 ;
	}
	else
	{
		process_origin_A = 0 ;
	}
	process_origin_B = 0 ;
	Busy_Flag_Origin_A = 1;
	Busy_Flag_Origin_B = 1;
	Busy_Flag_Origin_AB = 1;
	htim15.Init.Period = 400;
	HAL_TIM_Base_Start_IT(&htim15);



}
void TIM15_IRQHandler(void)
{
	TIM15->ARR=400;
	switch (process_origin_A)
	{
	case 0:
		HAL_GPIO_WritePin(MotorA_DIR, RESET); // nguoc chieu kim dong ho
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (HAL_GPIO_ReadPin(SensorA)== 1)//Neu Detect
		{
			Current_PosA = 0 ;
			process_origin_A = 1;
		}
		else if (Current_PosA == 4000)
		{
			Current_PosA = 0 ;
			process_origin_A = 2;
		}
		break;
	case 1:
		HAL_GPIO_WritePin(MotorA_DIR, RESET); // nguoc chieu kim dong ho
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (Current_PosA == 600)
		{
			process_origin_A = 100;
		}
		break;
	case 2:
		HAL_GPIO_WritePin(MotorA_DIR, SET);
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (HAL_GPIO_ReadPin(SensorA)== 1) // Neu Detect
		{
			Current_PosA = 0 ;
			process_origin_A = 4;
		}
		else if (Current_PosA == 6000)
		{
			Current_PosA = 0 ;
			process_origin_A = 101;
		}
		break;
	case 4:
		HAL_GPIO_WritePin(MotorA_DIR, SET); //chieu kim dong ho
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (Current_PosA == 3000)
		{
			process_origin_A = 0;
			Current_PosA  = 0 ;
		}
		break;
	case 10:
		HAL_GPIO_WritePin(MotorA_DIR, SET);
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (HAL_GPIO_ReadPin(SensorA)== 0)
		{
			Current_PosA = 0 ;
			process_origin_A = 0;
			HAL_GPIO_WritePin(MotorA_DIR, RESET);
		}
		else if (Current_PosA == 4000)
		{
			Current_PosA = 0 ;
			process_origin_A = 100;
		}
		break;
	case 100:
		HAL_GPIO_WritePin(LED_EMG, RESET);
		process_origin_A = 200 ;
		Current_PosA = 0 ;
		Busy_Flag_Origin_A =  0;
		break;
	case 101: //ERROR
		HAL_GPIO_WritePin(LED_EMG, SET);
		process_origin_A = 200 ;
		Current_PosA = 0 ;
		Busy_Flag_Origin_A =  0;
		break;
	case 200:
		process_origin_A = 200 ;
		break;

	}

	switch (process_origin_B)
	{
		case 0:
			if (HAL_GPIO_ReadPin(SensorB)== 0) // Neu chua detect
			{
				process_origin_B = 1;
				HAL_GPIO_WritePin(MotorB_DIR, RESET);
			}
			else // Neu dang Detect
			{
				HAL_GPIO_WritePin(MotorB_DIR, SET);
				Current_PosB = 0 ;
				process_origin_B = 2;
			}

			break;
		case 1:
			HAL_GPIO_TogglePin(MotorB_PUL);
			Current_PosB ++ ;
			if (HAL_GPIO_ReadPin(SensorB)== 1) // Neu detect
			{
				process_origin_B = 10;
				Current_PosB = 0 ;
			}
			break;
		case 2:
			HAL_GPIO_TogglePin(MotorB_PUL);
			Current_PosB ++ ;
			if (Current_PosB == 1000) // Neu chua detect
			{
				process_origin_B = 0;
				Current_PosB  = 0;
			}
			break;
		case 10:
			HAL_GPIO_TogglePin(MotorB_PUL);
			Current_PosB ++ ;
			if (Current_PosB == 1760)
			{
				process_origin_B = 200;
				Busy_Flag_Origin_B = 0 ;
				Current_PosB = 0 ;
			}
			break;
		case 200:
			process_origin_B = 200;
			break;

	}
	if ( Busy_Flag_Origin_A == 0 && Busy_Flag_Origin_B == 0)
	{
	 //	HAL_GPIO_WritePin(LED_EMG, RESET);
		process_origin_A = 0 ;
		process_origin_B = 0 ;
		Current_PosA = 0 ;
		Current_PosB = 0 ;
		Current_PosC = 0 ;
		Busy_Flag_Origin_A =  0;
		Busy_Flag_Origin_B =  0;
		Busy_Flag_Origin_AB =  0;
		HAL_TIM_Base_Stop_IT(&htim15);
	}


	HAL_TIM_IRQHandler(&htim15);
}
/*void Move_MotorA(int32_t PosA,float speed_value,float Accel_value)
{
	if(PosA == Current_PosA)
		{

		}
		else
		{
		    if (speed_value < 1 )speed_value = 1 ;
		    	if (speed_value > 1000)speed_value = 1000;

		    	if (Accel_value < 1 )Accel_value = 1 ;
		    	if (Accel_value > 100)Accel_value = 100;
		    	Accel = Accel_value * 100000;
		    	Limit_Timer = 1007 - speed_value ;// 14-12-2020 : 110
		    	C0 = 10000000*sqrt(2*Angle/Accel)*0.676;
		    	   Step[0] = C0;
		    	   Cn = C0;
		    	   n = 0 ;
		    	   Accel_Edge = 1;
		    	   for(uint32_t count_i=0; count_i<65535; count_i++)
		    	   {
		    	       if(Cn >= Limit_Timer)
		    	       {
		    	 	      n++;
		    		      Cn = Step[n-1]-2*Step[n-1]/(4*n+1);
		    		      if(Cn >= Limit_Timer)
		    		         Step[n] = Cn;
		    	       }
		    	       if(Cn < Limit_Timer)
		    	          break;
		    	       Accel_Edge++;
		    	       Decel_Edge = Accel_Edge;
		    	       Check_count = count_i;
		    	   }
		}

	    if((PosA - Current_PosA) > 0)
	    {
	    	Busy_Flag_A = 1;
	    	Set_Edge_A = 2*(PosA - Current_PosA);
	    	HAL_GPIO_WritePin(MotorA_DIR, RESET);
	    	HAL_TIM_Base_Start_IT(&htim3);
	    	htim3.Init.Period = Step[0];
	    }
	    else if((PosA - Current_PosA) < 0)
	    {

	    	Busy_Flag_A = 1;
	    	Set_Edge_A = 2*(Current_PosA - PosA);
	    	HAL_GPIO_WritePin(MotorA_DIR, SET);
	    	HAL_TIM_Base_Start_IT(&htim3);
	    	htim3.Init.Period = Step[0];
	    }
	    else
	    {
	    	HAL_TIM_Base_Stop_IT(&htim3);
	    }
	    Current_PosA=PosA;


}


void TIM3_IRQHandler(void)
{

		if(Set_Edge_A >= (2*Accel_Edge))
		{
			if(Current_Edge_A <= Accel_Edge )
			{
				if(A_index < (Accel_Edge-1))
				{
				   A_index++;
				}
				Current_Edge_A++;
				TIM3->ARR=Step[A_index];
				HAL_GPIO_TogglePin(MotorA_PUL);
			}

			else if(Current_Edge_A > Accel_Edge && Current_Edge_A < (Set_Edge_A - Decel_Edge))
			{
				Current_Edge_A++;
				TIM3->ARR=Step[Accel_Edge-1];
				HAL_GPIO_TogglePin(MotorA_PUL);
			}

			else
			{
				Current_Edge_A++;
				TIM3->ARR=Step[A_index];
				HAL_GPIO_TogglePin(MotorA_PUL);
				if(Current_Edge_A == Set_Edge_A)
				{

					Set_Edge_A =0;
					Current_Edge_A=0;
					A_index=0;
					Busy_Flag_A = 0;
					HAL_TIM_Base_Stop_IT(&htim3);
				}

				else
					A_index--;
			}

		}

		else
		{
			if(2*Current_Edge_A < (Set_Edge_A - 1))
			{
			   Current_Edge_A++;
			   A_index++;
			   TIM3->ARR=Step[A_index];
			   HAL_GPIO_TogglePin(MotorA_PUL);
			}
			else if(2*Current_Edge_A > (Set_Edge_A - 1))
			{
				Current_Edge_A++;
				TIM3->ARR=Step[A_index];
				A_index--;
				HAL_GPIO_TogglePin(MotorA_PUL);

				if(Current_Edge_A == Set_Edge_A)
				{
					Set_Edge_A=0;
					Current_Edge_A=0;
					A_index=0;
					Busy_Flag_A = 0;
					HAL_TIM_Base_Stop_IT(&htim3);
				}
			}
		}



   USER CODE BEGIN TIM3_IRQn 0

   USER CODE END TIM3_IRQn 0
  HAL_TIM_IRQHandler(&htim3);
   USER CODE BEGIN TIM3_IRQn 1

   USER CODE END TIM3_IRQn 1
}



void Move_MotorB(int32_t PosB,float speed_value,float Accel_value)
{
	if (PosB == Current_PosB)
	{

	}
	else
	{
		if (speed_value < 1 )speed_value = 1 ;
		if (speed_value > 1000)speed_value = 1000;

		if (Accel_value < 1 )Accel_value = 1 ;
		if (Accel_value > 100)Accel_value = 100;
		Accel = Accel_value * 100000;
		Limit_Timer = 1007 - speed_value ;// 14-12-2020 : 110
		C0 = 10000000*sqrt(2*Angle/Accel)*0.676;
		   Step[0] = C0;
		   Cn = C0;
		   n = 0 ;
		   Accel_Edge = 1;
		   for(uint32_t count_i=0; count_i<65535; count_i++)
		   {
		       if(Cn >= Limit_Timer)
		       {
		 	      n++;
			      Cn = Step[n-1]-2*Step[n-1]/(4*n+1);
			      if(Cn >= Limit_Timer)
			         Step[n] = Cn;
		       }
		       if(Cn < Limit_Timer)
		          break;
		       Accel_Edge++;
		       Decel_Edge = Accel_Edge;
		       Check_count = count_i;
		   }
	}


    if((PosB - Current_PosB) > 0)
    {
    	Busy_Flag_B = 1;
    	Set_Edge_B = 2*(PosB - Current_PosB);
    	HAL_GPIO_WritePin(MotorB_DIR, RESET);
    	HAL_TIM_Base_Start_IT(&htim4);
    	htim4.Init.Period = Step[0];
    }
    else if((PosB - Current_PosB) < 0)
    {

    	Busy_Flag_B = 1;
    	Set_Edge_B = 2*(Current_PosB - PosB);
    	HAL_GPIO_WritePin(MotorB_DIR, SET);
    	HAL_TIM_Base_Start_IT(&htim4);
    	htim4.Init.Period = Step[0];
    }
    else
    	HAL_TIM_Base_Stop_IT(&htim4);

    Current_PosB=PosB;


}


void TIM4_IRQHandler(void)
{

		if(Set_Edge_B >= (2*Accel_Edge))
		{
			if(Current_Edge_B <= Accel_Edge )
			{
				if(B_index < (Accel_Edge-1))
				{
				   B_index++;
				}
				Current_Edge_B++;
				TIM4->ARR=Step[B_index];
				HAL_GPIO_TogglePin(MotorB_PUL);
			}

			else if(Current_Edge_B > Accel_Edge && Current_Edge_B < (Set_Edge_B - Decel_Edge))
			{
				Current_Edge_B++;
				TIM4->ARR=Step[Accel_Edge-1];
				HAL_GPIO_TogglePin(MotorB_PUL);
			}

			else
			{
				Current_Edge_B++;
				TIM4->ARR=Step[B_index];
				HAL_GPIO_TogglePin(MotorB_PUL);
				if(Current_Edge_B == Set_Edge_B)
				{

					Set_Edge_B =0;
					Current_Edge_B=0;
					B_index=0;
					Busy_Flag_B = 0;
					HAL_TIM_Base_Stop_IT(&htim4);
				}

				else
					B_index--;
			}

		}

		else
		{
			if(2*Current_Edge_B < (Set_Edge_B - 1))
			{
			   Current_Edge_B++;
			   B_index++;
			   TIM4->ARR=Step[B_index];
			   HAL_GPIO_TogglePin(MotorB_PUL);
			}
			else if(2*Current_Edge_B > (Set_Edge_B - 1))
			{
				Current_Edge_B++;
				TIM4->ARR=Step[B_index];
				B_index--;
				HAL_GPIO_TogglePin(MotorB_PUL);

				if(Current_Edge_B == Set_Edge_B)
				{
					Set_Edge_B=0;
					Current_Edge_B=0;
					B_index=0;
					Busy_Flag_B = 0;
					HAL_TIM_Base_Stop_IT(&htim4);
				}
			}
		}



   USER CODE BEGIN TIM3_IRQn 0

   USER CODE END TIM3_IRQn 0
  HAL_TIM_IRQHandler(&htim4);
   USER CODE BEGIN TIM3_IRQn 1

   USER CODE END TIM3_IRQn 1
}

void Origin_Motor_A()
{
	if (HAL_GPIO_ReadPin(SensorA)== 1)
	{
		process_origin_A = 4 ;
	}
	else
	{
		process_origin_A = 0 ;
	}
	process_origin_B = 0 ;

//	HAL_GPIO_WritePin(LED_EMG, RESET);
	Busy_Flag_Origin_A = 1;
	Busy_Flag_Origin_B = 1;
	Busy_Flag_Origin_AB = 1;
	htim15.Init.Period = 400;
	HAL_TIM_Base_Start_IT(&htim15);



}
void TIM15_IRQHandler(void)
{
	TIM15->ARR=400;
	//HAL_GPIO_TogglePin(MotorB_PUL);
	switch (process_origin_A)
	{
	case 0:
		HAL_GPIO_WritePin(MotorA_DIR, RESET); // nguoc chieu kim dong ho
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (HAL_GPIO_ReadPin(SensorA)== 1)//Neu Detect
		{
			Current_PosA = 0 ;
			process_origin_A = 1;
		}
		else if (Current_PosA == 4000)
		{
			Current_PosA = 0 ;
			process_origin_A = 2;
		}
		break;
	case 1:
		HAL_GPIO_WritePin(MotorA_DIR, RESET); // nguoc chieu kim dong ho
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (Current_PosA == 600)
		{
			process_origin_A = 100;
		}
		break;
	case 2:
		HAL_GPIO_WritePin(MotorA_DIR, SET);
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (HAL_GPIO_ReadPin(SensorA)== 1) // Neu Detect
		{
			Current_PosA = 0 ;
			process_origin_A = 4;
		}
		else if (Current_PosA == 6000)
		{
			Current_PosA = 0 ;
			process_origin_A = 101;
		}
		break;
	case 4:
		HAL_GPIO_WritePin(MotorA_DIR, SET); //chieu kim dong ho
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (Current_PosA == 3000)
		{
			process_origin_A = 0;
			Current_PosA  = 0 ;
		}
		break;
	case 10:
		HAL_GPIO_WritePin(MotorA_DIR, SET);
		HAL_GPIO_TogglePin(MotorA_PUL);
		Current_PosA ++ ;
		if (HAL_GPIO_ReadPin(SensorA)== 0)
		{
			Current_PosA = 0 ;
			process_origin_A = 0;
			HAL_GPIO_WritePin(MotorA_DIR, RESET);
		}
		else if (Current_PosA == 4000)
		{
			Current_PosA = 0 ;
			process_origin_A = 100;
		}
		break;
	case 100:
		HAL_GPIO_WritePin(LED_EMG, RESET);
		process_origin_A = 200 ;
		Current_PosA = 0 ;
		Busy_Flag_Origin_A =  0;
		break;
	case 101: //ERROR
		HAL_GPIO_WritePin(LED_EMG, SET);
		process_origin_A = 200 ;
		Current_PosA = 0 ;
		Busy_Flag_Origin_A =  0;
		break;
	case 200:
		process_origin_A = 200 ;
		break;

	}

	switch (process_origin_B)
	{
		case 0:
			if (HAL_GPIO_ReadPin(SensorB)== 0) // Neu chua detect
			{
				process_origin_B = 1;
				HAL_GPIO_WritePin(MotorB_DIR, RESET);
			}
			else // Neu dang Detect
			{
				HAL_GPIO_WritePin(MotorB_DIR, SET);
				Current_PosB = 0 ;
				process_origin_B = 2;
			}

			break;
		case 1:
			HAL_GPIO_TogglePin(MotorB_PUL);
			Current_PosB ++ ;
			if (HAL_GPIO_ReadPin(SensorB)== 1) // Neu detect
			{
				process_origin_B = 10;
				Current_PosB = 0 ;
			}
			break;
		case 2:
			HAL_GPIO_TogglePin(MotorB_PUL);
			Current_PosB ++ ;
			if (Current_PosB == 1000) // Neu chua detect
			{
				process_origin_B = 0;
				Current_PosB  = 0;
			}
			break;
		case 10:
			HAL_GPIO_TogglePin(MotorB_PUL);
			Current_PosB ++ ;
			if (Current_PosB == 1760)
			{
				process_origin_B = 200;
				Busy_Flag_Origin_B = 0 ;
				Current_PosB = 0 ;
			}
			break;
		case 200:
			process_origin_B = 200;
			break;

	}
	if ( Busy_Flag_Origin_A == 0 && Busy_Flag_Origin_B == 0)
	{
	 //	HAL_GPIO_WritePin(LED_EMG, RESET);
		process_origin_A = 0 ;
		process_origin_B = 0 ;
		Current_PosA = 0 ;
		Current_PosB = 0 ;
		Current_PosC = 0 ;
		Busy_Flag_Origin_A =  0;
		Busy_Flag_Origin_B =  0;
		Busy_Flag_Origin_AB =  0;
		HAL_TIM_Base_Stop_IT(&htim15);
	}


	HAL_TIM_IRQHandler(&htim15);
}*/
//==============================================

#endif /* CONTROL_STEP_MOTOR_C_ */
