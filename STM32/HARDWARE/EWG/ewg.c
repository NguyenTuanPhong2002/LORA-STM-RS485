#include "ewg.h"

#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;

static inline void EWG_enableTransmitMode(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return ;
    }

    HAL_GPIO_WritePin(EWG_DE_GPIO, SET);
    HAL_GPIO_WritePin(EWG_DE_GPIO, SET);
}

static inline void EWG_enableReciveMode(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return ;
    }

    HAL_GPIO_WritePin(EWG_DE_GPIO, RESET);
    HAL_GPIO_WritePin(EWG_DE_GPIO, RESET);
}

static inline void EWG_shutdownMode(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return ;
    }

    HAL_GPIO_WritePin(EWG_DE_GPIO, SET);
    HAL_GPIO_WritePin(EWG_DE_GPIO, RESET);
}

static inline void EWG_powerEnable(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return ;
    }

    HAL_GPIO_WritePin(EWG_POWER_GPIO, SET);
}

static inline void EWG_powerDisable(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return ;
    }

    HAL_GPIO_WritePin(EWG_POWER_GPIO, RESET);
}

static uint16_t EWG_calcCRC16Modbus(const uint8_t *buf, uint8_t len)
{
    uint16_t crc = 0xFFFFU;
    int8_t i = 0;

    while (len--)
    {
        crc ^= (*buf++);

        for (i = 0; i < 8; i++)
        {
            if (crc & 1)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc;
}

EWG_StatusTypedef EWG_init(EWG_HandleTypedef *const me)
{
    if(me == NULL){
        return EWG_ERROR;
    }

    	if (HAL_UART_Init(huart2) != HAL_OK)
	{
		return EWG_ERROR;
	}
}
