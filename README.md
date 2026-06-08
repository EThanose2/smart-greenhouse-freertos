# 🌿 Smart Greenhouse — FreeRTOS Simulator

A simulated smart greenhouse monitoring system built with **FreeRTOS**, demonstrating real-time embedded software architecture concepts including multitasking, inter-task communication, and resource synchronization — without requiring physical hardware.

---

## 📋 Project Overview

This project simulates a greenhouse environment control system where:
- Temperature and humidity sensors are **software-simulated** (20–40°C, 40–90%)
- A **fan** activates when temperature exceeds 35°C
- A **water pump** activates when humidity drops below 50%
- An **alarm** triggers when temperature exceeds 38°C
- All data is periodically transmitted via simulated **UART**

---

## 🏗️ System Architecture

```
+------------------+
|   Sensor Task    |  Generates simulated sensor data every 1s
+------------------+
         |
         |  Queue (SensorData_t)
         v
+------------------+
|   Control Task   |  Applies control logic (Fan, Pump)
+------------------+
         |
    +----+----+
    |         |
    v         v
+-------+ +----------+
| Alarm | | Display  |
| Task  | |  Task    |
+-------+ +----------+
               |
               v  (Mutex-protected UART)
        +------------+
        | UART Task  |  Sends data every 2s
        +------------+
```

---

## ⚙️ FreeRTOS Concepts Demonstrated

| Concept | Usage |
|---|---|
| **Tasks** | 5 concurrent tasks with different priorities |
| **Queue** | `sensorQueue` passes `SensorData_t` from Sensor → Control Task |
| **Mutex** | `uartMutex` prevents concurrent UART access across tasks |
| **Task Priority** | Alarm (4) > Sensor (3) > Control (2) > Display/UART (1) |
| **vTaskDelay** | Non-blocking delay for each task's execution interval |
| **Static Allocation** | Idle and Timer tasks use static memory |

---

## 📁 Project Structure

```
SmartGreenhouse/
├── main.c            # Scheduler init, task creation, FreeRTOS hooks
├── greenhouse.h      # Shared types, extern declarations
├── sensor_task.c     # Simulates temperature & humidity readings
├── control_task.c    # Fan/pump control logic via queue
├── display_task.c    # Prints system state every 1s
├── alarm_task.c      # High-temperature warning every 500ms
├── uart_task.c       # Periodic data transmission every 2s
├── FreeRTOSConfig.h  # FreeRTOS configuration
└── Makefile          # Build script (MinGW/GCC)
```

---

## 🔄 Task Details

### Sensor Task — Priority 3
Runs every **1000ms**. Generates random sensor values:
```c
data.temperature = rand() % 21 + 20;  // 20~40°C
data.humidity    = rand() % 51 + 40;  // 40~90%
xQueueSend(sensorQueue, &data, portMAX_DELAY);
```

### Control Task — Priority 2
Receives data from queue and applies control rules:
```c
fan  = (temperature > 35) ? 1 : 0;
pump = (humidity    < 50) ? 1 : 0;
```

### Alarm Task — Priority 4 (highest)
Checks every **500ms** for critical temperature:
```c
if (currentTemp > 38)
    printf("[ALARM] !!! CANH BAO NHIET DO CAO: %d C !!!\n", currentTemp);
```

### Display Task — Priority 1
Prints full system status every **1000ms**.

### UART Task — Priority 1
Transmits compact data string every **2000ms**. Uses mutex to avoid collision with other tasks writing to UART.

---

## 📦 Shared Data Structure

```c
typedef struct {
    int temperature;
    int humidity;
} SensorData_t;
```

---

## 🖥️ Sample Output

```
=== Smart Greenhouse FreeRTOS Simulator ===

[SENSOR]  Temp=40 C  Hum=45%
[CONTROL] Fan=ON  Pump=ON
[DISPLAY] Temp=40C  Hum=45%  Fan=ON  Pump=ON
[UART]    Temp=40,Hum=45,Fan=ON,Pump=ON
[ALARM]   !!! CANH BAO NHIET DO CAO: 40 C !!!
[SENSOR]  Temp=33 C  Hum=71%
[CONTROL] Fan=OFF  Pump=OFF
[DISPLAY] Temp=33C  Hum=71%  Fan=OFF  Pump=OFF
[UART]    Temp=33,Hum=71,Fan=OFF,Pump=OFF
[SENSOR]  Temp=37 C  Hum=56%
[CONTROL] Fan=ON  Pump=OFF
```

---

## 🛠️ Build & Run

### Requirements
- [MSYS2](https://www.msys2.org/) with MinGW64
- [FreeRTOS Kernel](https://github.com/FreeRTOS/FreeRTOS) (cloned via git)
- GCC 14+

### Steps

```bash
# Clone FreeRTOS kernel
git clone https://github.com/FreeRTOS/FreeRTOS.git --depth=1
cd FreeRTOS
git submodule update --init --recursive

# Clone this repo
git clone https://github.com/EThanose2/smart-greenhouse-freertos
cd smart-greenhouse-freertos

# Build
make

# Run
./SmartGreenhouse.exe
```

---

## 📌 Key Design Decisions

**Why Queue instead of global variable for sensor data?**
Queue provides thread-safe, buffered communication between tasks. The Control Task blocks on the queue and only wakes when new data arrives — more efficient than polling a global variable.

**Why Mutex for UART?**
Multiple tasks (Display, UART, Alarm) all write to stdout. Without a mutex, their outputs would interleave and produce garbled text. The mutex ensures only one task writes at a time.

**Why higher priority for Alarm Task?**
Safety-critical alerts must preempt lower-priority tasks immediately. If the temperature is dangerously high, the alarm should not be delayed by display or UART operations.

---

## 🎯 Skills Demonstrated

`FreeRTOS` `RTOS` `Embedded Systems` `C` `Multitasking` `Queue` `Mutex` `Semaphore` `Task Scheduling` `Embedded Software Architecture` `MinGW` `Real-Time Systems`

---

## 📄 License

MIT License
