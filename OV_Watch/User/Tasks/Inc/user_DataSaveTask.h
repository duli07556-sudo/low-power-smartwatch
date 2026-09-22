#ifndef __USER_DATASAVETASK_H__
#define __USER_DATASAVETASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "user_TasksInit.h"


// 设置改变时只投递保存请求，EEPROM 实际写入统一放在 DataSaveTask 中执行。
void DataSave_Request(void);
void DataSaveTask(void *argument);

	
#ifdef __cplusplus
}
#endif

#endif

