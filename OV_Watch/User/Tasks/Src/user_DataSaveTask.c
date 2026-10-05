/* Private includes -----------------------------------------------------------*/
//includes
#include "user_DataSaveTask.h"
//APP SYS setting
#include "ui_DateTimeSetPage.h"
#include "ui_HomePage.h"
#include "ui_OffTimePage.h"

#include "main.h"
#include "rtc.h"
#include "DataSave.h"
#include "inv_mpu_dmp_motion_driver.h"

#include "HWDataAccess.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/******************************************
EEPROM Data description:
[0x00]:0x55 for check
[0x01]:0xAA for check

[0x10]:user wrist setting, HWInterface.IMU.wrist_is_enabled
[0x11]:user ui_APPSy_EN setting
[0x12]:normal brightness duration, ui_LTimeValue
[0x13]:STOP mode duration, ui_TTimeValue

[0x20]:Last Save Day(0-31)
[0x21]:Day Steps high byte
[0x22]:Day Steps low byte

*******************************************/


/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Request DataSaveTask to save the latest settings.
  * @note   The queue item carries no data. DataSaveTask reads the latest global
  *         values, so an already pending request also covers later changes.
  */
void DataSave_Request(void)
{
	uint8_t save_request = 1;

	// ä¿®å¤ï¼šè®¾ç½®æ”¹å˜æ—¶ç«‹å³é€šçŸ¥ä¿å­˜ä»»åŠ¡ï¼Œé¿å…å¿…é¡»ç­‰åˆ° STOP å”¤é†’åŽæ‰å†™ EEPROMã€‚
	(void)osMessageQueuePut(DataSave_MessageQueue, &save_request, 0, 0);
}

/* Tasks ---------------------------------------------------------------------*/

/**
  * @brief  Data Save in the EEPROM
  * @param  argument: Not used
  * @retval None
  */
void DataSaveTask(void *argument)
{

	while(1)
	{
		uint8_t Datastr=0;
		if(osMessageQueueGet(DataSave_MessageQueue,&Datastr,NULL,1)==osOK)
		{
			/****************
			Setting change
			date change
			Step change
			****************/
			uint8_t dat[4];
			dat[0] = HWInterface.IMU.wrist_is_enabled;
			dat[1] = ui_APPSy_EN;
			dat[2] = ui_LTimeValue;
			dat[3] = ui_TTimeValue;
			SettingSave(dat,0x10,4); // ä¿®å¤ï¼š0x10~0x13 ä¸€æ¬¡ä¿å­˜å››é¡¹ç”¨æˆ·è®¾ç½®ã€‚

			RTC_DateTypeDef nowdate;
			HAL_RTC_GetDate(&hrtc,&nowdate,RTC_FORMAT_BIN);

			SettingGet(dat,0x20,3);
			if(dat[0] != nowdate.Date)
			{
				if(!HWInterface.IMU.ConnectionError)
				{
					// MPU ¹²ÓÃ´«¸ÐÆ÷ I2C£ºÇåÁã²½ÊýÒ²Ðë»ñÈ¡Í¬Ò»°ÑËø£¬EEPROM ²»ÔÚ´ËËøÄÚ¡£
					SensorI2C_TaskLock();
					HWInterface.IMU.SetSteps(0);
					SensorI2C_TaskUnlock();
				}

				dat[0] = nowdate.Date;
				dat[2] = 0;
				dat[1] = 0;
				SettingSave(dat,0x20,3);
			}
			else
			{
				uint16_t temp;
				// GetSteps »á·ÃÎÊ MPU Ó²¼þ£»Óë´«¸ÐÆ÷¸üÐÂ¡¢Ì§Íó¼ì²âÈÎÎñ¹²ÓÃ»¥³âËø¡£
				SensorI2C_TaskLock();
				temp = HWInterface.IMU.GetSteps();
				SensorI2C_TaskUnlock();
				dat[0] = nowdate.Date;
				dat[2] = temp & 0xff;
				dat[1] = temp>>8 & 0xff;
				SettingSave(dat,0x20,3);
			}

		}
		osDelay(100);
	}
}


