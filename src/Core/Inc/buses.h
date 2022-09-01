/**
 * @file buses.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para buses.c
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _BUSES_H_
#define _BUSES_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* Application includes */
#include "types.h"
#include "can_def.h"

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/**
 * @brief Bus 1: bus de variables internas
 *
 */
typedef struct bus1
{
    /* Variables modo de manejo y fallas */
    driving_mode_t          driving_mode;
    failure_t               failure;

    /* Variable velocidad [0:100] */
    float 				    velocidad_inversor;

    /* Estructuras con variables decodificadas de los módulos */
    rx_peripherals_vars_t   Rx_Peripherals;
    rx_bms_vars_t           Rx_Bms;
    rx_dcdc_vars_t          Rx_Dcdc;
    rx_inversor_vars_t      Rx_Inversor;

    /* Estructuras con estados de las variables decodificadas de los módulos */
    st_bms_vars_t           St_Bms;
    st_dcdc_vars_t          St_Dcdc;
    st_inversor_vars_t      St_Inversor;

    /* Variables estado general de cada módulo */
    module_status_t         bms_status;
    module_status_t         dcdc_status;
    module_status_t         inversor_status;

} typedef_bus1_t;

/**
 * @brief Bus 2: bus de variables que se transmiten por CAN
 *
 */
typedef struct bus2
{
    uint8_t  autokill;                  /**< CAN  0x001 */
    uint8_t  estado_manejo; 	        /**< CAN  0x010 */
    uint8_t  estado_falla; 		        /**< CAN  0x011 */
    uint8_t  nivel_velocidad;	        /**< CAN  0x012 */
    uint8_t  hombre_muerto;		        /**< CAN  0x013 */
    uint8_t  control_ok;		        /**< CAN  0x014 */

} typedef_bus2_t;

/**
 * @brief Bus 3: bus de variables que se reciben por CAN
 *
 */
typedef struct bus3
{
    uint8_t  pedal;						/**< CAN 0x002 */
    uint8_t  hombre_muerto;				/**< CAN 0x003 */
    uint8_t  botones_cambio_estado;		/**< CAN 0x004 */
    uint8_t  perifericos_ok;			/**< CAN 0x005 */

    uint8_t  voltaje_bms;				/**< CAN 0x020 */
    uint8_t  corriente_bms;				/**< CAN 0x021 */
    uint8_t  voltaje_min_celda_bms;		/**< CAN 0x022 */
    uint8_t  potencia_bms;				/**< CAN 0x023 */
    uint8_t  t_max_bms;					/**< CAN 0x024 */
    uint8_t  nivel_bateria_bms;			/**< CAN 0x025 */
    uint8_t  bms_ok;					/**< CAN 0x026 */

    uint8_t  voltaje_bateria_dcdc;		/**< CAN 0x030 */
    uint8_t  voltaje_salida_dcdc;       /**< CAN 0x031 */
    uint8_t  t_max_dcdc;				/**< CAN 0x032 */
    uint8_t  dcdc_ok;					/**< CAN 0x033 */
    uint8_t  potencia_dcdc;             /**< CAN 0x034 */

    uint8_t  velocidad_inv;				/**< CAN 0x040 */
    uint8_t  V_inv;						/**< CAN 0x041 */
    uint8_t  I_inv;						/**< CAN 0x042 */
    uint8_t  temp_max_inv;				/**< CAN 0x043 */
    uint8_t  temp_motor_inv;			/**< CAN 0x044 */
    uint8_t  potencia_inv;				/**< CAN 0x045 */
    uint8_t  inversor_ok;				/**< CAN 0x046 */

} typedef_bus3_t;

/***********************************************************************************************************************
 * Global variables declarations
 **********************************************************************************************************************/

/** @brief Bus 1: Bus de datos */
extern typedef_bus1_t bus_data;

/** @brief Bus 2: Bus de transmisión de datos CAN */
extern typedef_bus2_t bus_can_output;

/** @brief Bus 3: Bus de recepción de datos CAN */
extern typedef_bus3_t bus_can_input;

#endif /* _BUSES_H_ */
