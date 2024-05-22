#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>

#define TASK_STACk_SIZE 128
static TaskHandle_t taskAHandle;
static TaskHandle_t taskBHandle;

void sendNotify(TaskHandle_t handle) {
    xTaskNotifyGive(handle);
}

void waitNotify(void ) {
    uint32_t ret;
    ret = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
    printf("notice:%d\r\n",ret);
}

static void taskAFun(void *arg) {
    while(1) {
        waitNotify();
        printf("task A print\r\n");
        sendNotify(taskBHandle);
    }
}

static void taskBFun(void *arg) {
    while(1) {
        waitNotify();
        printf("task B print\r\n");
        sendNotify(taskAHandle);
    }
}


void freertos_notice_init(void) {
    /* 创建两个任务-并触发对任务A的通知 */
    if(xTaskCreate(taskAFun,"taskA",TASK_STACk_SIZE,NULL,osPriorityAboveNormal,&taskAHandle) != pdPASS) {
        printf("create taskA error\r\n"); return;
    }
    if(xTaskCreate(taskBFun,"taskB",TASK_STACk_SIZE,NULL,osPriorityAboveNormal,&taskBHandle) != pdPASS) {
        printf("create taskB error\r\n"); return;
    }
    sendNotify(taskAHandle);
}
