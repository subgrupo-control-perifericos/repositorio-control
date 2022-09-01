/**
 * @file can_app.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para can_app.c
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef _CAN_APP_H_
#define _CAN_APP_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* CAN driver include */
#include "can_api.h"

/* CAN application includes */
#include "can_hw.h"
#include "can_def.h"

/* Application includes */
#include "decode_data.h"
#include "buses.h"

/* BSP (board support package) include */
#include "stm32f4xx_control.h"

/* STM32 HAL include */
#include "main.h"

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal de CAN a nivel de aplicación.
 *
 * Guarda mensaje CAN recibido en bus de entrada CAN cuando se activa
 * bandera de recepción. Envía datos de bus de salida CAN cuando se
 * activa bandera de transmisión.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void CAN_APP_Process(void);

/**
 * @brief Función de envío de datos de bus de salida CAN a módulo CAN.
 *
 * Realiza el envío de las variables que se encuentran en el bus de salida CAN a módulo CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param bus_can_output Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 * @retval None
 */
void CAN_APP_Send_BusData(typedef_bus2_t *bus_can_output);

/**
 * @brief Función guardar mensaje CAN recibido en bus de entrada CAN.
 *
 * Según standard identifier que se recibió, guarda dato en la variable correspondiente
 * del bus de recepción CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void CAN_APP_Store_ReceivedMessage(void);

#endif /* _CAN_APP_H_ */
