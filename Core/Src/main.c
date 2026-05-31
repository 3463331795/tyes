/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include "stdio.h"
#include "test.h"
#include "delay.h"
#include "lcd_init.h"
#include "lcd.h"
#include "cst816.h"

// ===================== LVGL驱动相关头文件 =======================
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"

// ===================== 自定义图形驱动相关头文件 =======================
#include "gui_guider.h"           // Gui Guider 生成的界面和控件的声明
#include "events_init.h"          // Gui Guider 生成的初始化事件、回调函数
lv_ui  guider_ui;                     // 声明 界面对象
uint8_t dc=100;

void LCD_ColorCycleDemo(void);

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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
  delay_init();
  LCD_Init();
  LCD_Set_Light(dc); // 亮度拉到最满
  LCD_Open_Light();   // 启动背光 PWM 

  CST816_Init();    //触摸屏

  // ===================== LVGL 初始化 =======================
  lv_init();          // LVGL 初始化
  lv_port_disp_init(); // LVGL 显示驱动初始化
  lv_port_indev_init(); // LVGL 输入设备驱动初始化
  HAL_TIM_Base_Start_IT(&htim11); // 启动 LVGL 定时器中断

  // ===================== 自定义图形 初始化 =======================
  setup_ui(&guider_ui); // Gui Guider 生成的界面和控件的初始化
  events_init(&guider_ui); // Gui Guider 生成的事件、回调函数的初始化
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    //LCD_ColorCycleDemo();
    
    HAL_Delay(1-1);

    static uint8_t msLVGL = 0;
    if(msLVGL++ >= 5) { // 每 5ms 调用一次 lv_task_handler，处理 LVGL 的任务
        msLVGL = 0;
        lv_task_handler();
    }
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */



#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	//HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,1000);
	
	while((huart1.Instance->SR & USART_SR_TXE) ==0);
	huart1.Instance->DR = *(uint8_t*)&ch;
	return ch;
}

// 简单纯色区域填充（使用 LCD_Color_Fill）
static void LCD_ColorFillSolid(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
    static uint16_t line_buf[LCD_W];
    uint16_t width = xend - xsta + 1;

    for (uint16_t i = 0; i < width; i++)
    {
        line_buf[i] = color;
    }

    for (uint16_t row = ysta; row <= yend; row++)
    {
        LCD_Color_Fill(xsta, row, xend, row, line_buf);
        while (hspi1.State != HAL_SPI_STATE_READY)
        {
        }
    }
       
}

// 简单颜色切换演示
void LCD_ColorCycleDemo(void)
{
    const uint16_t colors[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, BLACK};
    const char *names[] = {"RED", "GREEN", "BLUE", "YELLOW", "CYAN", "MAGENTA", "WHITE", "BLACK"};

    for (int i = 0; i < 8; i++)
    {
        uint16_t bg = colors[i];
        uint16_t fc = (bg == BLACK) ? WHITE : BLACK; // 黑底白字，其它底黑字
        LCD_ColorFillSolid(0, 0, LCD_W - 1, LCD_H - 1, bg);

        LCD_ShowString(60, 100, (uint8_t *)names[i], fc, bg, 24, 0);
        HAL_Delay(800);
    }
}

uint16_t time_tick = 0;
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  else if(htim->Instance == TIM11) // LVGL 定时器中断
  {
      lv_tick_inc(1); // 每 1ms 增加 LVGL 的系统时间
      // 这里可以添加其他需要在定时器中处理的任务
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
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
