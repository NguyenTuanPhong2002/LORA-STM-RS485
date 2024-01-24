/*
 * battery.h
 *
 *  Created on: Oct 18, 2023
 *      Author: NTPhong
 *      gmail: ntphong011102@gmail.com
 */

#ifndef BATTERY_BATTERY_H_
#define BATTERY_BATTERY_H_

#include "power.h"

typedef struct
{
	POWER_HandleTypeDef parent;
	ADC_HandleTypeDef *hadc;
} BATTERY_HandleTypeDef;

/* Upper battery threshold */
#define BATTERY_MAX_VOLTAGE		(12.6f)
/* Lower battery threshold */
#define BATTERY_MIN_VOLTAGE		(6.7f)

CTL_StatusTypedef BATTERY_init(BATTERY_HandleTypeDef *const me);
CTL_StatusTypedef BATTERY_getPowerState(BATTERY_HandleTypeDef *const me);
uint8_t BATTERY_getBatteryPercent(BATTERY_HandleTypeDef *const me);
float BATTERY_getBatteryVoltage(BATTERY_HandleTypeDef *const me);


#endif /* BATTERY_BATTERY_H_ */
