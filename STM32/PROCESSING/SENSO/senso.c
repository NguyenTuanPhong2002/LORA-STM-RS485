#include "senso.h"

#include <stdio.h>

extern RTC_HandleTypeDef hrtc;
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