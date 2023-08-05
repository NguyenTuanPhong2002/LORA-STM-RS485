/*
 * senso.h
 *
 *  Created on: Aug 3, 2023
 *      Author: ACER
 */

#ifndef SENSO_SENSO_H_
#define SENSO_SENSO_H_

#include "main.h"
#include "stm32l052xx.h"
#include "stm32l0xx_hal_uart.h"
#include "stm32l0xx_hal_uart_ex.h"

#define LEVEL_BUFFER_SIZE 500

typedef enum
{
    EWG_BUSY,
    EWG_OK,
    EWG_ERROR,
    EWG_TIMEOUT
} EWG_StatusTypedef;

typedef struct
{
    char buffer[LEVEL_BUFFER_SIZE];
    uint8_t flag;
    uint16_t sizeResponse;
}LEVEL_HandleTypedef;


#endif /* SENSO_SENSO_H_ */
