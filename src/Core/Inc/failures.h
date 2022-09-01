/**
 * @file failures.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para failures.c
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _FAILURES_H_
#define _FAILURES_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* Application includes */
#include "buses.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public functions prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal máquina de fallas.
 *
 * Determina estado general de cada uno de los modulos segun el estado de las
 * variables decodificadas.
 *
 * Llama a la función máquina de estados de fallas.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void FAILURES_Process(void);

#endif /* _FAILURES_H_ */
