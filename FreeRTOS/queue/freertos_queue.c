#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "usart.h"
#include "queue.h"

#define QUEUE_LEN 10
#define DATA_MAX  20
#define TASK_STACk_SIZE 128

// ...代表输入任意字符
// __VA_ARGS__代表函数中传入参数
#define osPrintf(...) do {\
    taskENTER_CRITICAL();\
    printf(__VA_ARGS__);\
    taskEXIT_CRITICAL();\
}while(0)

TaskHandle_t que1SendTaskHandle; // 写队列指针
TaskHandle_t que2SendTaskHandle; // 写队列指针
TaskHandle_t queRevTaskHandle;  // 读队列指针

/* 指向队列的句柄 */
QueueHandle_t queueHandle1;
QueueHandle_t queueHandle2;
/* 指向队列集的句柄 */
QueueSetHandle_t queSetHandle;

/* 队列中数据-结构体 */
typedef struct {
    uint32_t id;
    uint8_t data[DATA_MAX];
}QueueItem_t;

/* 向队列中写数据的任务回调函数-向队列1写数据*/
void que1SendTaskFuc(void *arg) {
    int queId = 0;
    QueueItem_t item;
    while(1) {
        // 准备数据
        item.id = queId++;
        if(queId % QUEUE_LEN == 0) queId = 0; 
        sprintf((char *)item.data,"messager:%d",item.id);

        // 向队列中写入数据-向队列尾部写数据
        if(xQueueSend(queueHandle1,&item,100)!= pdPASS ) {
            printf("Fail to xQueueSend1\r\n");
            break;
        }

        osPrintf("que1_send %s\r\n",(char *)item.data);
        osDelay(1000);
    }

    vTaskDelete(NULL); // 当任务异常跳出循环时，要结束任务，免得影响其它线程任务
}

/* 向队列中写数据的任务回调函数-向队列2写数据*/
void que2SendTaskFuc(void *arg) {
    int queId = 0;
    QueueItem_t item;
    while(1) {
        // 准备数据
        item.id = queId++;
        if(queId % QUEUE_LEN == 0) queId = 0; 
        sprintf((char *)item.data,"messager:%d",item.id);

        // 向队列中写入数据-向队列尾部写数据
        #if 1
        if(xQueueSend(queueHandle2,&item,100)!= pdPASS ) {
            printf("Fail to xQueueSend2!\r\n");
            break;
        }
        #endif

        osPrintf("que2_send %s\r\n",(char *)item.data);
        osDelay(1000);
    }

    vTaskDelete(NULL); // 当任务异常跳出循环时，要结束任务，免得影响其它线程任务
}

/* 读取队列消息的任务回调函数 */
void queSetRevTaskFuc(void *arg) {
    QueueItem_t item;
    QueueSetMemberHandle_t queueHandle;
    while(1) {
        // 从队列集中读取队列
        queueHandle = xQueueSelectFromSet(queSetHandle,portMAX_DELAY);
        if(!queueHandle) {
            printf("Fail to xQueueSelectFromSet!/r/n");
            break; 
        }

        if(xQueueReceive(queueHandle,&item,portMAX_DELAY) != pdPASS) {
            printf("Fail to xQueueReceive!/r/n");
            break; 
        }
        osPrintf("que_Rev %d : %s\r\n",item.id,(char *)item.data);
    }
    vTaskDelete(NULL); // 当任务异常跳出循环时，要结束任务，免得影响其它线程任务
}

void freertos_queue_init(void) {
    BaseType_t ret;
    /* 创建队列和队列集 */
    queueHandle1 = xQueueCreate(QUEUE_LEN, sizeof(QueueItem_t));
    if(!queueHandle1) {
        printf("Fail to xQueueCreate que1!\r\n");
        return;
    }
    queueHandle2 = xQueueCreate(QUEUE_LEN, sizeof(QueueItem_t));
    if(!queueHandle2) {
        printf("Fail to xQueueCreate que2!\r\n");
        return;
    }
    queSetHandle = xQueueCreateSet(QUEUE_LEN + QUEUE_LEN);
    if(!queSetHandle) {
        printf("Fail to xQueueCreate queSet!\r\n");
        return;
    }
    /* 将队列加入队列集 */
    if(xQueueAddToSet(queueHandle1,queSetHandle) != pdTRUE) {
        printf("Fail to xQueueAddToSet1!\r\n");
        return;
    }
    if(xQueueAddToSet(queueHandle2,queSetHandle) != pdTRUE) {
        printf("Fail to xQueueAddToSet2!\r\n");
        return;
    }
    /* 创建三个任务-两个任务分别向两个队列写数据，一个任务从队列集中读数据*/
    ret = xTaskCreate(que1SendTaskFuc,"que1_send",TASK_STACk_SIZE,NULL,
                      osPriorityNormal,&que1SendTaskHandle);
    if(ret != pdPASS) {
        printf("create freertos que1SendTask error!\r\n");
        return;
    }
    ret = xTaskCreate(que2SendTaskFuc,"que2_send",TASK_STACk_SIZE,NULL,
                      osPriorityNormal,&que2SendTaskHandle);
    if(ret != pdPASS) {
        printf("create freertos que2SendTask error!\r\n");
        return;
    }
    ret = xTaskCreate(queSetRevTaskFuc,"queSet_rev",TASK_STACk_SIZE,NULL,
                      osPriorityNormal,&queRevTaskHandle);
    if(ret != pdPASS) {
        printf("create freertos queSetRevTask error!\r\n");
        return;
    }
}
