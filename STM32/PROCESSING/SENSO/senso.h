/*
 * senso.h
 *
 *  Created on: Aug 3, 2023
 *      Author: ACER
 */

#ifndef SENSO_SENSO_H_
#define SENSO_SENSO_H_

#include "main.h"

#include "../../CONTROLLER/handle.h"

#define LEVEL_BUFFER_SIZE 100

typedef struct level
{
    char buffer[LEVEL_BUFFER_SIZE];
    volatile uint32_t SR;
    uint16_t sizeResponse;

    float levelValue;
    uint8_t angle;
    uint8_t valueIndex;
    uint32_t install;

    CTL_StatusTypedef (*levenInit)(struct level *const me);
    CTL_StatusTypedef (*levenDeInit)(struct level *const me);
    CTL_StatusTypedef (*levenProcess)(struct level *const me, uint16_t size);
    CTL_StatusTypedef (*levenGetConfig)(struct level *const me, uint32_t configType, char pData[], uint16_t size);
    CTL_StatusTypedef (*levsenSetSection)(struct level *const me, uint8_t section);

    float (*levenGetLevel)(struct level *const me);

} LEVEL_HandleTypedef;

typedef CTL_StatusTypedef (*levenInit)(struct level *const me);
typedef CTL_StatusTypedef (*levenDeInit)(struct level *const me);
typedef CTL_StatusTypedef (*levenProcess)(struct level *const me, uint16_t size);
typedef CTL_StatusTypedef (*levenGetConfig)(struct level *const me, uint32_t configType, char pData[], uint16_t size);
typedef CTL_StatusTypedef (*levsenSetSection)(struct level *const me, uint8_t section);
typedef float (*levenGetLevel)(struct level *const me);

#define SENSO_FLAG_SCF 0x01 // SENSO CONNECT FAIL
#define SENSO_FLAG_RX 0x02

#define SENSO_SET_FLAG(__ME__, __FLAG__) (((__ME__)->SR) = (__FLAG__))
#define SENSO_GET_FLAG(__ME__, __FLAG__) (((__ME__)->SR) == (__FLAG__))
#define SENSO_CLR_FLAG(__ME__, __FLAG__) (((__ME__)->SR) &= ~(__FLAG__))

// 20-29 used for EWG
#define SENSOR_SR_GCFG_EWG_SECTION (0x0010UL << 8u)

// #define SENSOR_EEPROM_INSTALL //(WLV_SENSOR_BASE)
// #define SENSOR_EEPROM_WARNING_LEVEL_1 (SENSOR_EEPROM_INSTALL + 4)
// #define SENSOR_EEPROM_WARNING_LEVEL_2 (SENSOR_EEPROM_WARNING_LEVEL_1 + 4)
// #define SENSOR_EEPROM_WARNING_LEVEL_3 (SENSOR_EEPROM_WARNING_LEVEL_2 + 4)
// #define SENSOR_EEPROM_WARNING_LEVEL_4 (SENSOR_EEPROM_WARNING_LEVEL_3 + 4)
// #define SENSOR_EEPROM_WARNING_LEVEL_5 (SENSOR_EEPROM_WARNING_LEVEL_4 + 4)
// #define SENSOR_EEPROM_ANGLE (SENSOR_EEPROM_WARNING_LEVEL_5 + 4)

#define SENSOR_EEPROM_INSTALL 0x08080000
#define SENSOR_EEPROM_ANGLE 0x0808000F

CTL_StatusTypedef SENSOR_init(LEVEL_HandleTypedef *const me);
CTL_StatusTypedef SENSOR_deInit(LEVEL_HandleTypedef *const me);
CTL_StatusTypedef SENSOR_process(LEVEL_HandleTypedef *const me, uint16_t size);
CTL_StatusTypedef SENSOR_getConfig(LEVEL_HandleTypedef *const me, uint32_t configType, char pData[], uint16_t size);
CTL_StatusTypedef SENSOR_setSection(LEVEL_HandleTypedef *const me, uint8_t section);
float SENSOR_getNewValue(LEVEL_HandleTypedef *const me);

CTL_StatusTypedef SENSOR_setAngle(LEVEL_HandleTypedef *const me, uint8_t value);
CTL_StatusTypedef SENSO_setInstall(LEVEL_HandleTypedef *const me, uint8_t value);

CTL_StatusTypedef SENSO_readEEPROM(LEVEL_HandleTypedef *const me);
CTL_StatusTypedef SENSO_writeEEPROM(LEVEL_HandleTypedef *const me);

#endif /* SENSO_SENSO_H_ */
