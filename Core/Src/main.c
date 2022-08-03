/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "fatfs.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs_sd.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "Modbus.h"
#include "Control_Step_Motor.h"
#include "Define.h"
#include "sub_Funct.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


modbusHandler_t ModbusH;
//uint16_t ModbusDATA[8];
uint16_t ModbusDATA[256];



uint32_t count = 0;
uint8_t test_step = 0;
uint8_t Bit_data0 = 0;
uint8_t Bit_data1 = 0;
uint8_t Bit_data2 = 0;
uint8_t Bit_data3 = 0;
uint8_t Bit_data4 = 0;
uint8_t Bit_data5 = 0;
uint8_t Bit_data6 = 0;
uint8_t Bit_data7 = 0;
uint8_t Bit_data8 = 0;
uint8_t Bit_data9 = 0;
uint8_t Bit_data10 = 0;
uint8_t Bit_data11 = 0;
uint8_t Bit_data12 = 0;
uint8_t Bit_data13 = 0;
uint8_t Bit_data14 = 0;
uint8_t Bit_data15 = 0;
uint8_t Bit_data16 = 0;
uint8_t Bit_data17 = 0;
uint8_t Bit_data18 = 0;
uint8_t Bit_data19 = 0;
uint8_t Bit_data20 = 0;
uint8_t Bit_data21 = 0;
uint8_t Bit_data22 = 0;
uint8_t Bit_data23 = 0;
uint8_t BT_Start_Stage = 0;
//uint32_t milisec = 0;
uint32_t bien_Count = 0;

/*------ Teaching by jog funct variable ------*/





/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	  mHandlers[0]->u8Buffer[3] = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_12);
	  Bit_data0 = mHandlers[0]->xBufferRX.uxBuffer[0];
	  Bit_data1 = mHandlers[0]->xBufferRX.uxBuffer[1];
	  Bit_data2 = mHandlers[0]->xBufferRX.uxBuffer[2];
	  Bit_data3 = mHandlers[0]->xBufferRX.uxBuffer[3];
	  Bit_data4 = mHandlers[0]->xBufferRX.uxBuffer[4];
	  Bit_data5 = mHandlers[0]->xBufferRX.uxBuffer[5];
	  Bit_data6 = mHandlers[0]->xBufferRX.uxBuffer[6];
	  Bit_data7 = mHandlers[0]->xBufferRX.uxBuffer[7];

	  Bit_data8 = mHandlers[0]->xBufferRX.uxBuffer[8];
	  Bit_data9 = mHandlers[0]->xBufferRX.uxBuffer[9];
	  Bit_data10 = mHandlers[0]->xBufferRX.uxBuffer[10];
	  Bit_data11 = mHandlers[0]->xBufferRX.uxBuffer[11];
	  Bit_data12 = mHandlers[0]->xBufferRX.uxBuffer[12];
	  Bit_data13 = mHandlers[0]->xBufferRX.uxBuffer[13];
	  Bit_data14 = mHandlers[0]->xBufferRX.uxBuffer[14];
	  Bit_data15 = mHandlers[0]->xBufferRX.uxBuffer[15];

	  Bit_data16 = mHandlers[0]->xBufferRX.uxBuffer[16];
	  Bit_data17 = mHandlers[0]->xBufferRX.uxBuffer[17];
	  Bit_data18 = mHandlers[0]->xBufferRX.uxBuffer[18];
	  Bit_data19 = mHandlers[0]->xBufferRX.uxBuffer[19];
	  Bit_data20 = mHandlers[0]->xBufferRX.uxBuffer[20];
	  Bit_data21 = mHandlers[0]->xBufferRX.uxBuffer[21];
	  Bit_data22 = mHandlers[0]->xBufferRX.uxBuffer[22];
	  Bit_data23 = mHandlers[0]->xBufferRX.uxBuffer[23];
	  bien_Count++;

/*	  if(Main_process == 1)
	  {
		  fresult = f_mount(&fs,"",1);
		  fresult = f_open(&myfile,"DUC.txt",FA_CREATE_ALWAYS|FA_WRITE);
		  f_printf(&myfile,SD_Coordinates);
		  f_close(&myfile);
		  f_sync(&myfile);
		  Main_process = 0;
	  }*/
      osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}
