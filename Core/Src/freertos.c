/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for SD_Card_Task */
osThreadId_t SD_Card_TaskHandle;
const osThreadAttr_t SD_Card_Task_attributes = {
  .name = "SD_Card_Task",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 128 * 4
};
/* Definitions for Teach_Motor_Tas */
osThreadId_t Teach_Motor_TasHandle;
const osThreadAttr_t Teach_Motor_Tas_attributes = {
  .name = "Teach_Motor_Tas",
  .priority = (osPriority_t) osPriorityNormal2,
  .stack_size = 128 * 4
};
/* Definitions for Call_Run_Task */
osThreadId_t Call_Run_TaskHandle;
const osThreadAttr_t Call_Run_Task_attributes = {
  .name = "Call_Run_Task",
  .priority = (osPriority_t) osPriorityNormal1,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Start_SDcard_Task(void *argument);
void Start_Teach_Motor(void *argument);
void Call_Run(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of SD_Card_Task */
  SD_Card_TaskHandle = osThreadNew(Start_SDcard_Task, NULL, &SD_Card_Task_attributes);

  /* creation of Teach_Motor_Tas */
  Teach_Motor_TasHandle = osThreadNew(Start_Teach_Motor, NULL, &Teach_Motor_Tas_attributes);

  /* creation of Call_Run_Task */
  Call_Run_TaskHandle = osThreadNew(Call_Run, NULL, &Call_Run_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */


/* USER CODE BEGIN Header_Start_SDcard_Task */
/**
* @brief Function implementing the SD_Card_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_SDcard_Task */


/* USER CODE BEGIN Header_Start_Teach_Motor */
/**
* @brief Function implementing the Teach_Motor_Tas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Teach_Motor */


/* USER CODE BEGIN Header_Call_Run */
/**
* @brief Function implementing the Call_Run_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Call_Run */


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
