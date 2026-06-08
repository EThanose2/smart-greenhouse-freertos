#include "greenhouse.h"

void vAlarmTask(void *pvParameters)
{
    while(1)
    {
        if(currentTemp > 38)
        {
            xSemaphoreTake(uartMutex, portMAX_DELAY);
            printf("[ALARM]   !!! CANH BAO NHIET DO CAO: %d C !!!\n", currentTemp);
            fflush(stdout);
            xSemaphoreGive(uartMutex);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}