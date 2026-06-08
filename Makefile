FREERTOS := /c/Users/ASUS/Downloads/FreeRTOS/FreeRTOS/Source

CC := gcc
CFLAGS := -O0 -g3 -Wall -D_WIN32_WINNT=0x0601 -I$(FREERTOS)/include -I$(FREERTOS)/portable/MSVC-MingW -I.

SRCS := main.c sensor_task.c control_task.c display_task.c alarm_task.c uart_task.c $(FREERTOS)/tasks.c $(FREERTOS)/queue.c $(FREERTOS)/list.c $(FREERTOS)/timers.c $(FREERTOS)/portable/MSVC-MingW/port.c $(FREERTOS)/portable/MemMang/heap_4.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o SmartGreenhouse.exe -lwinmm

clean:
	rm -f SmartGreenhouse.exe