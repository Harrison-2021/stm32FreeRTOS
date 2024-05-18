#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "usart.h"

#define TASK_STACk_SIZE 128

/* ����������ľ��-ע�ⲻ��osThreadId_t-ɾ�����������޷�����*/
TaskHandle_t taskHandle;        // ָ������
TaskHandle_t taskHandleState;
TaskHandle_t taskHandlePrint;   // ָ������

/* ��������ջ�ڴ��ַ */
StackType_t stackBuf[TASK_STACk_SIZE];
/* TCB�ڴ��ַ */
StaticTask_t staticTCBBuf;

/* ��дfputs����-ʵ��printf����
��stm32��MicroLIB����ʵ�ֵ�printf����������ͨ������fputc�����������
*/
int fputc(int ch, FILE *f) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
    return  EOF;
}

/* �Լ�������������Ҫִ�еĺ��� 
typedef void (*TaskFunction_t)( void * );
*/
void taskFunction(void *arg) { // Ҫ�в���-����ָ��
    int i;
    for(i = 0; i < 3; i++) {
		printf("this is task1\r\n");
		osDelay(1000); // ȡ����tickƵ�ʣ�������1ms
	}
    // ִ��3���ɾ������
    //vTaskDelete(taskHandleState); // ��ɾ���������
    // ִ��3����������
    //vTaskSuspend(taskHandleState);
    // ִ��3���ָ�����
    vTaskResume(taskHandleState);
    vTaskDelete(NULL);            // ɾ���Լ�����
}

void taskFunctionStatic(void *arg) { // Ҫ�в���-����ָ��
    // ����ǰ����
    printf("start running task_static\r\n");
    vTaskSuspend(NULL);
    while(1) {
		printf("this is task_staic\r\n");
		osDelay(1000); // ȡ����tickƵ�ʣ�������1ms
	}
}

void showTaskFunction(void *arg) { // Ҫ�в���-����ָ��
    char pcWriteBuffer[150]; // �Ǿ�̬����̬�ڴ�̶�
    //TickType_t xLastWakeTime;
    //xLastWakeTime = xTaskGetTickCount();//��ȡ��ǰʱ��
    while(1) {
		vTaskList(pcWriteBuffer);
        printf("-----------------------------------------\r\n");
        printf("Name\t\tState\tPriority  Stack  Num\r\n");
        printf("%s\r\n",pcWriteBuffer);
        /* �����ʱ������������жϣ��ӳ�ʱ�䲻�̶� */
        osDelay(1000); // ȡ����tickƵ�ʣ�������1ms
        /* ������ʱ����������ʵ�ʵ�ʱ����������������� */
        //vTaskDelayUntil(&xLastWakeTime,1000);
	}
}

/* �����Զ���������ܽӿ� */
void freertos_task_init(void) { // Ҫ��void����
    BaseType_t ret;
    /* 1.�����Զ��ڶ��������ڴ�-xTaskCreate */
    ret = xTaskCreate(taskFunction, "task1", TASK_STACk_SIZE, NULL, 
                     osPriorityNormal, &taskHandle);
    if(ret != pdPASS) {
        printf("create freertos tesk error!\r\n");
        return;
    }
    /* 2.�����ֶ������ڴ� */
    taskHandleState = xTaskCreateStatic(taskFunctionStatic,"task_staic",TASK_STACk_SIZE,NULL,
                                osPriorityNormal,stackBuf,&staticTCBBuf);
    if(!taskHandleState) {
        printf("creat freertos test_static error!\r\n");
        return;
    }

    /* 3.�������̴�ӡ������ϸ��Ϣ- vTaskList*/
    ret = xTaskCreate(showTaskFunction, "task_print", TASK_STACk_SIZE, NULL, 
                     osPriorityNormal, &taskHandlePrint);
    if(ret != pdPASS) {
        printf("create freertos task_print error!\r\n");
        return;
    }
}
