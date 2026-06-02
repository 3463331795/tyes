/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stdio.h"
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
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for key_task */
osThreadId_t key_taskHandle;
const osThreadAttr_t key_task_attributes = {
  .name = "key_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for Log_Task */
osThreadId_t Log_TaskHandle;
const osThreadAttr_t Log_Task_attributes = {
  .name = "Log_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for H_Task */
osThreadId_t H_TaskHandle;
const osThreadAttr_t H_Task_attributes = {
  .name = "H_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow2,
};
/* Definitions for M_Task */
osThreadId_t M_TaskHandle;
const osThreadAttr_t M_Task_attributes = {
  .name = "M_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for L_Task */
osThreadId_t L_TaskHandle;
const osThreadAttr_t L_Task_attributes = {
  .name = "L_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myTimer01 */
osTimerId_t myTimer01Handle;
const osTimerAttr_t myTimer01_attributes = {
  .name = "myTimer01"
};
/* Definitions for Mutex01 */
osMutexId_t Mutex01Handle;
const osMutexAttr_t Mutex01_attributes = {
  .name = "Mutex01"
};
/* Definitions for KeyBinarySem01 */
osSemaphoreId_t KeyBinarySem01Handle;
const osSemaphoreAttr_t KeyBinarySem01_attributes = {
  .name = "KeyBinarySem01"
};
/* Definitions for BinarySem01 */
osSemaphoreId_t BinarySem01Handle;
const osSemaphoreAttr_t BinarySem01_attributes = {
  .name = "BinarySem01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void KeyTaskFunc(void *argument);
void LogTaskFunc(void *argument);
void Task_H_Func(void *argument);
void Task_M_Func(void *argument);
void Task_L_Func(void *argument);
void Callback01(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
// 你的代码
  static uint16_t timecount=0;
	timecount += 1;
	if(timecount>500)
	{
		timecount = 0;
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
}
/* USER CODE END 3 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of Mutex01 */
  Mutex01Handle = osMutexNew(&Mutex01_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of KeyBinarySem01 */
  KeyBinarySem01Handle = osSemaphoreNew(1, 1, &KeyBinarySem01_attributes);

  /* creation of BinarySem01 */
  BinarySem01Handle = osSemaphoreNew(1, 1, &BinarySem01_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of myTimer01 */
  myTimer01Handle = osTimerNew(Callback01, osTimerPeriodic, NULL, &myTimer01_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  // defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  // /* creation of key_task */
  // key_taskHandle = osThreadNew(KeyTaskFunc, NULL, &key_task_attributes);

  // /* creation of Log_Task */
  // Log_TaskHandle = osThreadNew(LogTaskFunc, NULL, &Log_Task_attributes);

  // /* creation of H_Task */
  // H_TaskHandle = osThreadNew(Task_H_Func, NULL, &H_Task_attributes);

  // /* creation of M_Task */
  // M_TaskHandle = osThreadNew(Task_M_Func, NULL, &M_Task_attributes);

  // /* creation of L_Task */
  // L_TaskHandle = osThreadNew(Task_L_Func, NULL, &L_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  osTimerStart(myTimer01Handle,500);  //启动软件定时器，分配时间
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); 
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_KeyTaskFunc */
/**
* @brief Function implementing the key_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_KeyTaskFunc */
__weak void KeyTaskFunc(void *argument)
{
  /* USER CODE BEGIN KeyTaskFunc */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END KeyTaskFunc */
}

/* USER CODE BEGIN Header_LogTaskFunc */
/**
* @brief Function implementing the Log_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LogTaskFunc */
__weak void LogTaskFunc(void *argument)
{
  /* USER CODE BEGIN LogTaskFunc */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LogTaskFunc */
}

/* USER CODE BEGIN Header_Task_H_Func */
/**
* @brief Function implementing the H_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_H_Func */
void Task_H_Func(void *argument)
{
  /* USER CODE BEGIN Task_H_Func */
  /* Infinite loop */
  for(;;)
  {
    //osSemaphoreAcquire(BinarySem01Handle, osWaitForever);
    osMutexAcquire(Mutex01Handle, osWaitForever);
    printf("High Task get mutex, start\r\n");
    HAL_Delay(1000);
    printf("High Task give mutex, end\r\n");
    //osSemaphoreRelease(BinarySem01Handle);
    osMutexRelease(Mutex01Handle);
    osDelay(1000);
  }
  /* USER CODE END Task_H_Func */
}

/* USER CODE BEGIN Header_Task_M_Func */
/**
* @brief Function implementing the M_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_M_Func */
void Task_M_Func(void *argument)
{
  /* USER CODE BEGIN Task_M_Func */
  /* Infinite loop */
  for(;;)
  {
    printf("Middle Task use cpu, but do nothing\r\n");
    osDelay(1000);
  }
  /* USER CODE END Task_M_Func */
}

/* USER CODE BEGIN Header_Task_L_Func */
/**
* @brief Function implementing the L_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_L_Func */
void Task_L_Func(void *argument)
{
  /* USER CODE BEGIN Task_L_Func */
  /* Infinite loop */
  for(;;)
  {
    //osSemaphoreAcquire(BinarySem01Handle, osWaitForever);
    osMutexAcquire(Mutex01Handle, osWaitForever);
    printf("Low Task get mutex, start\r\n");
    //HAL_Delay(5000);
    HAL_Delay(3000);
    printf("Low Task give mutex, end\r\n");
    //osSemaphoreRelease(BinarySem01Handle);
    osMutexRelease(Mutex01Handle);
    osDelay(1000);    
  }
  /* USER CODE END Task_L_Func */
}

/* Callback01 function */
void Callback01(void *argument)
{
  /* USER CODE BEGIN Callback01 */
  printf("software timer run\r\n");
  /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */



/* USER CODE END Application */

