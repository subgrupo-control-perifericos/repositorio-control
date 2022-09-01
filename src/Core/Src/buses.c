/**
 * @file buses.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Buses arquitectura de firmware de Control
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "buses.h"

/***********************************************************************************************************************
 * Buses initialization
 **********************************************************************************************************************/

/* Inicialización de bus de datos (bus 1) */
typedef_bus1_t bus_data =
{
	/* Variables modo de manejo y fallas */
	.driving_mode = kDRIVING_MODE_NORMAL,
	.failure = kFAILURE_CAUTION1,

	/* Variable velocidad [0:100] */
	.velocidad_inversor = 0U,

	/* Estructuras con variables decodificadas de los módulos */
	.Rx_Peripherals =
	{
		.botones_cambio_estado = kBTN_NONE,
		.hombre_muerto = kHOMBRE_MUERTO_OFF,
		.perifericos_ok = kMODULE_INFO_ERROR
	},
	.Rx_Bms = {.bms_ok = kMODULE_INFO_ERROR},
	.Rx_Dcdc = {.dcdc_ok = kMODULE_INFO_ERROR},
	.Rx_Inversor = {.inversor_ok = kMODULE_INFO_ERROR},

	/* Estructuras con estados de las variables decodificadas de los módulos */
	.St_Bms = {kVAR_STATE_DATA_PROBLEM},
	.St_Dcdc = {kVAR_STATE_DATA_PROBLEM},
	.St_Inversor = {kVAR_STATE_DATA_PROBLEM},

	/* Variables estado general de cada módulo */
	.bms_status = kMODULE_STATUS_DATA_PROBLEM,
	.dcdc_status = kMODULE_STATUS_DATA_PROBLEM,
	.inversor_status = kMODULE_STATUS_DATA_PROBLEM,
};

/* Inicialización de bus de salida CAN (bus 2) */
typedef_bus2_t bus_can_output =
{
	.autokill = CAN_VALUE_AUTOKILL_OFF,
	.estado_manejo = CAN_VALUE_DRIVING_MODE_NORMAL,
	.estado_falla = CAN_VALUE_FAILURE_CAUTION1,
	.nivel_velocidad = 0,
	.hombre_muerto = CAN_VALUE_HOMBRE_MUERTO_OFF,
	.control_ok = CAN_VALUE_MODULE_IDLE
};

/* Inicialización de bus de recepción CAN (bus 3) */
typedef_bus3_t bus_can_input =
{
	.bms_ok = CAN_VALUE_MODULE_IDLE,
	.dcdc_ok = CAN_VALUE_MODULE_IDLE,
	.inversor_ok = CAN_VALUE_MODULE_OK,
	.perifericos_ok = CAN_VALUE_MODULE_IDLE,

	.hombre_muerto = CAN_VALUE_HOMBRE_MUERTO_OFF,
	.botones_cambio_estado = CAN_VALUE_BTN_NONE
};
