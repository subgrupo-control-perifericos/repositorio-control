/**
 * @file monitoring_api.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Implementación API para monitoreo de variables y módulos
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "monitoring_api.h"

/***********************************************************************************************************************
 * Public functions implementation
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
                                            const rx_bms_limits_t* bms_limits)
{
    /* NIVEL DE LA BATERÍA */

    if( Rx_Bms->nivel_bateria > bms_limits->REG_nivel_bateria)
    {
        St_Bms->nivel_bateria = kVAR_STATE_OK;
    }
    if( Rx_Bms->nivel_bateria < bms_limits->REG_nivel_bateria)
    {
        St_Bms->nivel_bateria = kVAR_STATE_REGULAR;
    }
    if( Rx_Bms->nivel_bateria < bms_limits->MIN_nivel_bateria)
    {
        St_Bms->nivel_bateria = kVAR_STATE_PROBLEM;
    }
	if(Rx_Bms->nivel_bateria == 0)
	{
		St_Bms->nivel_bateria = kVAR_STATE_DATA_PROBLEM;
	}

    /* VOLTAJE DE LA BATERÍA */
    if( Rx_Bms->voltaje < bms_limits->MAX_voltaje_bateria &&
        Rx_Bms->voltaje > bms_limits->MIN_voltaje_bateria)
    {
        St_Bms->voltaje = kVAR_STATE_OK;
    }
    else
    {
        St_Bms->voltaje = kVAR_STATE_PROBLEM;
    }
	if(Rx_Bms->voltaje == 0)
	{
		St_Bms->voltaje = kVAR_STATE_DATA_PROBLEM;
	}

    /* POTENCIA DE SALIDA */
    if( Rx_Bms->potencia < bms_limits->MAX_potencia &&
        Rx_Bms->potencia < bms_limits->REG_potencia)
    {
        St_Bms->potencia = kVAR_STATE_OK;
    }
    else if( Rx_Bms->potencia > bms_limits->REG_potencia &&
             Rx_Bms->potencia < bms_limits->MAX_potencia)
    {
        St_Bms->potencia = kVAR_STATE_REGULAR;
    }
    else if( Rx_Bms->potencia > bms_limits->MAX_potencia)
    {
        St_Bms->potencia = kVAR_STATE_PROBLEM;
    }
	if(Rx_Bms->potencia == 0)
	{
		St_Bms->potencia = kVAR_STATE_DATA_PROBLEM;
	}
}

/**
 * @brief Monitoreo de las variables del DCDC. Module Analog Variable -> Variable State
 *
 * @param Rx_Dcdc Puntero a estructura con variables decodificadas del DCDC
 * @param St_Dcdc Puntero a estructura con estado de variables decodificadas del DCDC
 * @param dcdc_limits Puntero a estructura con los límites de las variables del DCDC
 */
void MONITORING_API_Dcdc_VariableMonitoring(    rx_dcdc_vars_t* Rx_Dcdc,
                                                st_dcdc_vars_t* St_Dcdc,
                                                const rx_dcdc_limits_t* dcdc_limits)
{
    /* TEMPERATURA MÁXIMA DE MOSFETS */
    if( Rx_Dcdc->t_max < dcdc_limits->MAX_temp_max_mosfets &&
        Rx_Dcdc->t_max < dcdc_limits->REG_temp_max_mosfets)
    {
        St_Dcdc->t_max = kVAR_STATE_OK;
    }
    else if( Rx_Dcdc->t_max > dcdc_limits->REG_temp_max_mosfets &&
             Rx_Dcdc->t_max < dcdc_limits->MAX_temp_max_mosfets)
    {
        St_Dcdc->t_max = kVAR_STATE_REGULAR;
    }
    else if( Rx_Dcdc->t_max > dcdc_limits->MAX_temp_max_mosfets)
    {
        St_Dcdc->t_max = kVAR_STATE_PROBLEM;
    }
	if(Rx_Dcdc->t_max == 0)
	{
		St_Dcdc->t_max = kVAR_STATE_DATA_PROBLEM;
	}

    /* VOLTAJE DE SALIDA */
    if( Rx_Dcdc->voltaje_salida < dcdc_limits->MAX_voltaje_salida &&
        Rx_Dcdc->voltaje_salida > dcdc_limits->MIN_voltaje_salida)
    {
        St_Dcdc->voltaje_salida = kVAR_STATE_OK;
    }
    else
    {
        St_Dcdc->voltaje_salida = kVAR_STATE_PROBLEM;
    }
	if(Rx_Dcdc->voltaje_salida == 0)
	{
		St_Dcdc->voltaje_salida = kVAR_STATE_DATA_PROBLEM;
	}
    /* ... */
}

