/**
 * @file indicators.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para indicators.c
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _INDICATORS_H_
#define _INDICATORS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* Application includes */
#include "buses.h"

/* BSP (board support package) include */
#include "stm32f4xx_control.h"

/* STM32 HAL include */
#include "main.h"

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal bloque generación de indicadores.
 * 
 * Por defecto, actualiza LEDs de acuerdo al modo de manejo actual.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void INDICATORS_Process(void);

/**
 * @brief Actualiza LEDs para indicar confirmación de los módulos durante inicialización
 * 
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void INDICATORS_Update_ModulesLEDs(void);

/**
 * @brief Indicación de que la tarjeta ha finalizado la inicialización.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void INDICATORS_Finish_StartUp(void);


#endif /* _INDICATORS_H_ */
