#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

typedef struct {
    int temperature;
    int humidity;
} SensorData_t;

extern QueueHandle_t     sensorQueue;
extern SemaphoreHandle_t uartMutex;

extern volatile int currentTemp;
extern volatile int currentHum;
extern volatile int fan;
extern volatile int pump;

void vSensorTask (void *pvParameters);
void vControlTask(void *pvParameters);
void vDisplayTask(void *pvParameters);
void vAlarmTask  (void *pvParameters);
void vUartTask   (void *pvParameters);

#endif