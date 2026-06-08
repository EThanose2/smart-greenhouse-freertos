#include "greenhouse.h"

void vDisplayTask(void *pvParameters)
{
    while(1)
    {
        xSemaphoreTake(uartMutex, portMAX_DELAY);
        printf("[DISPLAY] Temp=%dC  Hum=%d%%  Fan=%s  Pump=%s\n",
               currentTemp, currentHum,
               fan  ? "ON" : "OFF",
               pump ? "ON" : "OFF");
        fflush(stdout);
        xSemaphoreGive(uartMutex);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}