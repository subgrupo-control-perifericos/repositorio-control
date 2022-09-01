/**
 * @file monitoring.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Implementación monitoreo de variables decodificadas
 * @version 0.1
 * @date 2021-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "monitoring.h"

/***********************************************************************************************************************
 * Private macros
 **********************************************************************************************************************/

/** @brief Define si usar feature monitoreo de las variables generales del vehículo o no */
#define USE_VEHICLE_VAR_MONITORING_FEATURE          0

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

#if USE_VEHICLE_VAR_MONITORING_FEATURE == 1
/*

PROBLEMA:

1. Estamos en SPORT...
BMS: 80 °C
DCDC: 78 °C
INVERSOR: 81 °C
Estas temperaturas para Sport son normales

2. Cambia a modo de manejo ECO...
BMS: 79 °C
DCDC: 77 °C
INVERSOR: 80 °C
Estas temperaturas para Eco no son normales

Puede generarse un estado de AUTOKILL!
Por qué? Porque en este caso, todos los módulos
están en condiciones de PROBLEM

*/

/* --------------- BMS LIMITS --------------- */

const rx_bms_limits_t bms_eco_limits =
{
    .MIN_nivel_bateria = 50.0,
    .REG_nivel_bateria = 60.0,
    .MAX_voltaje_bateria = 48.5,
    .MIN_voltaje_bateria = 47.5,
    .MAX_potencia = 545.0,
    .REG_potencia = 520.0
};

const rx_bms_limits_t bms_normal_limits =
{
    .MIN_nivel_bateria = 65.0,
    .REG_nivel_bateria = 70.0,
    .MAX_voltaje_bateria = 48.5,
    .MIN_voltaje_bateria = 47.5,
    .MAX_potencia = 545.0,
    .REG_potencia = 520.0
};

const rx_bms_limits_t bms_sport_limits =
{
    .MIN_nivel_bateria = 80.0,
    .REG_nivel_bateria = 83.0,
    .MAX_voltaje_bateria = 48.5,
    .MIN_voltaje_bateria = 47.5,
    .MAX_potencia = 545.0,
    .REG_potencia = 520.0
};

/* -------------- DCDC LIMITS -------------- */

const rx_dcdc_limits_t dcdc_eco_limits =
{
    .MAX_temp_max_mosfets = 75.0,
    .REG_temp_max_mosfets = 70.0,
    .MAX_voltaje_salida = 48.5,
    .MIN_voltaje_salida = 47.5
};

const rx_dcdc_limits_t dcdc_normal_limits =
{
    .MAX_temp_max_mosfets = 80.0,
    .REG_temp_max_mosfets = 75.0,
    .MAX_voltaje_salida = 60.5,
    .MIN_voltaje_salida = 59.5
};

const rx_dcdc_limits_t dcdc_sport_limits =
{
    .MAX_temp_max_mosfets = 85.0,
    .REG_temp_max_mosfets = 80.0,
    .MAX_voltaje_salida = 75.5,
    .MIN_voltaje_salida = 74.5
};

/* ------------ Inversor LIMITS ------------ */

const rx_inversor_limits_t inversor_eco_limits =
{
    .MAX_temp_max_mosfets = 75.0,
    .REG_temp_max_mosfets = 70.0,
    .MAX_voltaje_salida = 48.5,
    .MIN_voltaje_salida = 47.5
};

const rx_inversor_limits_t inversor_normal_limits =
{
    .MAX_temp_max_mosfets = 80.0,
    .REG_temp_max_mosfets = 75.0,
    .MAX_voltaje_salida = 60.5,
    .MIN_voltaje_salida = 59.5
};

const rx_inversor_limits_t inversor_sport_limits =
{
    .MAX_temp_max_mosfets = 85.0,
    .REG_temp_max_mosfets = 80.0,
    .MAX_voltaje_salida = 75.5,
    .MIN_voltaje_salida = 74.5
};

#endif /* USE_VEHICLE_VAR_MONITORING_FEATURE */

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

#if USE_VEHICLE_VAR_MONITORING_FEATURE == 1
static void MONITORING_Update_AnalogVariablesState(void);
static void MONITORING_Update_ModulesStatus(void);

#endif /* USE_VEHICLE_VAR_MONITORING_FEATURE */

static void MONITORING_Update_ReceivedModulesStatus(void);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función principal del bloque monitoreo de variables.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param   None
 * @retval  None
 */
