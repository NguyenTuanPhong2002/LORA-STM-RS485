/*
 * ewg.h
 *
 *  Created on: Aug 3, 2023
 *      Author: ACER
 */

#ifndef EWG_EWG_H_
#define EWG_EWG_H_

#include "main.h"

#define EWG_RE_GPIO GPIOB, RE_Pin
#define EWG_DE_GPIO GPIOB, DE_Pin

/* Array offset for water level sensor */
#define EWG_SECTION_ARR_OFFSET	(1u)
/* Number of sections of water level sensor */
#define EWG_MAX_SECTION			(12u + EWG_SECTION_ARR_OFFSET)

typedef struct
{
    uint8_t section;
    uint8_t sectionLevel[EWG_MAX_SECTION];
} EWG_HandleTypedef;

#endif /* EWG_EWG_H_ */
