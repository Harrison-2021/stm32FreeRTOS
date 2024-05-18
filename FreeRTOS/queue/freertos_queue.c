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

TaskHandle_t queSendTaskHandle; // 写队列指针
TaskHandle_t queRevTaskHandle;  // 读队列指针

/* 指向队列的句柄 */
QueueHandle_t queueHandle;
/* 队列中数据-结构体 */
typedef struct {
    uint32_t id;
    uint8_t data[DATA_MAX];
}QueueItem_t;

/* 向队列中写数据的任务回调函数*/
void queSendTaskFuc(void *arg) {
    int queId = 0;
    QueueItem_t item;
    while(1) {
        // 准备数据
        item.id = queId++;
        if(queId % QUEUE_LEN == 0) queId = 0; 
        sprintf((char *)item.data,"messager:%d",item.id);

        // 向队列中写入数据-向队列尾部写数据
        if(xQueueSend(queueHandle,&item,100)!= pdPASS ) {
            printf("Fail to xQueueSend!/r/n");
            break;
        }

        osPrintf("que_send %s\r\n",(char *)item.data);
        osDelay(1000);
    }

    vTaskDelete(NULL); // 当任务异常跳出循环时，要结束任务，免得影响其它线程任务
}

/* 读取队列消息的任务回调函数 */
void queRevTaskFuc(void *arg) {
    QueueItem_t item;
    while(1) {
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
    queueHandle = xQueueCreate(QUEUE_LEN, sizeof(QueueItem_t));
    if(!queueHandle) {
        printf("Fail to xQueueCreate!\r\n");
        return;
    }
    /* 创建读写队列的任务 */
    ret = xTaskCreate(queSendTaskFuc,"que_send",TASK_STACk_SIZE,NULL,
                      osPriorityNormal,&queSendTaskHandle);
    if(ret != pdPASS) {
        printf("create freertos queSendTask error!\r\n");
        return;
    }
    ret = xTaskCreate(queRevTaskFuc,"que_rev",TASK_STACk_SIZE,NULL,
                      osPriorityNormal,&queRevTaskHandle);
    if(ret != pdPASS) {
        printf("create freertos queSendTask error!\r\n");
        return;
    }
}
