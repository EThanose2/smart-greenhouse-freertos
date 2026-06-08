#include "greenhouse.h"

void vSensorTask(void *pvParameters)
{
    SensorData_t data;

    while(1)
    {
        data.temperature = rand() % 21 + 20;
        data.humidity    = rand() % 51 + 40;

        printf("[SENSOR]  Temp=%d C  Hum=%d%%\n",
               data.temperature, data.humidity);
        fflush(stdout);

        xQueueSend(sensorQueue, &data, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}