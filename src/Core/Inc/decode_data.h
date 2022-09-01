/**
 * @file decode_data.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para decode_data.c
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _DECODE_DATA_H_
#define _DECODE_DATA_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* Application includes */
#include "buses.h"
#include "can_def.h"

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/**
 * @brief Tipo de dato decode_status_t para bandera de decodificación
 *
 */
typedef enum
{
    DECODIFICA = 0, 	/**< Valor para decodificar */
    NO_DECODIFICA   	/**< Valor para no decodificar */
} decode_status_t;

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal de decodificación de datos de bus de recepción CAN.
 *
 * Decodifica los datos que se reciben desde el bus CAN. Los datos decodificados quedan
 * guardados en estructuras de tipo rx_bms_vars_t, rx_dcdc_vars_t, rx_inversor_vars_t,
 * y rx_peripherals_vars_t, en el bus de datos.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void DECODE_DATA_Process(void);

/***********************************************************************************************************************
 * Global variables declarations
 **********************************************************************************************************************/

/**
 * @brief Bandera para ejecutar bloque de decodificación de datos
 *
 */
extern decode_status_t flag_decodificar;

#endif /* _DECODE_DATA_H_ */
