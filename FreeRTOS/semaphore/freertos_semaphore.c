#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "semphr.h"

#define TASK_STACk_SIZE 128

TaskHandle_t taskAHandle;
TaskHandle_t taskBHandle;
SemaphoreHandle_t semaphA;
SemaphoreHandle_t semaphB;

void P(SemaphoreHandle_t semaphHandle) {
    if(xSemaphoreTake(semaphHandle,portMAX_DELAY) != pdTRUE) {
        printf("xSemaphoreTake error!\r\n");
        return;
    }
}

void V(SemaphoreHandle_t semaphHandle) {
    if(xSemaphoreGive(semaphHandle) != pdTRUE) {
        printf("xSemaphoreGive error!\r\n");
        return;
    }
}

void taskAFun(void *arg) {
    while(1) {
        // ����A��ʼ���ź���Ϊ1��BΪ0���Ȼ�ȡA��Դ����ӡA
        P(semaphA); // P����ȡ��Դ��-1
        printf("A\r\n");
        V(semaphB);  // V: �ͷ���Դ��+1
    }
}

void taskBFun(void *arg) {
    while(1) {
        P(semaphB);
        printf("B\r\n");
        V(semaphA);
    }
}

void freertos_semaphore_init(void) {
    /* 1.�ȴ��������ź���- �������ź���*/
    semaphA = xSemaphoreCreateCounting(1,1);
    if(!semaphA) {
        printf("create semaphA error!\r\n");
        return;
    }
    semaphB = xSemaphoreCreateCounting(1,0);
    if(!semaphB) {
        printf("create semaphB error!\r\n");
        return;
    }

    /* 2.��̬������������ */
    if(xTaskCreate(taskAFun,"taskA",TASK_STACk_SIZE,NULL,
                  osPriorityNormal,&taskAHandle) != pdPASS) {
        printf("create taskA error!\r\n");
        return;
    }
    if(xTaskCreate(taskBFun,"taskB",TASK_STACk_SIZE,NULL,
                  osPriorityNormal,&taskBHandle) != pdPASS) {
        printf("create taskB error!\r\n");
        return;
    }
}