void Start_SDcard_Task(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
/*	  count++;
	  if(count == 10000)
	  {
		  fresult = f_mount(&fs,"",1);											// Ket noi voi the nho
		  fresult = f_open(&myfile,"RTOSTUOILOZ.txt",FA_CREATE_ALWAYS|FA_WRITE); // Mo file
		  f_printf(&myfile,"dmchanvl");
		  f_close(&myfile);														// Dong the nho
		  f_sync(&myfile);
	  }*/
	  switch(Main_process)
	  {
		  case 1:
		  {
			  if(Pos_Index == 0)
			  {
				  fresult = f_mount(&fs,"",1);
				  fresult = f_open(&myfile,"No1.txt",FA_CREATE_ALWAYS|FA_WRITE);
				  f_printf(&myfile,SD_Coordinates);
				  f_close(&myfile);
				  f_sync(&myfile);
				  Main_process = 0;
				  Teach_Point_Count++;
			  }
			  else if(Pos_Index >= 1)
			  {
				  fresult = f_mount(&fs,"",1);
				  fresult = f_open(&myfile,"No1.txt",FA_CREATE_ALWAYS|FA_WRITE);
				  Main_Coor_count = Main_Coor_count + Temp_Coor_count;
				  fresult = f_lseek(&myfile,Main_Coor_count);
				  f_printf(&myfile,SD_Coordinates);
				  f_close(&myfile);
				  f_sync(&myfile);
				  Main_process = 0;
				  Teach_Point_Count++;
			  }
			  for(uint8_t i = 0;i<150;i++)
			  {
				  if(SD_Coordinates[i] == 0x00)
				  {
					  Temp_Coor_count = i;
					  break;
				  }
			  }
			  for(uint8_t i = 0;i<150;i++)
			  {
				  SD_Coordinates[i] = 0;
			  }
			 break;
		  }
		  case 2:
		  {
			  switch(Run_File_No)
			  {
				  case 1:
				  {
					  fresult = f_mount(&fs,"",1);
					  fresult = f_open(&myfile,"No1.txt",FA_READ);
					  fresult = f_read(&myfile,SD_All_Point,f_size(&myfile),(UINT*)&br);
					  f_close(&myfile);
					  f_sync(&myfile);
					  Main_process = 0xFF;
					  break;
				  }
				  case 2:
				  {
					  fresult = f_mount(&fs,"",1);
					  fresult = f_open(&myfile,"No2.txt",FA_READ);
					  fresult = f_read(&myfile,SD_All_Point,f_size(&myfile),(UINT*)&br);
					  f_close(&myfile);
					  f_sync(&myfile);
					  Main_process = 0xFF;
					  break;
				  }
			  }
			  break;
		  }
	  }
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}
void Start_Teach_Motor(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
	  switch(Teach_Move_Process)
	  {
	  	  case 1:
	  	  {
			  if(Busy_Flag_XYZ == 0 && Origin_Flag == 0 )
			  {
				  Move_XYZ_ABC(Teach_X_Axis_Value/2, Teach_Y_Axis_Value/2,Teach_Z_Axis_Value/2,Teach_A_Axis_Value/2,Teach_B_Axis_Value/2,Teach_C_Axis_Value/2,Teach_Velocity_Value,5);
				  Teach_Move_Process = 2;
			  }
	  		  break;
	  	  }
	  	  case 2:
	  	  {
	  		  if(Busy_Flag_XYZ == 0)
	  		  {
				  Teach_Move_Process = 0xFF;
	  		  }
	  		  break;
	  	  }
	  	  case 3:
	  	  {
	  		  if(Busy_Flag_XYZ == 0)
	  		  {
				  Origin_Motor();
				  Teach_Move_Process = 4;
	  		  }
	  		  break;
	  	  }
	  	  case 4:
	  	  {
	  		  if(Origin_Flag == 0)
	  		  {
	  			  reset_Value();
	  		  }
	  		  break;
	  	  }
	  	  default:
	  	  {
	  		  break;
	  	  }
	  }
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

void Call_Run(void *argument)
{
  /* USER CODE BEGIN Call_Run */
  /* Infinite loop */
  for(;;)
  {
	  switch(run_Process)
	  {
		  case 1:
		  {
			  count_Total_Point();
			  run_Process = 2;
			  break;
		  }
		  case 2:
		  {
			  sd_Data_Handle();
			  output_Display();
			  run_Process = 3;
			  break;
		  }
		  case 3:
		  {
			  if(Busy_Flag_XYZ == 0 && Origin_Flag == 0 )
			  {
				  Move_XYZ_ABC(run_PosX/2, run_PosY/2,run_PosZ/2,run_PosA/2,run_PosB/2,run_PosC/2,run_Speed,5);
				  run_Process = 4;
			  }
			  break;
		  }
		  case 4:
		  {
	  		  if(Busy_Flag_XYZ == 0)
	  		  {
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
	  			run_Point_Count++;
	  			run_Process = 5;
	  			current_Millis = milisec;
	  			if(run_Point_Count >= run_Pos_Index)
	  			{
		  			run_Process = 0xFF;
	  			}
	  		  }
			  break;
		  }
		  case 5:
		  {
			  if((milisec - current_Millis) >= 2000)
			  {

		  			run_Process = 1;
			  }
			  break;
		  }
		  default:
		  {
			  break;
		  }
	  }
    osDelay(1);
  }
  /* USER CODE END Call_Run */
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*modbusHandler_t ModbusH;
//uint16_t ModbusDATA[8];
uint16_t ModbusDATA[256];*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_SPI3_Init();
  MX_FATFS_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM15_Init();
  MX_TIM16_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */



  while(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_12) && HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_13));

  Motor_Init();
  Origin_Motor();
  while(Origin_Flag);
