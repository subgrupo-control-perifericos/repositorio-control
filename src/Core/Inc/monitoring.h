/**
 * @file monitoring.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para monitoring.c
 * @version 0.1
 * @date 2021-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _MONITORING_H_
#define _MONITORING_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* Application includes */
#include "monitoring_api.h"
#include "buses.h"

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal del bloque monitoreo de variables.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param   None
 * @retval  None
 */
void MONITORING_Process(void);

#endif /* _MONITORING_H_ */
