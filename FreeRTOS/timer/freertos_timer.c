#include "FreeRTOS.h"
#include "timers.h"
#include <stdio.h>

void timerCallbackFunction (TimerHandle_t xTimer) {
    uint32_t timerId = *(uint32_t *)pvTimerGetTimerID(xTimer);
    printf("timer ID:%d timeout\r\n",timerId);
}

/* �Զ���һ����ʱ���ӿ�-��ʱ�������𴴽�����ʼ������������ */
void freertos_timer_init(void) {
    TimerHandle_t timerHander;
    uint32_t pdtimerID;
    BaseType_t ret;
    // 1.������ʱ������
    timerHander = xTimerCreate("timer1",1000,pdTRUE,&pdtimerID,
                              timerCallbackFunction);
    if(!timerHander){
        printf("Fail to xTimerCreate for timer1\r\n");
        return;
    }
    // 2.������ʱ������
    ret = xTimerStart(timerHander,1000);
    if(ret != pdPASS){
        printf("Fail to xTimerStart\r\n");
        return;
    }
        
    return;
}
