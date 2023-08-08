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

static CTL_StatusTypedef sendCommand(EWG_HandleTypedef *const me, uint8_t *Command, uint8_t size, uint16_t timeout)
{
    if (me == NULL || Command == NULL)
    {
        return CTL_ERROR;
    }

    HAL_UARTEx_ReceiveToIdle_IT(&huart2, (uint8_t *)me->leverHandle.buffer, LEVEL_BUFFER_SIZE);

    EWG_enableTransmitMode(me);

    CTL_StatusTypedef status = CTL_BUSY;

    memset(me->leverHandle.buffer, "\0", LEVEL_BUFFER_SIZE);

    HAL_UART_Transmit(&huart2, Command, size, timeout);

    EWG_enableReciveMode(me);

    uint32_t tickStart = HAL_GetTick();

    while (status == CTL_BUSY)
    {
        if (HAL_GetTick() - tickStart >= timeout)
        {
            status = CTL_BUSY;
            SENSO_SET_FLAG(&me->leverHandle, SENSO_FLAG_SCF);
        }
        else
        {
            if (SENSO_GET_FLAG(&me->leverHandle, SENSO_FLAG_RX))
            {
                uint16_t packetCRC = ((uint16_t)me->leverHandle.buffer[me->leverHandle.sizeResponse - 1] << 8) |
                                     (me->leverHandle.buffer[me->leverHandle.sizeResponse - 2]);
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
                    status = CTL_OK;
                }
            }
        }
    }

    EWG_shutdownMode(me);
    SENSO_CLR_FLAG(&me->leverHandle, SENSO_FLAG_RX);
    return status;
}

CTL_StatusTypedef EWG_init(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        return CTL_ERROR;
    }

    EWG_powerEnable(me);

    HAL_UARTEx_ReceiveToIdle_IT(&huart2, (uint8_t *)me->leverHandle.buffer, LEVEL_BUFFER_SIZE);

    /* Message test connection - read the first section of the sensor */
    uint8_t command[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};

    uint32_t tickStart = HAL_GetTick();

    CTL_StatusTypedef status = CTL_ERROR;

    while (HAL_GetTick() - tickStart <= 3000)
    {
        if (sendCommand(me, command, sizeof(command), 1000) == CTL_OK)
        {
            status = CTL_OK;
            break;
        }
    }

    EWG_powerDisable(me);

    return status;
}

CTL_StatusTypedef EWG_deInit(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    HAL_UART_DeInit(&huart2);
#if 1
    HAL_GPIO_DeInit(EWG_RE_GPIO);
    HAL_GPIO_DeInit(EWG_DE_GPIO);
#endif
    return CTL_OK;
}

CTL_StatusTypedef EWG_process(EWG_HandleTypedef *const me, uint16_t size)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, (uint8_t *)me->leverHandle.buffer, LEVEL_BUFFER_SIZE);

    SENSO_SET_FLAG(&me->leverHandle, SENSO_FLAG_RX);
    me->leverHandle.sizeResponse = size;

    return CTL_OK;
}

float EWG_getLevel(EWG_HandleTypedef *const me)
{
    float lever = 0.0;

    uint8_t queryFrame[8] = {0x0, 0x3, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0};

    EWG_powerEnable(me);

    for (size_t i = 1; i <= me->section; i++)
    {
        queryFrame[0] = i;
        uint16_t reponseCRC = EWG_calcCRC16Modbus(queryFrame, sizeof(queryFrame) - 2);
        queryFrame[6] = (uint8_t)(reponseCRC & 0xFF);
        queryFrame[7] = (uint8_t)((reponseCRC >> 8) & 0xFF);

        if (CTL_OK == sendCommand(me, queryFrame, sizeof(queryFrame), 1000))
        {
            lever += me->sectionLevel[i];
        }
    }

    EWG_powerDisable(me);

    if (lever >= (me->section * LENGTH_OF_ONE_SECTION))
    {
        lever = 0.0f;
    }
    else
    {
        /* Convert cm to mm */
        lever *= 10.0f;
    }

    return lever;
}

CTL_StatusTypedef EWG_setSection(EWG_HandleTypedef *const me, uint8_t section)
{
    if (me == NULL || section > EWG_MAX_SECTION)
    {
        return CTL_ERROR;
    }

    me->section = section;

    uint8_t sectionStoredInDataEEPROM = *(volatile uint8_t *)EWG_EEPROM_SECTION;

    if (sectionStoredInDataEEPROM != section)
    {
        EWG_writeEEPROMs(me);
    }

    return CTL_OK;
}

CTL_StatusTypedef EWG_getConfig(EWG_HandleTypedef *const me, uint32_t configType, char pData[], uint16_t size)
{
    if (me == NULL || pData == NULL)
    {
        return CTL_ERROR;
    }

    if ((configType & SENSOR_SR_GCFG_EWG_SECTION) == SENSOR_SR_GCFG_EWG_SECTION)
    {
        snprintf(pData, size, "SECTION(s): %u", me->section);
    }

    return CTL_OK;
}

CTL_StatusTypedef EWG_writeEEPROMs(EWG_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    /* Read section from EEPROM */
    uint8_t sectionStoredInDataEEPROM = *(volatile uint8_t *)EWG_EEPROM_SECTION;

    // if (me->section != sectionStoredInDataEEPROM)
    // {
    //     HAL_FLASHEx_DATAEEPROM_Unlock();
    //     HAL_FLASHEx_DATAEEPROM_EnableFixedTimeProgram();
    //     HAL_FLASHEx_DATAEEPROM_Erase(FLASH_TYPEPROGRAMDATA_BYTE, EWG_EEPROM_SECTION);
    //     HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, EWG_EEPROM_SECTION, me->section);
    //     HAL_FLASHEx_DATAEEPROM_DisableFixedTimeProgram();
    //     HAL_FLASHEx_DATAEEPROM_Lock();
    // }

    return CTL_OK;
}
