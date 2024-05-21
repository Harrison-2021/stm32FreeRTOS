#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "semphr.h"
#include "stm32f1xx_hal.h"

#define TASK_STACk_SIZE 128
SemaphoreHandle_t semaphoreBinary;  // 二值信号量
SemaphoreHandle_t semaphoreMutex;   // 互斥信号量-可实现优先级继承
static TaskHandle_t taskAHandle;
static TaskHandle_t taskBHandle;
static TaskHandle_t taskCHandle;

static void taskAFun(void *args) {
    osDelay(2000); // A优先级最高，但让出CPU,2秒后再抢占执行
    printf("taskA start running\r\n");
    #if 0
    if(xSemaphoreTake(semaphoreBinary,portMAX_DELAY) != pdTRUE) {
        printf("taskA xSemaphoreTake error\r\n");
        return;
    }
    printf("taskA take semaphore\r\n");
    printf("taskA print\r\n");
    if(xSemaphoreGive(semaphoreBinary) != pdTRUE) {
        printf("taskA xSemaphoreGive error\r\n");
        return;
    }
    #endif
    if(xSemaphoreTake(semaphoreMutex,portMAX_DELAY) != pdTRUE) {
        printf("taskA xSemaphoreTake error\r\n");
        return;
    }
    printf("taskA take semaphore\r\n");
    printf("taskA print\r\n");
    if(xSemaphoreGive(semaphoreMutex) != pdTRUE) {
        printf("taskA xSemaphoreGive error\r\n");
        return;
    }
    vTaskDelete(NULL);
}

static void taskBFun(void *args) {
    int i;
    printf("taskB start running\r\n");

    // 打印B时，使用信号量，先获取信号量，打印10次，再释放信号量
    #if 0
    if(xSemaphoreTake(semaphoreBinary,portMAX_DELAY) != pdTRUE) {
        printf("taskB xSemaphoreTake error\r\n");
        return;
    }
    printf("taskB take semaphore\r\n");
    for(i = 0; i < 10; i++) {
        printf("taskB print\r\n");
        HAL_Delay(1000); // 注意不能使用osDelay(会从就绪列表迁移到延时列表，阻塞，让出CPU执行权)
    }
    if(xSemaphoreGive(semaphoreBinary) != pdTRUE) {
        printf("taskB xSemaphoreGive error\r\n");
        return;
    }
    #endif
    if(xSemaphoreTake(semaphoreMutex,portMAX_DELAY) != pdTRUE) {
        printf("taskB xSemaphoreTake error\r\n");
        return;
    }
    printf("taskB take semaphore\r\n");
    for(i = 0; i < 10; i++) {
        printf("taskB print\r\n");
        HAL_Delay(1000); // 注意不能使用osDelay(会从就绪列表迁移到延时列表，阻塞，让出CPU执行权)
    }
    if(xSemaphoreGive(semaphoreMutex) != pdTRUE) {
        printf("taskB xSemaphoreGive error\r\n");
        return;
    }
    vTaskDelete(NULL);
    
}

static void taskCFun(void *args) {
    int i;
    osDelay(5000);
    printf("taskC start running\r\n");
    for(i = 0; i < 3; i++) {
        printf("taskC print\r\n");
        HAL_Delay(1000);
    }
    vTaskDelete(NULL);

}

void freertos_priority_reverse_init(void) {
    /* 创建二值信号量-注意创建后默认为0，要先释放信号量 */
    #if 0
    semaphoreBinary = xSemaphoreCreateBinary();
    if(!semaphoreBinary) {
        printf("xSemaphoreCreateBinary error\r\n");
        return;
    }
    if(xSemaphoreGive(semaphoreBinary) != pdTRUE) {
        printf("xSemaphoreGive error\r\n");
        return;
    }
    #endif
    /* 互斥信号量，初始为1，无需先释放 */
    semaphoreMutex = xSemaphoreCreateMutex();
    if(!semaphoreMutex) {
        printf("semaphoreMutex error\r\n"); return;
    }
   
    /* 创建三个任务,优先级A>C>B */
    if(xTaskCreate(taskAFun,"taskA",TASK_STACk_SIZE,NULL,
                osPriorityNormal2,&taskAHandle) != pdPASS) {
        printf("Create taskA error\r\n");return;
    }
    if(xTaskCreate(taskBFun,"taskB",TASK_STACk_SIZE,NULL,
                osPriorityNormal,&taskBHandle) != pdPASS) {
        printf("Create taskB error\r\n");return;
    }
    if(xTaskCreate(taskCFun,"taskC",TASK_STACk_SIZE,NULL,
                osPriorityNormal1,&taskCHandle) != pdPASS) {
        printf("Create taskC error\r\n");return;
    }
}
