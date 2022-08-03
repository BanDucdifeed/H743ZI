/*
 * Control_Step_Motor.h
 *
 *  Created on: Mar 6, 2020
 *      Author: TL-APRO-NPC 16
 *	Modify By N.K.Dinh / 18/Nov/2021
 *
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
 */

#ifndef CONTROL_STEP_MOTOR_H_
#define CONTROL_STEP_MOTOR_H_

//==============================================

#include "stdint.h"
#include "stm32h7xx_hal.h"

#define MotorX_ENA    GPIOG,GPIO_PIN_9
#define MotorY_ENA    GPIOG,GPIO_PIN_10
#define MotorZ_ENA    GPIOG,GPIO_PIN_11
#define MotorA_ENA    GPIOD,GPIO_PIN_2
#define MotorB_ENA    GPIOD,GPIO_PIN_3
#define MotorC_ENA    GPIOD,GPIO_PIN_4


#define MotorX_DIR    GPIOC,GPIO_PIN_12
#define MotorY_DIR    GPIOD,GPIO_PIN_0
#define MotorZ_DIR    GPIOD,GPIO_PIN_1
#define MotorA_DIR    GPIOA,GPIO_PIN_10
#define MotorB_DIR    GPIOA,GPIO_PIN_11
#define MotorC_DIR    GPIOA,GPIO_PIN_12

#define MotorX_PUL    GPIOC,GPIO_PIN_9
#define MotorY_PUL    GPIOA,GPIO_PIN_8
#define MotorZ_PUL    GPIOA,GPIO_PIN_9
#define MotorA_PUL    GPIOC,GPIO_PIN_6
#define MotorB_PUL    GPIOC,GPIO_PIN_7
#define MotorC_PUL    GPIOC,GPIO_PIN_8

#define SensorX       GPIOF,GPIO_PIN_4
#define SensorY       GPIOF,GPIO_PIN_6
#define SensorZ       GPIOF,GPIO_PIN_8
#define SensorA       GPIOE,GPIO_PIN_2
#define SensorB       GPIOE,GPIO_PIN_3

#define EMG_Button          GPIOF, GPIO_PIN_14
#define Safety_DoorL  		GPIOF,GPIO_PIN_1
#define Safety_DoorR		GPIOF,GPIO_PIN_0
#define LED_EMG  			GPIOE,GPIO_PIN_12

//==============================================
int32_t Current_PosX;
int32_t Current_PosY;
int32_t Current_PosZ;

uint8_t Busy_Flag_X;
uint8_t Busy_Flag_Y;
uint8_t Busy_Flag_Z;
uint8_t Busy_Flag_XY;
uint8_t Busy_Flag_XYZ;

uint8_t Origin_Flag_X;
uint8_t Origin_Flag_Y;
uint8_t Origin_Flag_Z;
uint8_t Origin_Flag;
uint8_t Check_EMG;

int32_t Check_n;
float check_Cn;

int32_t check_pos_x,check_pos_y,check_pos_z,check_pos_a,check_pos_b,check_pos_c;
int32_t cur_pos_x,cur_pos_y, cur_pos_z,cur_pos_a,cur_pos_b, cur_pos_c;

//Motor A -B ///////////
int32_t Current_PosA;
int32_t Current_PosB;
int32_t Current_PosC;
uint8_t Busy_Flag_A;
uint8_t Busy_Flag_B;

uint8_t Busy_Flag_Origin_AB;


// Syn 6 Axis
uint8_t flag_check_syn ;


//==============================================


void Motor_Init(void);

void Origin_Motor(void); //tim5

void Move_MotorA(int32_t PosA,float speed_value,float Accel_value); //tim3 -- 1-1000, 1-100

void Move_MotorB(int32_t PosB,float speed_value,float Accel_value); //tim4 -- 1-1000, 1-100

void Origin_Motor_A(); // timer 15

void Draw_Circle_XY(int32_t Ox, int32_t Oy, uint16_t R,float speed_value,float Accel_value); //tim16

void Move_MotorXYZ(int32_t Pos_X, int32_t Pos_Y,int32_t Pos_Z,float speed_value,float Accel_value); // tim17

void Move_XYZ_ABC(int32_t Pos_X, int32_t Pos_Y,int32_t Pos_Z,int32_t Pos_A, int32_t Pos_B,int32_t Pos_C,float speed_value,float Accel_value); // tim17

//==============================================

#endif /* CONTROL_STEP_MOTOR_H_ */




