#include "scheduler.h"

/* 任务结构体定义 */
typedef struct
{
    void (*task_func)(void); // 任务函数指针
    uint32_t rate_ms;        // 任务执行周期(ms)
    uint32_t last_run;       // 上次执行时间戳
} task_t;

/* 任务数量 */
uint8_t task_num;

/* 任务列表初始化 */
static task_t scheduler_task[] = {
    {OLED_Proc,     100,  0},  // OLED 显示任务(100 ms)
    {DS1302_Proc,   1000, 0},  // DS1302 时钟任务(1000 ms)
    {MAX30102_Proc, 10,   0},  // MAX30102 传感器任务(10 ms)
    {MLX90614_Proc, 500,  0},  // MLX90614 温度采集任务(500 ms)
    {SG90_Proc,     20,   0},  // SG90 舵机任务(20 ms)
    {Key_Proc,      20,   0},  // 按键处理任务(20 ms)
    {Beeper_Proc,   200,  0}   // 蜂鸣器任务(200 ms)
};

/* 调度器初始化 */
void scheduler_init(void)
{
    task_num = sizeof(scheduler_task) / sizeof(task_t);
}

/* 调度器主循环调用函数 */
void scheduler_run(void)
{
    for (uint8_t i = 0; i < task_num; i++)
    {
        uint32_t now_time = uwTick;
        if (now_time >= scheduler_task[i].rate_ms + scheduler_task[i].last_run)
        {
            scheduler_task[i].last_run = now_time;
            scheduler_task[i].task_func(); // 执行任务
        }
    }
}

