# 项目介绍

- 项目旨在使用FreeTROS完成在stm32中进行多任务控制；并学习FreeRTOS系统架构设计，研究Tickless低功耗模式控制、内存管理deng

# 项目模块

## [1.FreeRTOS架构](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/1.FreeRTOS%E4%BB%8B%E7%BB%8D.md)

- FreeRTOS特点；
- STM32 CubeMX配置FreeRTOS；
- FreeRTOS源码概述（入口代码，命名规范，数据类型）；
- FreeRTOS默认任务分析（环境初始化，执行默认任务，执行任务调度，空闲函数执行）。

## [2.FreeRTOS任务管理](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/2.FreeRTOS%E4%BB%BB%E5%8A%A1%E7%AE%A1%E7%90%86.md)

- 任务创建与删除(xTaskCreate，xTaskCreateStatic，创建过程分析（分配空间，初始化TCB，根据优先级添加到就绪列表中），vTaskList，vTaskDelete，任务删除过程分析)；
- 任务挂起和恢复（vTaskSuspend，vTaskResume）；
- 任务状态转换（运行态，就绪态，阻塞态，挂起态）；
- 任务状态转换（运行态，就绪态，阻塞态，挂起态）；
- 任务调度（调度规则（抢占式，时间片），任务调度的本质，PendSV中断触发，PendSV上下文切换）；
- 任务延时（相对延时函数vTaskDelay，绝对延时函数vTaskDelayUntil）。

## [3.RreeRTOS软件定时器](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/3.RreeRTOS%E8%BD%AF%E4%BB%B6%E5%AE%9A%E6%97%B6%E5%99%A8.md)

- 软件定时器特点与使用场景；
- FreeRTOS软件定时器特点（可裁剪，单次和周期）；
- 软件定时器服务任务（软件定时器的命令队列）；
- 软件定时器的状态（休眠态与运行态）；
- 单次定时器和周期定时器；

## [4.FreeRTOS消息队列](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/4.FreeRTOS%E6%B6%88%E6%81%AF%E9%98%9F%E5%88%97.md)

- 消息队列的特点（FIFO，数据传递方式，出队与入队阻塞）；
- 队列结构体（队列，信号量，内存分配）；
- 队列创建（动态方式，静态方式，队列的类型）；
- 队列读写接口使用（屏蔽中断方式解决并发问题）；队列集使用。



## [5.FreeRTOS同步与互斥](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/5.FreeRTOS%E5%90%8C%E6%AD%A5%E4%B8%8E%E4%BA%92%E6%96%A5.md)

- 信号量（种类，本质与区别）；优先级翻/反转和优先级继承；
- 事件标志组（与队列、信号量区别，API接口）；
- 任务通知（任务通知特点，任务通知值和通知状态，优劣势）。

## [6.FreeRTOS之Tickless低功耗模式](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/6.FreeRTOS%E4%B9%8BTickless%E4%BD%8E%E5%8A%9F%E8%80%97%E6%A8%A1%E5%BC%8F.md)

- STM32电源管理（电源种类，管理系统，备份域电路，调压器供电电路，ADC电源及参考电压）；
- STM32中断与事件（外部中断，DMA事件，产生过程分析）；
- STM32的低功耗模式（模式种类（睡眠模式，停止模式，待机模式），低功耗模式分析，WFI和WFE指令）；
- FreeRTOS Tickless模式降低功耗；
- FreeRTOS  Tickless模式具体实现（启动低功耗 tickless 模式，设置低功耗模式的时间，在进入与退出Tickless模式时增加代码，通常是关闭外设，HAL库嘀嗒定时器等）。

## [7.FreeRTOS之内存管理](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/7.FreeRTOS%E4%B9%8B%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86.md)

- 动态创建和静态创建；
- 不使用malloc()和free()原因；
- FreeRTOS内存管理算法；
- FreeRTOS内存管理API使用。

# 模块测试结果展示

## [2.FreeRTOS任务管理](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/2.FreeRTOS%E4%BB%BB%E5%8A%A1%E7%AE%A1%E7%90%86.md)

### 1. 任务创建与删除

#### xTaskCreate

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/79f1cb25add04cc8a7077d9d6b71fbc9.png)

#### 2.xTaskCreateStatic

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/88028bcccb7549c49ea13247861e2ce8.png)

#### 3.vTaskList

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/ea1ad67d1fe74a55962d85fd73874dc1.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/2f02160810ab470ab44cd552664806f4.png)

#### 4.vTaskDelete

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/80517f67b6174d968104b01d0b350cd4.png)

### 2. 任务挂起和恢复

#### 1.vTaskSuspend

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/a1614d66f5e94ad69e36565109f7698f.png)

#### 2.vTaskResume

