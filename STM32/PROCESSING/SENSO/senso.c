#include "senso.h"

#include <stdio.h>

//extern RTC_HandleTypeDef hrtc;
/**
 * @brief  Calculate cosine using Taylor series
 * @param degree [in]  Angle in degree.
 * @retval Cosine of degree
 */
static double SENSOR_cosine(int16_t degree)
{
    double sum = 1.0;
    double term = 1.0;
    double sign = -1.0;
    /* Conver degree to radian */
    double rad = degree * 3.14159265 / 180;

    for (uint32_t i = 2u; i <= 20u; i += 2u)
    {
        term *= (rad * rad) / ((double)i * ((double)i - 1.0));
        sum += sign * term;
        sign *= -1.0;
    }

    return sum;
}

CTL_StatusTypedef SENSOR_init(LEVEL_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    return (*me->levenInit)(me);
};

CTL_StatusTypedef SENSOR_deInit(LEVEL_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }
    return (*me->levenDeInit)(me);
}

CTL_StatusTypedef SENSOR_process(LEVEL_HandleTypedef *const me, uint16_t size)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }
    return (*me->levenProcess)(me, size);
}

CTL_StatusTypedef SENSOR_getConfig(LEVEL_HandleTypedef *const me, uint32_t configType, char pData[], uint16_t size)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    return (*me->levenGetConfig)(me, configType, pData, size);
}

CTL_StatusTypedef SENSOR_setSection(LEVEL_HandleTypedef *const me, uint8_t section)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    return (*me->levsenSetSection)(me, section);
}

float SENSOR_getNewValue(LEVEL_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    float level;
    level = (*me->levenGetLevel)(me);

    //level = (float)me->install + (SENSOR_cosine(me->angle) * (*me->levenGetLevel)(me));

    return level;
}

CTL_StatusTypedef SENSOR_setAngle(LEVEL_HandleTypedef *const me, uint8_t value)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    me->angle = value;

    return CTL_OK;
}

CTL_StatusTypedef SENSO_setInstall(LEVEL_HandleTypedef *const me, uint8_t value)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    me->install = value;

    return CTL_OK;
}

CTL_StatusTypedef SENSO_readEEPROM(LEVEL_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    uint32_t installStoredInDataEEPROM =
        *(volatile uint32_t *)SENSOR_EEPROM_INSTALL;
    uint8_t angleStoredInDataEEPROM =
        *(volatile uint8_t *)SENSOR_EEPROM_ANGLE;

    SENSO_setInstall(me, installStoredInDataEEPROM);
    SENSOR_setAngle(me, angleStoredInDataEEPROM);

    return CTL_OK;
}
CTL_StatusTypedef SENSO_writeEEPROM(LEVEL_HandleTypedef *const me)
{
    if (me == NULL)
    {
        return CTL_ERROR;
    }

    uint32_t installStoredInDataEEPROM =
        *(volatile uint32_t *)SENSOR_EEPROM_INSTALL;
    uint8_t angleStoredInDataEEPROM =
        *(volatile uint8_t *)SENSOR_EEPROM_ANGLE;

    if ((installStoredInDataEEPROM != me->install) || (angleStoredInDataEEPROM != me->angle))
    {
        HAL_FLASHEx_DATAEEPROM_Unlock();
        HAL_FLASHEx_DATAEEPROM_EnableFixedTimeProgram();
        HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,
                                       SENSOR_EEPROM_INSTALL, me->install);
        HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,
                                       SENSOR_EEPROM_ANGLE, me->angle);
        HAL_FLASHEx_DATAEEPROM_DisableFixedTimeProgram();
        HAL_FLASHEx_DATAEEPROM_Lock();
    }

    return CTL_OK;
}
