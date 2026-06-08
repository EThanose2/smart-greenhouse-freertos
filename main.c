#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "greenhouse.h"

QueueHandle_t     sensorQueue;
SemaphoreHandle_t uartMutex;

volatile int currentTemp = 0;
volatile int currentHum  = 0;
volatile int fan         = 0;
volatile int pump        = 0;

/* Required by FreeRTOS Windows port */
void vApplicationMallocFailedHook(void) {}
void vApplicationIdleHook(void) {}
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    (void)pxTask; (void)pcTaskName;
}
void vApplicationTickHook(void) {}
void vApplicationDaemonTaskStartupHook(void) {}

static StaticTask_t xIdleTaskTCB;
static StackType_t  uxIdleTaskStack[configMINIMAL_STACK_SIZE];
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t  **ppxIdleTaskStackBuffer,
                                   StackType_t   *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer   = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
}


void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t  **ppxTimerTaskStackBuffer,
                                    StackType_t   *pulTimerTaskStackSize)
{
    static StaticTask_t xTimerTaskTCB;
    static StackType_t  uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    *ppxTimerTaskTCBBuffer   = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH;
}

int main(void)
{
    printf("=== Smart Greenhouse FreeRTOS Simulator ===\n\n");
    fflush(stdout);

    printf("Creating queue...\n"); fflush(stdout);
    sensorQueue = xQueueCreate(5, sizeof(SensorData_t));
    if(sensorQueue == NULL) { printf("Queue failed!\n"); return 1; }

    printf("Creating mutex...\n"); fflush(stdout);
    uartMutex = xSemaphoreCreateMutex();
    if(uartMutex == NULL) { printf("Mutex failed!\n"); return 1; }

    printf("Creating tasks...\n"); fflush(stdout);
    xTaskCreate(vAlarmTask,   "Alarm",   4096, NULL, 4, NULL);
    xTaskCreate(vSensorTask,  "Sensor",  4096, NULL, 3, NULL);
    xTaskCreate(vControlTask, "Control", 4096, NULL, 2, NULL);
    xTaskCreate(vDisplayTask, "Display", 4096, NULL, 1, NULL);
    xTaskCreate(vUartTask,    "UART",    4096, NULL, 1, NULL);

    printf("Starting scheduler...\n"); fflush(stdout);
    vTaskStartScheduler();

    return 0;
}