/**
 * @brief Monitoreo de las variables del inversor. Module Analog Variable -> Variable State
 *
 * @param Rx_Inversor Puntero a estructura con variables decodificadas del inversor
 * @param St_Inversor Puntero a estructura con estado de variables decodificadas del inversor
 * @param inversor_limits Puntero a estructura con los límites de las variables del inversor
 */
void MONITORING_API_Inversor_VariableMonitoring(    rx_inversor_vars_t* Rx_Inversor,
                                                    st_inversor_vars_t* St_Inversor,
                                                    const rx_inversor_limits_t* inversor_limits)
{
    /* TEMPERATURA MÁXIMA DE MOSFETS */
    if( Rx_Inversor->temp_max < inversor_limits->MAX_temp_max_mosfets &&
        Rx_Inversor->temp_max < inversor_limits->REG_temp_max_mosfets)
    {
        St_Inversor->temp_max = kVAR_STATE_OK;
    }
    else if( Rx_Inversor->temp_max > inversor_limits->REG_temp_max_mosfets &&
             Rx_Inversor->temp_max < inversor_limits->MAX_temp_max_mosfets)
    {
        St_Inversor->temp_max = kVAR_STATE_REGULAR;
    }
    else if( Rx_Inversor->temp_max > inversor_limits->MAX_temp_max_mosfets)
    {
        St_Inversor->temp_max = kVAR_STATE_PROBLEM;
    }
	if(Rx_Inversor->temp_max == 0)
	{
		St_Inversor->temp_max = kVAR_STATE_DATA_PROBLEM;
	}

    /* VOLTAJE DE SALIDA */
    if( Rx_Inversor->V < inversor_limits->MAX_voltaje_salida &&
        Rx_Inversor->V > inversor_limits->MIN_voltaje_salida)
    {
        St_Inversor->V = kVAR_STATE_OK;
    }
    else
    {
        St_Inversor->V = kVAR_STATE_PROBLEM;
    }
	if(Rx_Inversor->V == 0)
	{
		St_Inversor->V = kVAR_STATE_DATA_PROBLEM;
	}
    /* ... */
}

/* ------------------------------------------------------------------------------------------------------------------ */

/**
 * @brief Retorna estado del módulo BMS de acuerdo al valor de la variable de estado de módulo recibida (bms_ok).
 *
 * @param Rx_Bms Puntero a estructura con variables decodificadas del BMS
 * @return module_status_t
 */
module_status_t MONITORING_API_Get_Bms_ReceivedStatus(rx_bms_vars_t* Rx_Bms)
{
    if (Rx_Bms->bms_ok == kMODULE_INFO_OK)       // verifica valor de la variable bms_ok
    {
        return kMODULE_STATUS_OK;                // retorna estado del módulo BMS
    }

    /* El módulo BMS está en algún estado de falla? */

    else if (Rx_Bms->bms_ok == kMODULE_INFO_ERROR)    	// verifica valor de la variable bms_ok
    {
        return kMODULE_STATUS_PROBLEM;           		// retorna estado del módulo BMS
    }

    else
    {
    	return kMODULE_STATUS_DATA_PROBLEM;
    }
}

/**
 * @brief Retorna estado del módulo DCDC de acuerdo al valor de la variable de estado de módulo recibida (dcdc_ok).
 *
 * @param Rx_Dcdc Puntero a estructura con variables decodificadas del DCDC
 * @return module_status_t
 */
module_status_t MONITORING_API_Get_Dcdc_ReceivedStatus(rx_dcdc_vars_t* Rx_Dcdc)
{
    if (Rx_Dcdc->dcdc_ok == kMODULE_INFO_OK)     // verifica valor de la variable dcdc_ok
    {
        return kMODULE_STATUS_OK;                // retorna estado del módulo DCDC
    }

    /* El módulo DCDC está en algún estado de falla? */

    else if (Rx_Dcdc->dcdc_ok == kMODULE_INFO_ERROR)    	// verifica valor de la variable dcdc_ok
    {
        return kMODULE_STATUS_PROBLEM;               		// retorna estado del módulo DCDC
    }

    else
    {
    	return kMODULE_STATUS_DATA_PROBLEM;
    }
}

/**
 * @brief Retorna estado del módulo Inversor de acuerdo al valor de la variable de estado de módulo recibida (inversor_ok).
 *
 * @param Rx_Inversor Puntero a estructura con variables decodificadas del inversor
 * @return module_status_t
 */
