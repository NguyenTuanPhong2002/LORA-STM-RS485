#include "handle.h"

#include "string.h"

extern UART_HandleTypeDef huart1;

void print(const char *buffer)
{
        char txBuffer[500];
        sprintf((char *)txBuffer, "%s\r\n", buffer);
        uint16_t len = strlen((char *)txBuffer);
        HAL_UART_Transmit(&huart1, (uint8_t *)txBuffer, len, 100);
}