```c
void taskFunctionStatic(void *arg) { // 要有参数-函数指针
    // 挂起当前任务
    printf("start running task_static\r\n");
    vTaskSuspend(NULL);
    while(1) {
		printf("this is task_staic\r\n");
		osDelay(1000); // 取决于tick频率，本案例1ms
	}
}

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

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/f0833c552c4640468540f17e7c0c15c9.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/a7945cc175b243e8a0ffe6e6aec231b2.png)

## [3.RreeRTOS软件定时器](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/3.RreeRTOS%E8%BD%AF%E4%BB%B6%E5%AE%9A%E6%97%B6%E5%99%A8.md)

```c
#include "FreeRTOS.h"
#include "timers.h"
#include <stdio.h>

void timerCallbackFunction (TimerHandle_t xTimer) {
    uint32_t timerId = *(uint32_t *)pvTimerGetTimerID(xTimer);
    printf("timer ID:%d timeout\r\n",timerId);
}

/* 自定义一个定时器接口-向定时器任务发起创建，开始，结束等命令 */
void freertos_timer_init(void) {
    TimerHandle_t timerHander;
    uint32_t pdtimerID;
    BaseType_t ret;
    // 1.创建定时器任务
    timerHander = xTimerCreate("timer1",1000,pdTRUE,&pdtimerID,
                              timerCallbackFunction);
    if(!timerHander){
        printf("Fail to xTimerCreate for timer1\r\n");
        return;
    }
    // 2.启动定时器任务
    ret = xTimerStart(timerHander,1000);
    if(ret != pdPASS){
        printf("Fail to xTimerStart\r\n");
        return;
    }
        
    return;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/77521d94414b4e858c485f7640f893aa.png)

## [4.FreeRTOS消息队列](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/4.FreeRTOS%E6%B6%88%E6%81%AF%E9%98%9F%E5%88%97.md)

```c
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
        sprintf((char *)item.data,"messager:%d",item.id); // 将id写入data中

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
        if(xQueueSend(queueHandle2,&item,100)!= pdPASS ) {
            printf("Fail to xQueueSend2!\r\n");
            break;
        }

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
	// 读取有数据的消息队列
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

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/e57952dfe9b24318bd5f4ecce3fa2c58.png)

## [5.FreeRTOS同步与互斥](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/5.FreeRTOS%E5%90%8C%E6%AD%A5%E4%B8%8E%E4%BA%92%E6%96%A5.md)

### 1. 使用信号量控制同步

```c
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
        // 先让A初始化信号量为1，B为0，先获取A资源，打印A
        P(semaphA); // P：获取资源：-1
        printf("A\r\n");
        V(semaphB);  // V: 释放资源：+1
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
    /* 1.先创建两个信号量- 计数型信号量*/
    semaphA = xSemaphoreCreateCounting(1,1); // 初始化1
    if(!semaphA) {
        printf("create semaphA error!\r\n");
        return;
    }
    semaphB = xSemaphoreCreateCounting(1,0);// 初始化0
    if(!semaphB) {
        printf("create semaphB error!\r\n");
        return;
    }

    /* 2.动态创建两个任务 */
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

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/ab5d506f311146f88e0ee59d6e5359bd.png)

### 2. 解决优先级反转的代码实现

```c
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "semphr.h"
#include "stm32f1xx_hal.h"

#define TASK_STACk_SIZE 128
SemaphoreHandle_t semaphoreBinary;  // 二值信号量
SemaphoreHandle_t semaphoreMutex;   // 互斥信号量-可实现优先级继承
static TaskHandle_t taskAHandle;
static TaskHandle_t taskBHandle;
static TaskHandle_t taskCHandle;

static void taskAFun(void *args) {
    osDelay(2000); // A优先级最高，但让出CPU,2秒后再抢占执行
    printf("taskA start running\r\n");
   
    if(xSemaphoreTake(semaphoreMutex,portMAX_DELAY) != pdTRUE) {
        printf("taskA xSemaphoreTake error\r\n");
        return;
    }
    printf("taskA take semaphore\r\n");
    printf("taskA print\r\n");
    if(xSemaphoreGive(semaphoreMutex) != pdTRUE) {
        printf("taskA xSemaphoreGive error\r\n");
        return;
    }
    vTaskDelete(NULL);
}

static void taskBFun(void *args) {
    int i;
    printf("taskB start running\r\n");

    // 打印B时，使用信号量，先获取信号量，打印10次，再释放信号量
    if(xSemaphoreTake(semaphoreMutex,portMAX_DELAY) != pdTRUE) {
        printf("taskB xSemaphoreTake error\r\n");
        return;
    }
    printf("taskB take semaphore\r\n");
    for(i = 0; i < 10; i++) {
        printf("taskB print\r\n");
        HAL_Delay(1000); // 注意不能使用osDelay(会从就绪列表迁移到延时列表，阻塞，让出CPU执行权)
    }
    if(xSemaphoreGive(semaphoreMutex) != pdTRUE) {
        printf("taskB xSemaphoreGive error\r\n");
        return;
    }
    vTaskDelete(NULL);
    
}

static void taskCFun(void *args) {
    int i;
    osDelay(5000);
    printf("taskC start running\r\n");
    for(i = 0; i < 3; i++) {
        printf("taskC print\r\n");
        HAL_Delay(1000);
    }
    vTaskDelete(NULL);

}

void freertos_priority_reverse_init(void) {
   
    /* 互斥信号量，初始为1，无需先释放 */
    semaphoreMutex = xSemaphoreCreateMutex();
    if(!semaphoreMutex) {
        printf("semaphoreMutex error\r\n"); return;
    }
   
    /* 创建三个任务,优先级A>C>B */
    if(xTaskCreate(taskAFun,"taskA",TASK_STACk_SIZE,NULL,
                osPriorityNormal2,&taskAHandle) != pdPASS) {
        printf("Create taskA error\r\n");return;
    }
    if(xTaskCreate(taskBFun,"taskB",TASK_STACk_SIZE,NULL,
                osPriorityNormal,&taskBHandle) != pdPASS) {
        printf("Create taskB error\r\n");return;
    }
    if(xTaskCreate(taskCFun,"taskC",TASK_STACk_SIZE,NULL,
                osPriorityNormal1,&taskCHandle) != pdPASS) {
        printf("Create taskC error\r\n");return;
    }
}

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/ef07fcbee42a4fdca25218c028579c8a.png)

### 3. 事件标志组-实现AB同步打印

```c
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "event_groups.h"

