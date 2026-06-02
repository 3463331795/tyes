#include "cmsis_os2.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
extern osSemaphoreId_t KeyBinarySem01Handle;
void LogTaskFunc()
{
    for(;;)
    {
        if(osSemaphoreAcquire(KeyBinarySem01Handle, 100) == osOK) // 尝试获取信号量，立即返回
        {
            printf("按键事件已处理\r\n");
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，指示按键事件被处理
        }
        osDelay(500);
    }
}