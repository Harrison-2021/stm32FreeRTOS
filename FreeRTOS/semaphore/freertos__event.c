#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "event_groups.h"

#define TASK_STACk_SIZE 128
/* 定义A事件标志位：0位，B事件标志位：1位 */
#define ATASK_PRINT_EVENT (1 << 0)
#define BTASK_PRINT_EVENT (1 << 1)

EventGroupHandle_t eventGroupHandle;

void setEvent(const EventBits_t  uxBitsToSet) {
    xEventGroupSetBits(eventGroupHandle,uxBitsToSet);
}

void waitEvent(const EventBits_t  uxBitsToWaitFor) {
    xEventGroupWaitBits(eventGroupHandle,uxBitsToWaitFor,pdTRUE,pdFALSE,portMAX_DELAY);
}

static void taskAFun(void *arg) {
    while(1) {
        waitEvent(ATASK_PRINT_EVENT);
        printf("TaskA print\r\n");
        setEvent(BTASK_PRINT_EVENT);
    }
}

static void taskBFun(void *arg) {
    while(1) {
        waitEvent(BTASK_PRINT_EVENT);
        printf("TaskB print\r\n");
        setEvent(ATASK_PRINT_EVENT);
    }
}

void freertos_event_init(void) {
    TaskHandle_t taskAHandle;
    TaskHandle_t taskBHandle;

    /* 1.创建事件组-默认事件都没有设置，可先设置标志位，便于任务获取*/
    eventGroupHandle = xEventGroupCreate();
    if(!eventGroupHandle) {
        printf("eventGroupHandle error\r\n"); return;
    }
    // 先打印A,即A任务需要获取A标志位，需要先设置A标志位
    setEvent(ATASK_PRINT_EVENT);

    /* 2.创建两个任务分别打印A和打印B */
    if(xTaskCreate(taskAFun,"taskA",TASK_STACk_SIZE,NULL,osPriorityNormal,&taskAHandle) != pdPASS) {
        printf("create taskA error\r\n"); return;
    }
    if(xTaskCreate(taskBFun,"taskA",TASK_STACk_SIZE,NULL,osPriorityNormal,&taskBHandle) != pdPASS) {
        printf("create taskB error\r\n"); return;
    }
}