void MONITORING_Process(void)
{
    MONITORING_Update_ReceivedModulesStatus();     	// actualiza estado recibido de los módulos (fallas internas)

#if USE_VEHICLE_VAR_MONITORING_FEATURE == 1
    MONITORING_Update_AnalogVariablesState();       // variables analógicas recibidas que dan información general del estado del vehículo
    MONITORING_Update_ModulesStatus();              // estado de los módulos de acuerdo al estado de las variables analógicas recibidas

#endif /* USE_VEHICLE_VAR_MONITORING_FEATURE */
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

/**
 * @brief Modules Received Status
 *
 * Estado general de los módulos de acuerdo a las variables de estado de módulo recibidas. Sintetizan las variables
 * internas y los estados de falla definidos internamente por cada módulo del vehículo.
 *
 */
static void MONITORING_Update_ReceivedModulesStatus(void)
{
    bus_data.bms_status = MONITORING_API_Get_Bms_ReceivedStatus(&bus_data.Rx_Bms);                  // actualiza variable estado del módulo BMS

    bus_data.dcdc_status = MONITORING_API_Get_Dcdc_ReceivedStatus(&bus_data.Rx_Dcdc);               // actualiza variable estado del módulo DCDC

    bus_data.inversor_status = MONITORING_API_Get_Inversor_ReceivedStatus(&bus_data.Rx_Inversor);   // actualiza variable estado del módulo inversor
}

#if USE_VEHICLE_VAR_MONITORING_FEATURE == 1
/**
 * @brief Vehicle Variables Monitoring
 *
 * Se realiza el monitoreo de las variables analógicas recibidas de los módulos. Estas variables analógicas se consideran
 * como variables generales del sistema que brindan información relevante del estado general del vehículo.
 *
 */
static void MONITORING_Update_AnalogVariablesState(void)
{

    switch (bus_data.driving_mode)
    {
    case kDRIVING_MODE_ECO:

        /* Actualiza estado de las variables del módulo BMS */
        MONITORING_API_Bms_VariableMonitoring(  &bus_data.Rx_Bms,
                                                &bus_data.St_Bms,
                                                &bms_eco_limits);

        /* Actualiza estado de las variables del módulo DCDC */
        MONITORING_API_Dcdc_VariableMonitoring( &bus_data.Rx_Dcdc,
                                                &bus_data.St_Dcdc,
                                                &dcdc_eco_limits);

        /* Actualiza estado de las variables del módulo inversor */
        MONITORING_API_Inversor_VariableMonitoring( &bus_data.Rx_Inversor,
                                                    &bus_data.St_Inversor,
                                                    &inversor_eco_limits);

        break;

    case kDRIVING_MODE_NORMAL:

        /* Actualiza estado de las variables del módulo BMS */
        MONITORING_API_Bms_VariableMonitoring(  &bus_data.Rx_Bms,
                                                &bus_data.St_Bms,
                                                &bms_normal_limits);

        /* Actualiza estado de las variables del módulo DCDC */
        MONITORING_API_Dcdc_VariableMonitoring( &bus_data.Rx_Dcdc,
                                                &bus_data.St_Dcdc,
                                                &dcdc_normal_limits);

        /* Actualiza estado de las variables del módulo inversor */
        MONITORING_API_Inversor_VariableMonitoring( &bus_data.Rx_Inversor,
                                                    &bus_data.St_Inversor,
                                                    &inversor_normal_limits);

        break;

    case kDRIVING_MODE_SPORT:

        /* Actualiza estado de las variables del módulo BMS */
        MONITORING_API_Bms_VariableMonitoring(  &bus_data.Rx_Bms,
                                                &bus_data.St_Bms,
                                                &bms_sport_limits);

        /* Actualiza estado de las variables del módulo DCDC */
        MONITORING_API_Dcdc_VariableMonitoring( &bus_data.Rx_Dcdc,
                                                &bus_data.St_Dcdc,
                                                &dcdc_sport_limits);

        /* Actualiza estado de las variables del módulo inversor */
        MONITORING_API_Inversor_VariableMonitoring( &bus_data.Rx_Inversor,
                                                    &bus_data.St_Inversor,
                                                    &inversor_sport_limits);

        break;

    default:
        break;
    }
}

/**
 * @brief Estado general de los módulos de acuerdo al estado de las variables analógicas recibidas
 *
 * A partir de los estados de las variables analógicas de los módulos, que se encuentran guardados en la estructuras  St_Bms, St_Dcdc,
 * St_Inversor, actualiza la variable de estado general de cada uno de los módulos (BMS, DCDC, e inversor).
 *
 */
static void MONITORING_Update_ModulesStatus(void)
{
	module_status_t analog_bms_status;
	module_status_t analog_dcdc_status;
	module_status_t analog_inversor_status;

    /* Las fallas internas tienen prioridad sobre el monitoreo de las variables del vehículo */
    if (bus_data.bms_status != kMODULE_STATUS_PROBLEM)
    {
    	analog_bms_status = MONITORING_API_Get_Bms_Status(&bus_data.St_Bms);

    	if( analog_bms_status != kMODULE_STATUS_DATA_PROBLEM)
    	{
    		bus_data.bms_status = analog_bms_status;				// actualiza variable estado del módulo BMS
    	}
    }

    if (bus_data.dcdc_status != kMODULE_STATUS_PROBLEM)
    {
    	analog_dcdc_status = MONITORING_API_Get_Dcdc_Status(&bus_data.St_Dcdc);

    	if( analog_dcdc_status != kMODULE_STATUS_DATA_PROBLEM)
    	{
    		bus_data.dcdc_status = analog_dcdc_status;				// actualiza variable estado del módulo DCDC
    	}
    }

    if (bus_data.inversor_status != kMODULE_STATUS_PROBLEM)
    {
    	analog_inversor_status = MONITORING_API_Get_Inversor_Status(&bus_data.St_Inversor);

    	if( analog_inversor_status != kMODULE_STATUS_DATA_PROBLEM)
    	{
    		bus_data.inversor_status = analog_inversor_status;		// actualiza variable estado del módulo Inversor
    	}
    }
}

#endif /* USE_VEHICLE_VAR_MONITORING_FEATURE */
