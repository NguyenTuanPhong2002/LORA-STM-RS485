#include "ewg.h"

#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;

static inline void EWG_enableTransmitMode(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return;
    }

    HAL_GPIO_WritePin(EWG_DE_GPIO, SET);
    HAL_GPIO_WritePin(EWG_DE_GPIO, SET);
}

static inline void EWG_enableReciveMode(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return;
    }

    HAL_GPIO_WritePin(EWG_DE_GPIO, RESET);
    HAL_GPIO_WritePin(EWG_DE_GPIO, RESET);
}

static inline void EWG_shutdownMode(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return;
    }

    HAL_GPIO_WritePin(EWG_DE_GPIO, SET);
    HAL_GPIO_WritePin(EWG_DE_GPIO, RESET);
}

static inline void EWG_powerEnable(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return;
    }

    HAL_GPIO_WritePin(EWG_POWER_GPIO, SET);
}

static inline void EWG_powerDisable(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return;
    }

    HAL_GPIO_WritePin(EWG_POWER_GPIO, RESET);
}

uint16_t EWG_calcCRC16Modbus(const uint8_t *buf, uint8_t len)
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

static EWG_StatusTypedef sendCommand(EWG_HandleTypedef *const me, uint8_t *Command, uint8_t size, uint8_t timeout)
{
    if (me == NULL || Command == NULL)
    {
        return EWG_ERROR;
    }

    HAL_UARTEx_ReceiveToIdle_IT(&huart2, (uint8_t *)me->leverHandle.buffer, LEVEL_BUFFER_SIZE);

    EWG_enableTransmitMode(me);

    EWG_StatusTypedef status = EWG_BUSY;

    memset(me->leverHandle.buffer, "\0", LEVEL_BUFFER_SIZE);

    HAL_UART_Transmit(&huart2, Command, size, timeout);

    EWG_enableReciveMode(me);

    uint32_t tickStart = HAL_GetTick();

    while (status == EWG_BUSY)
    {
        if (HAL_GetTick() - tickStart >= timeout)
        {
            status = EWG_BUSY;
            me->leverHandle.flag = 0;
        }
        else
        {
            if (me->leverHandle.flag == 1)
            {
                uint16_t packetCRC = ((uint16_t)me->leverHandle.buffer[me->leverHandle.sizeResponse - 1] << 8) | (me->leverHandle.buffer[me->leverHandle.sizeResponse - 2]);
                if (EWG_calcCRC16Modbus((uint8_t *)me->leverHandle.buffer, me->leverHandle.sizeResponse - 2) == packetCRC)
                {
                    for (size_t i = 1; i <= me->section; i++)
                    {
                        if (me->leverHandle.buffer[0] == i)
                        {
                            me->sectionLevel[i] = me->leverHandle.buffer[4];
                            break;
                        }
                    }
                    status = EWG_OK;
                }
            }
        }
    }

    EWG_shutdownMode(me);
    me->leverHandle.flag = 0;
    return status;
}

EWG_StatusTypedef EWG_init(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return EWG_ERROR;
    }

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        return EWG_ERROR;
    }

    EWG_powerEnable(me);
}
