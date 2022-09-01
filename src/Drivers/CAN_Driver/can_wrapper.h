/**
 * @file can_wrapper.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para can_wrapper.c
 * @version 0.1
 * @date 2022-18-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _CAN_WRAPPER_H_
#define _CAN_WRAPPER_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* CAN driver include */
#include "can_api.h"

/* CAN application definitions include */
#include "can_def.h"

/* STM32 specific hardware configuration includes */
#include "can.h"
#include "tim.h"

/* STM32 HAL include */
#include "main.h"

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función wrapper inicialización de periférico CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param   None
 * @retval  can_status_t
 */
can_status_t CAN_Wrapper_Init(void);

/**
 * @brief Función wrapper transmisión de datos CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param id Standard identifier
 * @param ide Type of identifier
 * @param rtr Type of frame
 * @param dlc Length of frame
 * @param data Data to transmit
 * @retval None
 */
can_status_t CAN_Wrapper_TransmitData(uint32_t id, uint8_t ide, uint8_t rtr, uint8_t dlc, uint8_t *data);

/**
 * @brief Función wrapper recepción de datos CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param id Received identifier
 * @param data Received data
 * @retval  can_status_t
 */
can_status_t CAN_Wrapper_ReceiveData(uint32_t *id, uint8_t *data);

/**
 * @brief Función wrapper conteo dato recibido por CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @return can_status_t
 */
can_status_t CAN_Wrapper_DataCount(void);


#endif /* _CAN_WRAPPER_H_ */
