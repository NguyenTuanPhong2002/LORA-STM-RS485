/*
 * lora.c
 *
 *  Created on: Aug 9, 2023
 *      Author: NTPhong
 *      gmail: ntphong011102@gmail.com
 */


#include "lora.h"

CTL_StatusTypedef LORA_init(LORA_HandleTypeDef *const me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}
	return (*me->init)(me);
}

CTL_StatusTypedef LORA_transmit(LORA_HandleTypeDef *const me, const uint8_t *pBuffer, uint16_t size, uint32_t timeout)
{
	if (me == NULL || pBuffer == NULL)
	{
		return CTL_ERROR;
	}

	return (*me->transmit)(me, pBuffer, size, timeout);
}

CTL_StatusTypedef LORA_receivePolling(LORA_HandleTypeDef *const me, uint8_t *pBuffer, uint16_t size, uint32_t timeout)
{
	if (me == NULL || pBuffer == NULL)
	{
		return CTL_ERROR;
	}

	return (*me->receive)(me, pBuffer, size, timeout);
}

CTL_StatusTypedef LORA_startReceiveIT(LORA_HandleTypeDef *const me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}

	return (*me->startReceiveIT)(me);
}

CTL_StatusTypedef LORA_receiveIT(LORA_HandleTypeDef *const me, uint8_t *pBuffer, uint16_t size)
{
	if (me == NULL || pBuffer == NULL)
	{
		return CTL_ERROR;
	}

	return (*me->receiveIT)(me, pBuffer, size);
}

CTL_StatusTypedef LORA_shutdown(LORA_HandleTypeDef *const me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}
	return (*me->shutdown)(me);
}

int16_t LORA_getRSSI(LORA_HandleTypeDef *const me)
{
	if (me == NULL)
	{
		return CTL_ERROR;
	}
	return (*me->getRSSI)(me);
}
