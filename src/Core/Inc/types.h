/**
 * @file types.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Declaraciones tipos de datos generales
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _TYPES_H_
#define _TYPES_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/**
 * @brief Tipo de dato para variable info de cada módulo
 *
 */
typedef enum
{
    kMODULE_INFO_OK,                /**< Modulo OK */
	kMODULE_INFO_ERROR              /**< Modulo ERROR */
} module_info_t;

/**
 * @brief Tipo de dato para variable analogica decodificada
 *
 */
typedef float rx_var_t;

/**
 * @brief Tipo de dato para estado de variable analogica
 *
 */
typedef enum
{
    kVAR_STATE_DATA_PROBLEM = 0,    /**< Problema con el dato */
    kVAR_STATE_OK,                  /**< Estado de variable OK */
    kVAR_STATE_REGULAR,             /**< Estado de variable REGULAR */
    kVAR_STATE_PROBLEM,             /**< Estado de variable PROBLEM */
} var_state_t;

/**
 * @brief Tipo de dato para estado de módulo
 *
 */
typedef enum
{
    kMODULE_STATUS_DATA_PROBLEM = 0,
    kMODULE_STATUS_OK,
    kMODULE_STATUS_REGULAR,
    kMODULE_STATUS_PROBLEM,
} module_status_t;

/********************************************************************************
 *                                CONTROL                                       *
 *******************************************************************************/

/**
 * @brief Tipo de dato para modos de manejo
 *
 */
typedef enum
{
    kDRIVING_MODE_ECO,      /**< Modo de manejo ECO */
	kDRIVING_MODE_NORMAL,   /**< Modo de manejo NORMAL */
	kDRIVING_MODE_SPORT     /**< Modo de manejo SPORT */
} driving_mode_t;

/**
 * @brief Tipo de dato para fallas
 *
 */
typedef enum
{       
	kFAILURE_OK,            /**< Falla OK */
	kFAILURE_CAUTION1,      /**< Falla CAUTION1 */
	kFAILURE_CAUTION2,      /**< Falla CAUTION1 */
	kFAILURE_AUTOKILL       /**< Falla AUTOKILL */
} failure_t;

/********************************************************************************
 *                              PERIFERICOS                                     *
 *******************************************************************************/

/**
 * @brief Tipo de dato para botones de modo de manejo
 *
 */
typedef enum
{
	kBTN_NONE = 0,
	kBTN_ECO,
	kBTN_NORMAL,
	kBTN_SPORT
} btn_modo_manejo_t;

/**
 * @brief Tipo de dato para estado de hombre muerto
 *
 */
typedef enum
{
	kHOMBRE_MUERTO_OFF = 0,
	kHOMBRE_MUERTO_ON
} hm_state_t;

/**
 * @brief Tipo de dato estructura para variables decodificadas de Periféricos
 *
 */
typedef struct
{
    rx_var_t            pedal;
    hm_state_t          hombre_muerto;
    btn_modo_manejo_t   botones_cambio_estado;

    module_info_t       perifericos_ok;

} rx_peripherals_vars_t;

/********************************************************************************
 *                                   BMS                                        *
 *******************************************************************************/

/**
 * @brief Tipo de dato estructura para variables decodificadas de BMS
 *
 */
typedef struct
{
    rx_var_t        voltaje;
    rx_var_t        corriente;
    rx_var_t        voltaje_min_celda;
    rx_var_t        potencia;
    rx_var_t        t_max;
    rx_var_t        nivel_bateria;

    module_info_t   bms_ok;

} rx_bms_vars_t;

/**
 * @brief Tipo de dato estructura para estado de las variables de BMS
 *
 */
typedef struct
{
    var_state_t     voltaje;
    var_state_t     corriente;
    var_state_t     voltaje_min_celda;
    var_state_t     potencia;
    var_state_t     t_max;
    var_state_t     nivel_bateria;

} st_bms_vars_t;

/********************************************************************************
 *                                   DCDC                                       *
 *******************************************************************************/

/**
 * @brief Tipo de dato estructura para variables decodificadas de DCDC
 *
 */
typedef struct
{
    rx_var_t        voltaje_bateria;
    rx_var_t        voltaje_salida;
    rx_var_t        t_max;
    rx_var_t        potencia;

    module_info_t   dcdc_ok;

} rx_dcdc_vars_t;

/**
 * @brief Tipo de dato estructura para estado de las variables de DCDC
 *
 */
typedef struct
{
    var_state_t     voltaje_bateria;
    var_state_t     voltaje_salida;
    var_state_t     t_max;
    var_state_t     potencia;

} st_dcdc_vars_t;

/********************************************************************************
 *                                  INVERSOR                                    *
 *******************************************************************************/

/**
 * @brief Tipo de dato estructura para variables decodificadas de Inversor
 *
 */
typedef struct
{
    rx_var_t        velocidad;
    rx_var_t        V;
    rx_var_t        I;
    rx_var_t        temp_max;
    rx_var_t        temp_motor;
    rx_var_t        potencia;

    module_info_t   inversor_ok;

} rx_inversor_vars_t;

/**
 * @brief Tipo de dato estructura para estado de las variables de Inversor
 *
 */
typedef struct
{
    var_state_t     velocidad;
    var_state_t     V;
    var_state_t     I;
    var_state_t     temp_max;
    var_state_t     temp_motor;
    var_state_t     potencia;

} st_inversor_vars_t;

#endif /* _TYPES_H_ */
