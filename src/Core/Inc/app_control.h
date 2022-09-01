/**
 * @file app_control.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para app_control.c
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _APP_CONTROL_H_
#define _APP_CONTROL_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* BSP (board support package) include */
#include "stm32f4xx_control.h"

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

void MX_APP_Init(void);
void MX_APP_Process(void);

#endif /* _APP_CONTROL_H_ */