#define TASK_STACk_SIZE 128
/* 定义A事件标志位：0位，B事件标志位：1位 */
#define ATASK_PRINT_EVENT (1 << 0)
#define BTASK_PRINT_EVENT (1 << 1)

EventGroupHandle_t eventGroupHandle;

void setEvent(const EventBits_t uxBitsToSet) {
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

    /* 1.创建事件组-默认事件都没有设置，可先设置标志位，便于任务获取*/
    eventGroupHandle = xEventGroupCreate();
    if(!eventGroupHandle) {
        printf("eventGroupHandle error\r\n"); return;
    }
    // 先打印A,即A任务需要获取A标志位，需要先设置A标志位
    setEvent(ATASK_PRINT_EVENT);

    /* 2.创建两个任务分别打印A和打印B */
    if(xTaskCreate(taskAFun,"taskA",TASK_STACk_SIZE,NULL,osPriorityNormal,&taskAHandle) != pdPASS) {
        printf("create taskA error\r\n"); return;
    }
    if(xTaskCreate(taskBFun,"taskA",TASK_STACk_SIZE,NULL,osPriorityNormal,&taskBHandle) != pdPASS) {
        printf("create taskB error\r\n"); return;
    }
}

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/4360c58b129c4f009674cd0007723a63.png)

### 4. 任务通知

```c
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

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/886d9388f9574062ad4835d6570d187b.png)

## [6.FreeRTOS之Tickless低功耗模式](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/6.FreeRTOS%E4%B9%8BTickless%E4%BD%8E%E5%8A%9F%E8%80%97%E6%A8%A1%E5%BC%8F.md)

```c
__weak void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
{
    ...
		// 进入低功耗模式之前调用
                configPRE_SLEEP_PROCESSING( xModifiableIdleTime ); (9)
                if( xModifiableIdleTime > 0 )
                {
                        __dsb( portSY_FULL_READ_WRITE );
                        __wfi(); (10)  // WFI指令进入低功耗模式
                        __isb( portSY_FULL_READ_WRITE );
                }
                    //当代码执行到这里的时候说明已经退出了低功耗模式！
                configPOST_SLEEP_PROCESSING( xExpectedIdleTime ); (11)
    ...
}
```



```c
/* USER CODE BEGIN PREPOSTSLEEP */
__weak void PreSleepProcessing(uint32_t *ulExpectedIdleTime)  // 参数，进入低功耗模式持续时间
{
        printf("Enter tickless mode\r\n");
         
        //进入休眠前，关闭外设等
        __HAL_RCC_GPIOA_CLK_DISABLE();
        __HAL_RCC_GPIOB_CLK_DISABLE();
        __HAL_RCC_GPIOC_CLK_DISABLE();
        __HAL_RCC_GPIOD_CLK_DISABLE(); 
        __HAL_RCC_GPIOE_CLK_DISABLE();
        HAL_SuspendTick();// 将HAL库嘀嗒定时器关掉，防止睡眠模式被任何中断唤醒
}
 
__weak void PostSleepProcessing(uint32_t *ulExpectedIdleTime)
{
        //退出休眠，开启外设等
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();
        
       printf("Exit tickless mode\r\n");
       HAL_ResumeTick();
}
/* USER CODE END PREPOSTSLEEP */
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/83bda4ac17fa448796a3925347215b36.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a0b7523371044bf6b3d23ef20731f598.png)

## [7.FreeRTOS之内存管理](https://github.com/Harrison-2021/stm32FreeRTOS/blob/master/notes/7.FreeRTOS%E4%B9%8B%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86.md)

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/6e4909606703414baf37dc6b6ba12f54.png)



![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/b6abe1607e6a4265ab9726b41d353cda.png)
