#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdio.h>
#include <windows.h>

#define configUSE_PREEMPTION                    1
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configUSE_TRACE_FACILITY                0
#define configUSE_16_BIT_TICKS                  0
#define configUSE_MUTEXES                       1
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               2
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            256
#define configCPU_CLOCK_HZ                      100000000
#define configTICK_RATE_HZ                      1000
#define configMINIMAL_STACK_SIZE                1024
#define configTOTAL_HEAP_SIZE                   (4*1024*1024)
#define configMAX_TASK_NAME_LEN                 16
#define configMAX_PRIORITIES                    7
#define configQUEUE_REGISTRY_SIZE               0
#define configUSE_MALLOC_FAILED_HOOK            0
#define configCHECK_FOR_STACK_OVERFLOW          0
#define configUSE_STATS_FORMATTING_FUNCTIONS    0
#define configUSE_QUEUE_SETS                    0
#define configSUPPORT_STATIC_ALLOCATION         1
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configNUMBER_OF_CORES                   1

#define INCLUDE_vTaskDelay                      1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_xTaskGetSchedulerState          1

#define configASSERT(x) if((x)==0){printf("ASSERT failed line %d\n",__LINE__);for(;;);}

#endif