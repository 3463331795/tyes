#include "cmsis_os2.h"
#include "key.h"
#include "stdio.h"
extern osSemaphoreId_t KeyBinarySem01Handle;

void KeyTaskFunc()
{
    for(;;)
    {
        if(KeyScan(0)) 
        {
            printf("按键入列\r\n");
            osSemaphoreRelease(KeyBinarySem01Handle); // 释放信号量，通知 Log_Task 有按键事件发生
        }
        osDelay(1);
    }
}