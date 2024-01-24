/*
 * ewg.h
 *
 *  Created on: Aug 3, 2023
 *      Author: NTPhong
 *      gmail: ntphong011102@gmail.com
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
/* Length per section */
#define LENGTH_OF_ONE_SECTION 40

/* Address to save section in EEPROM */
#define EWG_EEPROM_SECTION (SENSOR_EEPROM_ANGLE + 1)
typedef struct
{
	LEVEL_HandleTypedef leverHandle;
	uint8_t section;
	uint8_t sectionLevel[EWG_MAX_SECTION];

} EWG_HandleTypedef;

CTL_StatusTypedef EWG_init(EWG_HandleTypedef *const me);
CTL_StatusTypedef EWG_deInit(EWG_HandleTypedef *const me);
CTL_StatusTypedef EWG_process(EWG_HandleTypedef *const me, uint16_t size);
float EWG_getLevel(EWG_HandleTypedef *const me);
CTL_StatusTypedef EWG_setSection(EWG_HandleTypedef *const me, uint8_t section);
CTL_StatusTypedef EWG_getConfig(EWG_HandleTypedef *const me,
								uint32_t configType, char pData[], uint16_t size);
CTL_StatusTypedef EWG_writeEEPROMs(EWG_HandleTypedef *const me);

#endif /* EWG_EWG_H_ */
