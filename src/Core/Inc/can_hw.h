/**
 * @file can_hw.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para can_hw.c
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _CAN_HW_H_
#define _CAN_HW_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* STM32 specific hardware configuration includes */
#include "can.h"
#include "tim.h"

/* CAN driver includes */
#include "can_api.h"
#include "can_wrapper.h"

/* STM32 HAL include */
#include "main.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/**
 * @brief Tipo de dato can_rx_status_t para estado de recepción de mensaje CAN
 *
 */
typedef enum
{
	CAN_MSG_RECEIVED = 0, 		/**< Mensaje CAN recibido */
    CAN_MSG_NOT_RECEIVED   		/**< Mensaje CAN no recibido */
} can_rx_status_t;

/**
 * @brief Tipo de dato can_tx_status_t para estado de transmisión de mensaje CAN
 *
 */
typedef enum
{
    CAN_TX_READY = 0, 		/**< Listo para transmitir mensaje CAN */
    CAN_TX_NOT_READY   		/**< No listo para transmitir mensaje CAN */
} can_tx_status_t;

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

void CAN_HW_Init(void);

/***********************************************************************************************************************
 * Global variables declarations
 **********************************************************************************************************************/

/** Bandera mensaje recibido CAN */
extern can_rx_status_t flag_rx_can;

/** Bandera transmisión CAN */
extern can_tx_status_t flag_tx_can;

#endif /* _CAN_HW_H_ */