/*  Origin_Motor_A();
  while(Busy_Flag_Origin_AB);*/

  HAL_Delay(200);
	HAL_TIM_Base_Start_IT(&htim14);
  /* Modbus Slave initialization */
        ModbusH.uModbusType = MB_SLAVE;
        ModbusH.port =  &huart3; // This is the UART port connected to STLINK in the NUCLEO F429
        ModbusH.u8id = 1; //slave ID
        ModbusH.u16timeOut = 1000;
        ModbusH.EN_Port = NULL; // No RS485
//         ModbusH.EN_Port = LD2_GPIO_Port; // RS485 Enable
//         ModbusH.EN_Pin = LD2_Pin; // RS485 Enable
/*
         ModbusH2.EN_Port = LD2_GPIO_Port; // RS485 Enable
         ModbusH2.EN_Pin = LD2_Pin; // RS485 Enable
*/
        ModbusH.u16regs = ModbusDATA;
        ModbusH.u16regsize= sizeof(ModbusDATA)/sizeof(ModbusDATA[0]);
        ModbusH.xTypeHW = USART_HW;
         //Initialize Modbus library
        ModbusInit(&ModbusH);
        //Start capturing traffic on serial Port
        ModbusStart(&ModbusH);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_SPI3;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void TIM16_IRQHandler(void)
{
  /* USER CODE BEGIN TIM16_IRQn 0 */

	switch(JogX_Busy_Flag)
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			HAL_GPIO_TogglePin(MotorX_PUL);
			Teach_X_Axis_Value++;
			Current_PosX = Teach_X_Axis_Value / 2;
			if(Teach_X_Axis_Value >= 60000)
			{
				HAL_TIM_Base_Stop_IT(&htim16);
			}
			break;
		}
		case 2:
		{
			if(HAL_GPIO_ReadPin(SensorX) == 0)
			{
				HAL_GPIO_TogglePin(MotorX_PUL);
				Teach_X_Axis_Value--;
				Current_PosX = Teach_X_Axis_Value / 2;
				JogX_Busy_Flag = 3;
				break;
			}
			break;
		}
		case 3:
		{
			if(HAL_GPIO_ReadPin(SensorX) == 1)
			{
				Teach_X_Axis_Value = 0;
				Current_PosX = 0;
				HAL_TIM_Base_Stop_IT(&htim16);
			}
			else
			{
				JogX_Busy_Flag = 2;
			}
			break;
		}
		default :
		{
			break;
		}
	}
	switch(JogY_Busy_Flag)
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			HAL_GPIO_TogglePin(MotorY_PUL);
			Teach_Y_Axis_Value++;
			Current_PosY = Teach_Y_Axis_Value / 2;
			if(Teach_Y_Axis_Value >= 60000)
			{
				HAL_TIM_Base_Stop_IT(&htim16);
			}
			break;
		}
		case 2:
		{
			if(HAL_GPIO_ReadPin(SensorY) == 0)
			{
				HAL_GPIO_TogglePin(MotorY_PUL);
				Teach_Y_Axis_Value--;
				Current_PosY = Teach_Y_Axis_Value / 2;
				JogY_Busy_Flag = 3;
				break;
			}
			break;
		}
		case 3:
		{
			if(HAL_GPIO_ReadPin(SensorY) == 1)
			{
				Teach_Y_Axis_Value = 0;
				Current_PosY = 0;
				HAL_TIM_Base_Stop_IT(&htim16);
			}
			else
			{
				JogY_Busy_Flag = 2;
			}
			break;
		}
		default :
		{
			break;
		}
	}
	switch(JogZ_Busy_Flag)
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			if(HAL_GPIO_ReadPin(SensorZ) == 0)
			{
				HAL_GPIO_TogglePin(MotorZ_PUL);
				Teach_Z_Axis_Value--;
				Current_PosZ = Teach_Z_Axis_Value / 2;
				if(Teach_Z_Axis_Value == 0)
				{
					HAL_TIM_Base_Stop_IT(&htim16);
				}
				break;
			}
			break;
		}
		case 2:
		{
			if(Teach_Z_Axis_Value >= 0 && Teach_Z_Axis_Value <= 40000 )
			{
				HAL_GPIO_TogglePin(MotorZ_PUL);
				Teach_Z_Axis_Value;
				Current_PosZ = Teach_Z_Axis_Value / 2;
			}
			else if(JogZ_Axis_Count > 40000)
			{
				HAL_TIM_Base_Stop_IT(&htim16);
			}
			break;
		}
		case 3:
		{
			if(HAL_GPIO_ReadPin(SensorZ) == 1)
			{
				Teach_Z_Axis_Value = 0;
				Current_PosZ = 0;
				HAL_TIM_Base_Stop_IT(&htim16);
			}
			else
			{
				JogZ_Busy_Flag = 1;
			}
			break;
		}
		default :
		{
			break;
		}
	}



  /* USER CODE END TIM16_IRQn 0 */
  HAL_TIM_IRQHandler(&htim16);
  /* USER CODE BEGIN TIM16_IRQn 1 */

  /* USER CODE END TIM16_IRQn 1 */
}

void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */
	milisec++;
  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
  HAL_TIM_IRQHandler(&htim14);
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM17 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM17) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