module_status_t MONITORING_API_Get_Inversor_ReceivedStatus(rx_inversor_vars_t* Rx_Inversor)
{
    if (Rx_Inversor->inversor_ok == kMODULE_INFO_OK)     // verifica valor de la variable inversor_ok
    {
        return kMODULE_STATUS_OK;                        // retorna estado del módulo inversor
    }

    /* El módulo inversor está en algún estado de falla? */

    else if (Rx_Inversor->inversor_ok == kMODULE_INFO_ERROR)  	// verifica valor de la variable inversor_ok
    {
        return kMODULE_STATUS_PROBLEM;                       	// retorna estado del módulo inversor
    }

    else
    {
    	return kMODULE_STATUS_DATA_PROBLEM;
    }
}

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
module_status_t MONITORING_API_Get_Bms_Status(st_bms_vars_t* St_Bms)
{
    /* condición OK */
    if (St_Bms->nivel_bateria == kVAR_STATE_OK
        && St_Bms->voltaje == kVAR_STATE_OK
        && St_Bms->potencia == kVAR_STATE_OK)
    {
        return kMODULE_STATUS_OK;
    }

    /* condición REGULAR */
    else if (St_Bms->nivel_bateria == kVAR_STATE_REGULAR
        || St_Bms->potencia == kVAR_STATE_REGULAR
        || St_Bms->voltaje == kVAR_STATE_REGULAR)
    {
        return kMODULE_STATUS_REGULAR;
    }

    /* condición PROBLEM */
    else if (St_Bms->nivel_bateria == kVAR_STATE_PROBLEM
        || St_Bms->potencia == kVAR_STATE_PROBLEM
        || St_Bms->voltaje == kVAR_STATE_PROBLEM)
    {
        return kMODULE_STATUS_PROBLEM;
    }

    else
    {
    	return kMODULE_STATUS_DATA_PROBLEM;
    }
}

/**
 * @brief Determina el estado del general módulo DCDC de acuerdo al estado de las variables analógicas del módulo.
 *
 * A partir de los estados de las variables decodificadas guardados en la estructura
 * St_Dcdc del bus_data, actualiza el estado general del módulo DCDC.
 *
 * @param St_Dcdc Puntero a estructura con estado de variables decodificadas del DCDC
 * @return module_status_t Estado del módulo DCDC
 */
module_status_t MONITORING_API_Get_Dcdc_Status(st_dcdc_vars_t* St_Dcdc)
{
    /* condición OK */
    if (St_Dcdc->voltaje_salida == kVAR_STATE_OK
        && St_Dcdc->t_max == kVAR_STATE_OK)
    {
        return kMODULE_STATUS_OK;
    }

    /* condición REGULAR */
    else if (St_Dcdc->voltaje_salida == kVAR_STATE_REGULAR
            || St_Dcdc->t_max == kVAR_STATE_REGULAR)
    {
        return kMODULE_STATUS_REGULAR;
    }

    /* condición PROBLEM */
    else if (St_Dcdc->voltaje_salida == kVAR_STATE_PROBLEM
            || St_Dcdc->t_max == kVAR_STATE_PROBLEM)
    {
        return kMODULE_STATUS_PROBLEM;
    }

    else
    {
    	return kMODULE_STATUS_DATA_PROBLEM;
    }
}

/**
 * @brief Determina el estado general del módulo inversor de acuerdo al estado de las variables analógicas del módulo.
 *
 * A partir de los estados de las variables decodificadas guardados en la estructura
 * St_Inversor del bus_data, actualiza el estado general del módulo inversor.
 *
 * @param St_Inversor Puntero a estructura con estado de variables decodificadas del inversor
 * @return module_status_t Estado del módulo inversor
 */
module_status_t MONITORING_API_Get_Inversor_Status(st_inversor_vars_t* St_Inversor)
{
    /* condición OK */
    if (St_Inversor->V == kVAR_STATE_OK
        && St_Inversor->temp_max == kVAR_STATE_OK)
    {
        return kMODULE_STATUS_OK;
    }

    /* condición REGULAR */
    else if (St_Inversor->V == kVAR_STATE_REGULAR
        || St_Inversor->temp_max == kVAR_STATE_REGULAR)
    {
        return kMODULE_STATUS_REGULAR;
    }

    /* condición PROBLEM */
    else if (St_Inversor->V == kVAR_STATE_PROBLEM
        || St_Inversor->temp_max == kVAR_STATE_PROBLEM)
    {
        return kMODULE_STATUS_PROBLEM;
    }

    else
    {
    	return kMODULE_STATUS_DATA_PROBLEM;
    }
}
