#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "event_groups.h"

#define TASK_STACk_SIZE 128
/* ����A�¼���־λ��0λ��B�¼���־λ��1λ */
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

    /* 1.�����¼���-Ĭ���¼���û�����ã��������ñ�־λ�����������ȡ*/
    eventGroupHandle = xEventGroupCreate();
    if(!eventGroupHandle) {
        printf("eventGroupHandle error\r\n"); return;
    }
    // �ȴ�ӡA,��A������Ҫ��ȡA��־λ����Ҫ������A��־λ
    setEvent(ATASK_PRINT_EVENT);

    /* 2.������������ֱ��ӡA�ʹ�ӡB */
    if(xTaskCreate(taskAFun,"taskA",TASK_STACk_SIZE,NULL,osPriorityNormal,&taskAHandle) != pdPASS) {
        printf("create taskA error\r\n"); return;
    }
    if(xTaskCreate(taskBFun,"taskA",TASK_STACk_SIZE,NULL,osPriorityNormal,&taskBHandle) != pdPASS) {
        printf("create taskB error\r\n"); return;
    }
}
