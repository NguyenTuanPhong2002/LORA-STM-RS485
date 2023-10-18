/*
 * lora.h
 *
 *  Created on: Aug 9, 2023
 *      Author: NTPhong
 *      gmail: ntphong011102@gmail.com
 */

#ifndef LORA_LORA_H_
#define LORA_LORA_H_

#include "../../PROCESSING/DEBUG/handle.h"

typedef enum
{
	LORA_MODE_SLEEP,
	LORA_MODE_STANDBY,
	LORA_MODE_FSTX,
	LORA_MODE_TX,
	LORA_MODE_RSRX,
	LORA_MODE_RXCONTINUOUS,
	LORA_MODE_RXSINGLE,
	LORA_MODE_CAD,
	LORA_MODE_LORA,
	LORA_MODE_RESET = 0xF8U
} LORA_ModeTypeDef;

typedef enum
{
	LORA_SF_6 = 0x06U,
	LORA_SF_7,
	LORA_SF_8,
	LORA_SF_9,
	LORA_SF_10,
	LORA_SF_11,
	LORA_SF_12,
} LORA_SpredFactTypeDef;

typedef enum
{
	LORA_BW_7D8,
	LORA_BW_10D4,
	LORA_BW_15D6,
	LORA_BW_20D8,
	LORA_BW_31D25,
	LORA_BW_41D7,
	LORA_BW_62D5,
	LORA_BW_125,
	LORA_BW_250,
	LORA_BW_500,
} LORA_SigBandTypeDef;

typedef enum
{
	LORA_CR_45 = 0x01U,
	LORA_CR_46 = 0x02U,
	LORA_CR_47 = 0x03U,
	LORA_CR_48 = 0x04U,
} LORA_ErrCodRateTypeDef;

typedef enum
{
	LORA_PW_2dBm,
	LORA_PW_3dBm,
	LORA_PW_4dBm,
	LORA_PW_5dBm,
	LORA_PW_6dBm,
	LORA_PW_7dBm,
	LORA_PW_8dBm,
	LORA_PW_9dBm,
	LORA_PW_10dBm,
	LORA_PW_11dBm,
	LORA_PW_12dBm,
	LORA_PW_13dBm,
	LORA_PW_14dBm,
	LORA_PW_15dBm,
	LORA_PW_16dBm,
	LORA_PW_17dBm,
} LORA_PowerTxTypeDef;

typedef enum
{
	LORA_LNA_G1 = 0x01U,
	LORA_LNA_G2 = 0x02U,
	LORA_LNA_G3 = 0x03U,
	LORA_LNA_G4 = 0x04U,
	LORA_LNA_G5 = 0x05U,
	LORA_LNA_G6 = 0x06U,
} LORA_LNATypeDef;

typedef enum
{
	LORA_CAD_DETECT = 0x00U,
	LORA_CAD_UNDETECT = 0x01U,
	LORA_CAD_ERROR = 0x02U
} LORA_CADStatusTypeDef;

typedef struct lora
{
	uint32_t freq;
	LORA_SpredFactTypeDef SF;
	LORA_SigBandTypeDef BW;
	LORA_ErrCodRateTypeDef CR;
	LORA_PowerTxTypeDef ptx;
	LORA_LNATypeDef LNA;
	LORA_ModeTypeDef mode;
	uint16_t preamble;
	CTL_StatusTypedef (*init)(struct lora *const me);
	CTL_StatusTypedef (*transmit)(struct lora *const me, const uint8_t *pBuffer, uint16_t size, uint32_t timeout);
	CTL_StatusTypedef (*receive)(struct lora *const me, uint8_t *pBuffer, uint16_t size, uint32_t timeout);
	CTL_StatusTypedef (*startReceiveIT)(struct lora *const me);
	CTL_StatusTypedef (*receiveIT)(struct lora *const me, uint8_t *pBuffer, uint16_t size);
	CTL_StatusTypedef (*shutdown)(struct lora *const me);
	int16_t (*getRSSI)(struct lora *const me);
} LORA_HandleTypeDef;

typedef CTL_StatusTypedef (*loraInit)(struct lora *const me);
typedef CTL_StatusTypedef (*loraTransmit)(struct lora *const me, const uint8_t *pBuffer, uint16_t size, uint32_t timeout);
typedef CTL_StatusTypedef (*loraReceive)(struct lora *const me, uint8_t *pBuffer, uint16_t size, uint32_t timeout);
typedef CTL_StatusTypedef (*loraStartReceiveOnIRQ)(struct lora *const me);
typedef CTL_StatusTypedef (*loraReceiveOnIRQ)(struct lora *const me, uint8_t *pBuffer, uint16_t size);
typedef CTL_StatusTypedef (*loraShutdown)(struct lora *const me);
typedef int16_t (*loraGetRSSI)(struct lora *const me);

CTL_StatusTypedef LORA_init(LORA_HandleTypeDef *const me);
CTL_StatusTypedef LORA_receivePolling(LORA_HandleTypeDef *const me, uint8_t *pBuffer, uint16_t size, uint32_t timeout);
CTL_StatusTypedef LORA_startReceiveIT(LORA_HandleTypeDef *const me);
CTL_StatusTypedef LORA_receiveIT(LORA_HandleTypeDef *const me, uint8_t *pBuffer, uint16_t size);
CTL_StatusTypedef LORA_transmit(LORA_HandleTypeDef *const me, const uint8_t *pBuffer, uint16_t size, uint32_t timeout);
CTL_StatusTypedef LORA_shutdown(LORA_HandleTypeDef *const me);
int16_t LORA_getRSSI(LORA_HandleTypeDef *const me);

#endif /* LORA_LORA_H_ */
