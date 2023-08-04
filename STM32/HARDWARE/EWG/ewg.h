/*
 * ewg.h
 *
 *  Created on: Aug 3, 2023
 *      Author: ACER
 */

#ifndef EWG_EWG_H_
#define EWG_EWG_H_

#include "../../PROCESSING/SENSO/senso.h"

#define EWG_RE_GPIO RE_GPIO_Port, RE_Pin
#define EWG_DE_GPIO DE_GPIO_Port, DE_Pin

#define EWG_POWER_GPIO PWR_SENSO_GPIO_Port, PWR_SENSO_Pin

/* Array offset for water level sensor */
#define EWG_SECTION_ARR_OFFSET (1u)
/* Number of sections of water level sensor */
#define EWG_MAX_SECTION (12u + EWG_SECTION_ARR_OFFSET)

typedef struct
{
    uint8_t section;
    uint8_t sectionLevel[EWG_MAX_SECTION];
    LEVEL_HandleTypedef leverHandle; 
} EWG_HandleTypedef;

EWG_StatusTypedef EWG_init(EWG_HandleTypedef *const me);
#endif /* EWG_EWG_H_ */
