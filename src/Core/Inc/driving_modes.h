/**
 * @file driving_modes.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para driving_modes.c
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _DRIVING_MODES_H_
#define _DRIVING_MODES_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* Application includes */
#include "buses.h"
#include "indicators.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal máquina de modos de manejo.
 *
 * Llama a la función máquina de estados de modos de manejo. 
 * 
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void DRIVING_MODES_Process(void);

#endif /* _DRIVING_MODES_H_ */
