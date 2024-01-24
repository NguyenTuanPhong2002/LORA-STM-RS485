/*
 * power.c
 *
 *  Created on: Oct 18, 2023
 *      Author: NTPhong
 *      gmail: ntphong011102@gmail.com
 */




#include "power.h"

#include <stddef.h>

/**
 * @brief Power Initialize
 *
 * @param me [in] A pointer to POWER_HandleTypeDef structure
 * @return THT_StatusTypeDef
 */
CTL_StatusTypedef POWER_init(POWER_HandleTypeDef *const me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}

	return (*me->init)(me);
}

/**
 * @brief Get Battery Voltage Percent
 *
 * @param me [in] A pointer to POWER_HandleTypeDef structure
 * @return uint8_t
 */
uint8_t POWER_getBatPercent(POWER_HandleTypeDef *me)
{
	if (me == NULL)
	{
		return 0;
	}

	return (*me->getPercent)(me);
}

/**
 * @brief Get Battery Voltage
 *
 * @param me [in] A pointer to POWER_HandleTypeDef structure
 * @return float
 */
float POWER_getBatVoltage(POWER_HandleTypeDef *me)
{
	if (me == NULL)
	{
		return 0;
	}

	return (*me->getVoltage)(me);
}

/**
 * @brief Get Power State
 *
 * @param me [in] A pointer to POWER_HandleTypeDef structure
 * @return THT_StatusTypeDef
 */
CTL_StatusTypedef POWER_getPowerState(POWER_HandleTypeDef *me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}

	return (*me->getPowerState)(me);
}
