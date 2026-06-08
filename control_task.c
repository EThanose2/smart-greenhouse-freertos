#include "greenhouse.h"

void vControlTask(void *pvParameters)
{
    SensorData_t data;

    while(1)
    {
        if(xQueueReceive(sensorQueue, &data, portMAX_DELAY) == pdTRUE)
        {
            currentTemp = data.temperature;
            currentHum  = data.humidity;

            fan  = (data.temperature > 35) ? 1 : 0;
            pump = (data.humidity    < 50) ? 1 : 0;

            printf("[CONTROL] Fan=%s  Pump=%s\n",
                   fan ? "ON" : "OFF", pump ? "ON" : "OFF");
            fflush(stdout);
        }
    }
}