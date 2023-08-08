/*
 * senso.h
 *
 *  Created on: Aug 3, 2023
 *      Author: ACER
 */

#ifndef SENSO_SENSO_H_
#define SENSO_SENSO_H_

#include "main.h"

#include "../../CONTROLLER/inc/controller.h"

#define LEVEL_BUFFER_SIZE 500

typedef struct level
{
    char buffer[LEVEL_BUFFER_SIZE];
    volatile uint32_t SR;
    uint16_t sizeResponse;

    CTL_StatusTypedef (*levenInit)(struct lever *const me);
} LEVEL_HandleTypedef;

typedef CTL_StatusTypedef (*levenInit)(struct lever *const me);

#define SENSO_FLAG_SCF 0x01 // SENSO CONNECT FAIL
#define SENSO_FLAG_RX 0x02

#define SENSO_SET_FLAG(__ME__, __FLAG__) (((__ME__)->SR) = (__FLAG__))
#define SENSO_GET_FLAG(__ME__, __FLAG__) (((__ME__)->SR) == (__FLAG__))
#define SENSO_CLR_FLAG(__ME__, __FLAG__) (((__ME__)->SR) &= ~(__FLAG__))

// 20-29 used for EWG
#define SENSOR_SR_GCFG_EWG_SECTION (0x0010UL << 8u)

#define SENSOR_EEPROM_INSTALL //(WLV_SENSOR_BASE)
#define SENSOR_EEPROM_WARNING_LEVEL_1 (SENSOR_EEPROM_INSTALL + 4)
#define SENSOR_EEPROM_WARNING_LEVEL_2 (SENSOR_EEPROM_WARNING_LEVEL_1 + 4)
#define SENSOR_EEPROM_WARNING_LEVEL_3 (SENSOR_EEPROM_WARNING_LEVEL_2 + 4)
#define SENSOR_EEPROM_WARNING_LEVEL_4 (SENSOR_EEPROM_WARNING_LEVEL_3 + 4)
#define SENSOR_EEPROM_WARNING_LEVEL_5 (SENSOR_EEPROM_WARNING_LEVEL_4 + 4)
#define SENSOR_EEPROM_ANGLE (SENSOR_EEPROM_WARNING_LEVEL_5 + 4)

#endif /* SENSO_SENSO_H_ */
