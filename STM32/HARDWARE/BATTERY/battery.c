/*
 * battery.c
 *
 *  Created on: Oct 18, 2023
 *      Author: NTPhong
 *      gmail: ntphong011102@gmail.com
 */


#include "battery.h"

CTL_StatusTypedef BATTERY_init(BATTERY_HandleTypeDef *const me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}

	// ADC_ChannelConfTypeDef sConfig = {0};

	// /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	//  */
	// me->hadc->Instance = ADC1;
	// me->hadc->Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV4;
	// me->hadc->Init.Resolution = ADC_RESOLUTION_12B;
	// me->hadc->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	// me->hadc->Init.ScanConvMode = ADC_SCAN_DISABLE;
	// me->hadc->Init.EOCSelection = ADC_EOC_SEQ_CONV;
	// me->hadc->Init.LowPowerAutoWait = ADC_AUTOWAIT_UNTIL_DATA_READ;
	// me->hadc->Init.LowPowerAutoPowerOff = ADC_AUTOPOWEROFF_IDLE_PHASE;
	// me->hadc->Init.ChannelsBank = ADC_CHANNELS_BANK_A;
	// me->hadc->Init.ContinuousConvMode = ENABLE;
	// me->hadc->Init.NbrOfConversion = 1;
	// me->hadc->Init.DiscontinuousConvMode = DISABLE;
	// me->hadc->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	// me->hadc->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	// me->hadc->Init.DMAContinuousRequests = DISABLE;
	// if (HAL_ADC_Init(me->hadc) != HAL_OK)
	// {
	// 	return CTL_ERROR;
	// }
	// /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	//  */
	// sConfig.Channel = ADC_CHANNEL_18;
	// sConfig.Rank = ADC_REGULAR_RANK_1;
	// sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
	// if (HAL_ADC_ConfigChannel(me->hadc, &sConfig) != HAL_OK)
	// {
	// 	return CTL_ERROR;
	// }

	return CTL_OK;
}

/**
 * @brief BATTERY Get power state
 * @param me Baterry handle
 * @retval WLV Status
 */
CTL_StatusTypedef BATTERY_getPowerState(BATTERY_HandleTypeDef *const me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}

	return CTL_OK;
}

/**
 * @brief Get battery in percent format
 * @param me Baterry handle
 * @retval Battery percent
 */
uint8_t BATTERY_getBatteryPercent(BATTERY_HandleTypeDef *const me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}

    float VOTAGE_SCALE_RATIO = 3.5f;
	enum {
		COUNTER = 10
	};
	/* 1. Calculates battery voltage */
	me->parent.voltage = 0.0f;
	uint32_t adcValue = 0U;

	HAL_ADC_Start(me->hadc);

	uint32_t tickStart = HAL_GetTick();

	while (HAL_OK != HAL_ADC_Start(me->hadc))
	{
		if (HAL_GetTick() - tickStart >= 100)
		{
			break;
		}
	}
	for (size_t i = 0; i < COUNTER; i++)
	{
		adcValue += HAL_ADC_GetValue(me->hadc);
		HAL_Delay(50);
	}

	HAL_ADC_Stop(me->hadc);

	me->parent.voltage = ((float)(((adcValue / COUNTER) * 3.3f) / 4095U) * VOTAGE_SCALE_RATIO);



	/* 2. Calculates percent from voltage */

	me->parent.percent = (uint8_t)(((me->parent.voltage - BATTERY_MIN_VOLTAGE) / (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE)) * 100U);
	if (me->parent.percent > 100U)
	{
		me->parent.percent = 100U;
	}
	else if (me->parent.percent < 0U)
	{
		me->parent.percent = 0U;
	}

	return me->parent.percent;
}

/**
 * @brief Get battery voltage
 * @param me Baterry handle
 * @retval battery voltage (V)
 */
float BATTERY_getBatteryVoltage(BATTERY_HandleTypeDef *const me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}

	/* 1. Calculates battery voltage */
	me->parent.voltage = 0.0f;
	uint32_t adcValue = 0U;

	HAL_ADC_Start(me->hadc);

	HAL_Delay(10);

	adcValue = HAL_ADC_GetValue(me->hadc);

	me->parent.voltage = ((float)((adcValue * 3.3f) / 4096U) * 5U);

	HAL_ADC_Stop(me->hadc);

	return me->parent.voltage;
}
