/*
 * config.h
 *
 *  Created on: Sep 20, 2023
 *      Author: NTPhong
 *      gmail: ntphong011102@gmail.com
 */

#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

#include "../../PROCESSING/DEBUG/handle.h"
#include "stm32l0xx.h"
#define CFG_DEVICE_ID_SIZE 15U
#define CFG_MASTER_ID_SIZE 15U

#define CFG_EEPROM_DEVICE_ID (0x00080060UL)
#define CFG_EEPROM_MASTER_ID (CFG_EEPROM_DEVICE_ID + CFG_DEVICE_ID_SIZE)

typedef struct
{
	char deviceID[CFG_DEVICE_ID_SIZE];
	char masterID[CFG_MASTER_ID_SIZE];
} CFG_HandleTypeDef;

CTL_StatusTypedef CFG_setDeviceID(CFG_HandleTypeDef *const me, const char *pID, uint8_t size);
CTL_StatusTypedef CFG_setDeviceMaster(CFG_HandleTypeDef *const me, const char *pID, uint8_t size);

char *CFG_getDeviceID(CFG_HandleTypeDef *const me);
char *CFG_getDeviceMaster(CFG_HandleTypeDef *const me);

CTL_StatusTypedef CFG_writeEEPROM(CFG_HandleTypeDef *me);
CTL_StatusTypedef CFG_getID(CFG_HandleTypeDef *me);
CTL_StatusTypedef CFG_getMaster(CFG_HandleTypeDef *me);
#endif /* CONFIG_CONFIG_H_ */
