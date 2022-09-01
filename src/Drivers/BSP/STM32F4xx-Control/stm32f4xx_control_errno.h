/**
 * @file stm32f4xx_control_errno.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Códigos de error de driver BSP (board support package)
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _STM32F4XX_CONTROL_ERRNO_H_
#define _STM32F4XX_CONTROL_ERRNO_H_

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/* Common Error codes */

#define BSP_ERROR_NONE                         0
#define BSP_ERROR_NO_INIT                     -1
#define BSP_ERROR_WRONG_PARAM                 -2
#define BSP_ERROR_BUSY                        -3
#define BSP_ERROR_PERIPH_FAILURE              -4
#define BSP_ERROR_COMPONENT_FAILURE           -5
#define BSP_ERROR_UNKNOWN_FAILURE             -6
#define BSP_ERROR_UNKNOWN_COMPONENT           -7
#define BSP_ERROR_BUS_FAILURE                 -8
#define BSP_ERROR_CLOCK_FAILURE               -9
#define BSP_ERROR_MSP_FAILURE                 -10
#define BSP_ERROR_FEATURE_NOT_SUPPORTED       -11

#endif /* _STM32F4XX_CONTROL_ERRNO_H_ */
