#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "usart.h"

#define TASK_STACk_SIZE 128

/* 创建的任务的句柄 */
osThreadId_t taskHandle;      // 指针类型
 TaskHandle_t taskHandleState;
osThreadId_t taskHandlePrint; // 指针类型
/* 任务分配的栈内存地址 */
StackType_t stackBuf[TASK_STACk_SIZE];
/* TCB内存地址 */
StaticTask_t staticTCBBuf;

/* 重写fputs函数-实现printf函数
在stm32的MicroLIB库中实现的printf函数最终是通过调用fputc函数输出数据
*/
int fputc(int ch, FILE *f) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
    return  EOF;
}

/* 自己创建的任务中要执行的函数 
typedef void (*TaskFunction_t)( void * );
*/
void taskFunction(void *arg) { // 要有参数-函数指针
    int i;
    for(i = 0; i < 3; i++) {
		printf("this is task1\r\n");
		osDelay(1000); // 取决于tick频率，本案例1ms
	}
    // 执行3秒后删除任务
    //vTaskDelete(taskHandleState); // 先删除别的任务
    // 执行3秒后挂起任务
    //vTaskSuspend(taskHandleState);
    // 执行3秒后恢复任务
    vTaskResume(taskHandleState);
    vTaskDelete(NULL);            // 删除自己任务
}

void taskFunctionStatic(void *arg) { // 要有参数-函数指针
    // 挂起当前任务
    printf("start running task_static\r\n");
    vTaskSuspend(NULL);
    while(1) {
		printf("this is task_staic\r\n");
		osDelay(1000); // 取决于tick频率，本案例1ms
	}
}

void showTaskFunction(void *arg) { // 要有参数-函数指针
    char pcWriteBuffer[150]; // 非静态，静态内存固定
    while(1) {
		vTaskList(pcWriteBuffer);
        printf("-----------------------------------------\r\n");
        printf("Name\t\tState\tPriority  Stack  Num\r\n");
        printf("%s\r\n",pcWriteBuffer);
        osDelay(1000); // 取决于tick频率，本案例1ms
	}
}

/* 创建自定义任务的总接口 */
void freertos_task_init(void) { // 要有void参数
    BaseType_t ret;
    /* 1.任务自动在堆区分配内存-xTaskCreate */
    ret = xTaskCreate(taskFunction, "task1", TASK_STACk_SIZE, NULL, 
                     osPriorityNormal, &taskHandle);
    if(ret != pdPASS) {
        printf("create freertos tesk error!\r\n");
        return;
    }
    /* 2.任务手动分配内存 */
    taskHandleState = xTaskCreateStatic(taskFunctionStatic,"task_staic",TASK_STACk_SIZE,NULL,
                                osPriorityNormal,stackBuf,&staticTCBBuf);
    if(!taskHandleState) {
        printf("creat freertos test_static error!\r\n");
        return;
    }

    /* 3.创建进程打印任务详细信息- vTaskList*/
    ret = xTaskCreate(showTaskFunction, "task_print", TASK_STACk_SIZE, NULL, 
                     osPriorityNormal, &taskHandlePrint);
    if(ret != pdPASS) {
        printf("create freertos task_print error!\r\n");
        return;
    }
}
