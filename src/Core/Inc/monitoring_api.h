/**
 * @file monitoring_api.h
 * @author Subgrupo Control
 * @brief Archivo header para monitoring_api.c
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _MONITORING_API_H
#define _MONITORING_API_H

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

/* Application includes */
#include "types.h"

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/**
 * @brief Tipo de dato estructura límites para variables decodificadas del BMS.
 *
 */
typedef struct
{
    float MIN_nivel_bateria;
    float REG_nivel_bateria;

    float MAX_voltaje_bateria;
    float MIN_voltaje_bateria;

    float MAX_potencia;
    float REG_potencia;

} rx_bms_limits_t;

/**
 * @brief Tipo de dato estructura límites para variables decodificadas del DCDC.
 *
 */
typedef struct
{
    float MAX_temp_max_mosfets;
    float REG_temp_max_mosfets;

    float MAX_voltaje_salida;
    float MIN_voltaje_salida;

} rx_dcdc_limits_t;

/**
 * @brief Tipo de dato estructura límites para variables decodificadas del inversor.
 *
 */
typedef struct
{
    float MAX_temp_max_mosfets;
    float REG_temp_max_mosfets;

    float MAX_voltaje_salida;
    float MIN_voltaje_salida;

} rx_inversor_limits_t;

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Monitoreo de las variables del BMS. Module Analog Variable -> Variable State
 *
 * @param Rx_Bms Puntero a estructura con variables decodificadas del BMS
 * @param St_Bms Puntero a estructura con estado de variables decodificadas del BMS
 * @param bms_limits Puntero a estructura con los límites de las variables del BMS
 */
void MONITORING_API_Bms_VariableMonitoring( rx_bms_vars_t* Rx_Bms,
                                            st_bms_vars_t* St_Bms,
                                            const rx_bms_limits_t* bms_limits);

/**
 * @brief Monitoreo de las variables del DCDC. Module Analog Variable -> Variable State
 *
 * @param Rx_Dcdc Puntero a estructura con variables decodificadas del DCDC
 * @param St_Dcdc Puntero a estructura con estado de variables decodificadas del DCDC
 * @param dcdc_limits Puntero a estructura con los límites de las variables del DCDC
 */
void MONITORING_API_Dcdc_VariableMonitoring(    rx_dcdc_vars_t* Rx_Dcdc,
                                                st_dcdc_vars_t* St_Dcdc,
                                                const rx_dcdc_limits_t* dcdc_limits);

/**
 * @brief Monitoreo de las variables del inversor. Module Analog Variable -> Variable State
 *
 * @param Rx_Inversor Puntero a estructura con variables decodificadas del inversor
 * @param St_Inversor Puntero a estructura con estado de variables decodificadas del inversor
 * @param inversor_limits Puntero a estructura con los límites de las variables del inversor
 */
void MONITORING_API_Inversor_VariableMonitoring(    rx_inversor_vars_t* Rx_Inversor,
                                                    st_inversor_vars_t* St_Inversor,
                                                    const rx_inversor_limits_t* inversor_limits);

/* ------------------------------------------------------------------------------------------------------------------ */

/**
 * @brief Retorna estado del módulo BMS de acuerdo al valor de la variable de estado de módulo recibida (bms_ok).
 *
 * @param Rx_Bms Puntero a estructura con variables decodificadas del BMS
 * @return module_status_t
 */
module_status_t MONITORING_API_Get_Bms_ReceivedStatus( rx_bms_vars_t* Rx_Bms);

/**
 * @brief Retorna estado del módulo DCDC de acuerdo al valor de la variable de estado de módulo recibida (dcdc_ok).
 *
 * @param Rx_Dcdc Puntero a estructura con variables decodificadas del DCDC
 * @return module_status_t
 */
module_status_t MONITORING_API_Get_Dcdc_ReceivedStatus( rx_dcdc_vars_t* Rx_Dcdc);

/**
 * @brief Retorna estado del módulo Inversor de acuerdo al valor de la variable de estado de módulo recibida (inversor_ok).
 *
 * @param Rx_Inversor Puntero a estructura con variables decodificadas del inversor
 * @return module_status_t
 */
module_status_t MONITORING_API_Get_Inversor_ReceivedStatus( rx_inversor_vars_t* Rx_Inversor);

/* ------------------------------------------------------------------------------------------------------------------ */

/**
 * @brief Determina el estado general del módulo BMS de acuerdo al estado de las variables analógicas del módulo.
 *
 * A partir de los estados de las variables decodificadas guardados en la estructura
 * St_Bms del bus_data, actualiza el estado general del módulo BMS.
 *
 * @param St_Bms Puntero a estructura con estado de variables decodificadas del BMS
 * @return module_status_t Estado del módulo BMS
 */
module_status_t MONITORING_API_Get_Bms_Status( st_bms_vars_t* St_Bms);

/**
 * @brief Determina el estado del general módulo DCDC de acuerdo al estado de las variables analógicas del módulo.
 *
 * A partir de los estados de las variables decodificadas guardados en la estructura
 * St_Dcdc del bus_data, actualiza el estado general del módulo DCDC.
 *
 * @param St_Dcdc Puntero a estructura con estado de variables decodificadas del DCDC
 * @return module_status_t Estado del módulo DCDC
 */
module_status_t MONITORING_API_Get_Dcdc_Status( st_dcdc_vars_t* St_Dcdc);

/**
 * @brief Determina el estado general del módulo inversor de acuerdo al estado de las variables analógicas del módulo.
 *
 * A partir de los estados de las variables decodificadas guardados en la estructura
 * St_Inversor del bus_data, actualiza el estado general del módulo inversor.
 *
 * @param St_Inversor Puntero a estructura con estado de variables decodificadas del inversor
 * @return module_status_t Estado del módulo inversor
 */
module_status_t MONITORING_API_Get_Inversor_Status( st_inversor_vars_t* St_Inversor);

#endif /* _MONITORING_API_H */
