/*
 * controller.h
 *
 *  Created on: Aug 8, 2023
 *      Author: NTPhong
 *      gmail: ntphong011102@gmail.com
 */

#ifndef INC_CONTROLLER_H_
#define INC_CONTROLLER_H_

#include "main.h"

typedef enum
{
    CTL_BUSY,
    CTL_OK,
    CTL_ERROR,
    CTL_TIMEOUT
} CTL_StatusTypedef;

void print(const char *buffer);

#endif /* INC_CONTROLLER_H_ */
