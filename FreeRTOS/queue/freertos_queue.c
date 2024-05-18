#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "usart.h"
#include "queue.h"

#define QUEUE_LEN 10
#define DATA_MAX  20
#define TASK_STACk_SIZE 128

// ...�������������ַ�
// __VA_ARGS__�������д������
#define osPrintf(...) do {\
    taskENTER_CRITICAL();\
    printf(__VA_ARGS__);\
    taskEXIT_CRITICAL();\
}while(0)

TaskHandle_t queSendTaskHandle; // д����ָ��
TaskHandle_t queRevTaskHandle;  // ������ָ��

/* ָ����еľ�� */
QueueHandle_t queueHandle;
/* ����������-�ṹ�� */
typedef struct {
    uint32_t id;
    uint8_t data[DATA_MAX];
}QueueItem_t;

/* �������д���ݵ�����ص�����*/
void queSendTaskFuc(void *arg) {
    int queId = 0;
    QueueItem_t item;
    while(1) {
        // ׼������
        item.id = queId++;
        if(queId % QUEUE_LEN == 0) queId = 0; 
        sprintf((char *)item.data,"messager:%d",item.id);

        // �������д������-�����β��д����
        if(xQueueSend(queueHandle,&item,100)!= pdPASS ) {
            printf("Fail to xQueueSend!/r/n");
            break;
        }

        osPrintf("que_send %s\r\n",(char *)item.data);
        osDelay(1000);
    }

    vTaskDelete(NULL); // �������쳣����ѭ��ʱ��Ҫ�����������Ӱ�������߳�����
}

/* ��ȡ������Ϣ������ص����� */
void queRevTaskFuc(void *arg) {
    QueueItem_t item;
    while(1) {
        if(xQueueReceive(queueHandle,&item,portMAX_DELAY) != pdPASS) {
            printf("Fail to xQueueReceive!/r/n");
            break; 
        }
        osPrintf("que_Rev %d : %s\r\n",item.id,(char *)item.data);
    }
    vTaskDelete(NULL); // �������쳣����ѭ��ʱ��Ҫ�����������Ӱ�������߳�����
}

void freertos_queue_init(void) {
    BaseType_t ret;
    queueHandle = xQueueCreate(QUEUE_LEN, sizeof(QueueItem_t));
    if(!queueHandle) {
        printf("Fail to xQueueCreate!\r\n");
        return;
    }
    /* ������д���е����� */
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
