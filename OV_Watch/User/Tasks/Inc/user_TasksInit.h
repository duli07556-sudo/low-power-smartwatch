#ifndef __USER_TASKSINIT_H__
#define __USER_TASKSINIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "cmsis_os.h"

#define SCRRENEW_DEPTH	5

/*
 * Shared PB13/PB14 software-I2C protection switch.
 * 0: preserve original non-blocking behavior for the baseline test.
 * 1: serialize MPUCheckTask and SensorDataTask access with a task-level mutex.
 */
#define SENSOR_I2C_TASK_MUTEX_ENABLE  1U

extern osMessageQueueId_t Key_MessageQueue;
extern osMessageQueueId_t Idle_MessageQueue;
extern osMessageQueueId_t Stop_MessageQueue;
extern osMessageQueueId_t IdleBreak_MessageQueue;
extern osMessageQueueId_t HomeUpdata_MessageQueue;
extern osMessageQueueId_t DataSave_MessageQueue;

/* Task-level sensor-I2C mutex and diagnostic counters. */
extern volatile uint32_t g_sensor_i2c_wait_count;
extern volatile uint32_t g_sensor_i2c_max_wait_ticks;
void SensorI2C_TaskLock(void);
void SensorI2C_TaskUnlock(void);

void User_Tasks_Init(void);
void TaskTickHook(void);

#ifdef __cplusplus
}
#endif

#endif

