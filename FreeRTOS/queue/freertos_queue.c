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

TaskHandle_t que1SendTaskHandle; // д����ָ��
TaskHandle_t que2SendTaskHandle; // д����ָ��
TaskHandle_t queRevTaskHandle;  // ������ָ��

/* ָ����еľ�� */
QueueHandle_t queueHandle1;
QueueHandle_t queueHandle2;
/* ָ����м��ľ�� */
QueueSetHandle_t queSetHandle;

/* ����������-�ṹ�� */
typedef struct {
    uint32_t id;
    uint8_t data[DATA_MAX];
}QueueItem_t;

/* �������д���ݵ�����ص�����-�����1д����*/
void que1SendTaskFuc(void *arg) {
    int queId = 0;
    QueueItem_t item;
    while(1) {
        // ׼������
        item.id = queId++;
        if(queId % QUEUE_LEN == 0) queId = 0; 
        sprintf((char *)item.data,"messager:%d",item.id);

        // �������д������-�����β��д����
        if(xQueueSend(queueHandle1,&item,100)!= pdPASS ) {
            printf("Fail to xQueueSend1\r\n");
            break;
        }

        osPrintf("que1_send %s\r\n",(char *)item.data);
        osDelay(1000);
    }

    vTaskDelete(NULL); // �������쳣����ѭ��ʱ��Ҫ�����������Ӱ�������߳�����
}

/* �������д���ݵ�����ص�����-�����2д����*/
void que2SendTaskFuc(void *arg) {
    int queId = 0;
    QueueItem_t item;
    while(1) {
        // ׼������
        item.id = queId++;
        if(queId % QUEUE_LEN == 0) queId = 0; 
        sprintf((char *)item.data,"messager:%d",item.id);

        // �������д������-�����β��д����
        #if 1
        if(xQueueSend(queueHandle2,&item,100)!= pdPASS ) {
            printf("Fail to xQueueSend2!\r\n");
            break;
        }
        #endif

        osPrintf("que2_send %s\r\n",(char *)item.data);
        osDelay(1000);
    }

    vTaskDelete(NULL); // �������쳣����ѭ��ʱ��Ҫ�����������Ӱ�������߳�����
}

/* ��ȡ������Ϣ������ص����� */
void queSetRevTaskFuc(void *arg) {
    QueueItem_t item;
    QueueSetMemberHandle_t queueHandle;
    while(1) {
        // �Ӷ��м��ж�ȡ����
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
    vTaskDelete(NULL); // �������쳣����ѭ��ʱ��Ҫ�����������Ӱ�������߳�����
}

void freertos_queue_init(void) {
    BaseType_t ret;
    /* �������кͶ��м� */
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
    /* �����м�����м� */
    if(xQueueAddToSet(queueHandle1,queSetHandle) != pdTRUE) {
        printf("Fail to xQueueAddToSet1!\r\n");
        return;
    }
    if(xQueueAddToSet(queueHandle2,queSetHandle) != pdTRUE) {
        printf("Fail to xQueueAddToSet2!\r\n");
        return;
    }
    /* ������������-��������ֱ�����������д���ݣ�һ������Ӷ��м��ж�����*/
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
