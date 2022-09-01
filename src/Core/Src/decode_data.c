/**
 * @file decode_data.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Decodificación de datos provenientes de CAN
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "decode_data.h"

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

/** @brief Bandera para ejecutar bloque de decodificación de datos */
decode_status_t flag_decodificar = NO_DECODIFICA;

/* Puntero a estructura de tipo rx_peripherals_vars_t que contiene los valores de las variables decodificadas de Periféricos */
static rx_peripherals_vars_t* Rx_Peripherals = &bus_data.Rx_Peripherals;

/* Puntero a estructura de tipo rx_bms_vars_t que contiene los valores de las variables decodificadas de BMS */
static rx_bms_vars_t* Rx_Bms = &bus_data.Rx_Bms;

/* Puntero a estructura de tipo rx_dcdc_vars_t que contiene los valores de las variables decodificadas de DCDC */
static rx_dcdc_vars_t* Rx_Dcdc = &bus_data.Rx_Dcdc;

/* Puntero a estructura de tipo rx_inversor_vars_t que contiene los valores de las variables decodificadas de Inversor */
static rx_inversor_vars_t* Rx_Inversor = &bus_data.Rx_Inversor;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void DECODE_DATA_Decode_Bms(void);

static void DECODE_DATA_Decode_Dcdc(void);

static void DECODE_DATA_Decode_Inversor(void);

static void DECODE_DATA_Decode_Perifericos(void);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función principal de decodificación de datos de bus de recepción CAN.
 *
 * Decodifica los datos que se reciben desde el bus CAN. Los datos decodificados quedan
 * guardados en estructuras de tipo rx_bms_vars_t, rx_dcdc_vars_t, rx_inversor_vars_t,
 * y rx_peripherals_vars_t, en el bus de datos.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void DECODE_DATA_Process(void)
{
    if (flag_decodificar == DECODIFICA)
    {
    	DECODE_DATA_Decode_Bms();
        DECODE_DATA_Decode_Dcdc();
    	DECODE_DATA_Decode_Inversor();
        DECODE_DATA_Decode_Perifericos();

        flag_decodificar = NO_DECODIFICA;
    }
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

/**
 * @brief Decodifica los datos de BMS
 *
 * Decodifica las variables que se reciben de BMS por CAN y guarda
 * los datos en la estructura Rx_Bms del tipo rx_bms_vars_t y que
 * se encuentra en el bus_data.
 *
 */
static void DECODE_DATA_Decode_Bms(void)
{
    /* Decodifica info de BMS */
    switch (bus_can_input.bms_ok)
    {
    case CAN_VALUE_MODULE_OK:
    	Rx_Bms->bms_ok = kMODULE_INFO_OK;
        break;
    case CAN_VALUE_MODULE_ERROR:
    	Rx_Bms->bms_ok = kMODULE_INFO_ERROR;
        break;
    }

    /* Decodifica las variables analógicas de BMS */
    Rx_Bms->voltaje = (rx_var_t)bus_can_input.voltaje_bms / 2.0;
    Rx_Bms->corriente = (rx_var_t)bus_can_input.corriente_bms;
    Rx_Bms->voltaje_min_celda = (rx_var_t)bus_can_input.voltaje_min_celda_bms / 50.0;
    Rx_Bms->potencia = (rx_var_t)bus_can_input.potencia_bms * 10.0;
    Rx_Bms->t_max = (rx_var_t)bus_can_input.t_max_bms;
    Rx_Bms->nivel_bateria = (rx_var_t)bus_can_input.nivel_bateria_bms / 2.0;
}

/**
 * @brief Decodifica los datos del DCDC
 *
 * Decodifica las variables que se reciben del DCDC por CAN y guarda
 * los datos en la estructura Rx_Dcdc del tipo rx_dcdc_vars_t y que
 * se encuentra en el bus_data.
 *
 */
static void DECODE_DATA_Decode_Dcdc(void)
{
    /* Decodifica info de DCDC */
    switch (bus_can_input.dcdc_ok)
    {
    case CAN_VALUE_MODULE_OK:
    	Rx_Dcdc->dcdc_ok = kMODULE_INFO_OK;
        break;
    case CAN_VALUE_MODULE_ERROR:
    	Rx_Dcdc->dcdc_ok = kMODULE_INFO_ERROR;
        break;
    }

    /* Decodifica las variables analógicas de DCDC */
    Rx_Dcdc->voltaje_bateria = (rx_var_t)bus_can_input.voltaje_bateria_dcdc;
    Rx_Dcdc->voltaje_salida = (rx_var_t)bus_can_input.voltaje_salida_dcdc;
    Rx_Dcdc->t_max = (rx_var_t)bus_can_input.t_max_dcdc;
    Rx_Dcdc->potencia = (rx_var_t)bus_can_input.potencia_dcdc;
}

/**
 * @brief Decodifica los datos del Inversor
 *
 * Decodifica las variables que se reciben del inversor por CAN y guarda
 * los datos en la estructura Rx_Inversor del tipo rx_inversor_vars_t y
 * que se encuentra en el bus_data.
 *
 */
static void DECODE_DATA_Decode_Inversor(void)
{
    /* Decodifica info de Inversor */
    switch (bus_can_input.inversor_ok)
    {
    case CAN_VALUE_MODULE_OK:
    	Rx_Inversor->inversor_ok = kMODULE_INFO_OK;
        break;
    case CAN_VALUE_MODULE_ERROR:
    	Rx_Inversor->inversor_ok = kMODULE_INFO_ERROR;
        break;
    }

	/* Decodifica las variables analógicas de Inversor */
    Rx_Inversor->velocidad = (rx_var_t)bus_can_input.velocidad_inv;
    Rx_Inversor->V = (rx_var_t)bus_can_input.V_inv;
    Rx_Inversor->I = (rx_var_t)bus_can_input.I_inv;
    Rx_Inversor->temp_max = (rx_var_t)bus_can_input.temp_max_inv;
    Rx_Inversor->temp_motor = (rx_var_t)bus_can_input.temp_motor_inv;
    Rx_Inversor->potencia = (rx_var_t)bus_can_input.potencia_inv;
}

static void DECODE_DATA_Decode_Perifericos(void)
{
    /* Decodifica info de Perifericos */
    switch (bus_can_input.perifericos_ok)
    {
    case CAN_VALUE_MODULE_OK:
        Rx_Peripherals->perifericos_ok = kMODULE_INFO_OK;
        break;
    case CAN_VALUE_MODULE_ERROR:
        Rx_Peripherals->perifericos_ok = kMODULE_INFO_ERROR;
        break;
    }

	/* Decodifica botones de modos de manejo */
    switch (bus_can_input.botones_cambio_estado)
    {
    case CAN_VALUE_BTN_NONE:
    	Rx_Peripherals->botones_cambio_estado = kBTN_NONE;
        break;
    case CAN_VALUE_BTN_ECO:
    	Rx_Peripherals->botones_cambio_estado = kBTN_ECO;
        break;
    case CAN_VALUE_BTN_NORMAL:
    	Rx_Peripherals->botones_cambio_estado = kBTN_NORMAL;
        break;
    case CAN_VALUE_BTN_SPORT:
    	Rx_Peripherals->botones_cambio_estado = kBTN_SPORT;
        break;
    }

    /* Decodifica estado de hombre muerto */
    switch (bus_can_input.hombre_muerto)
    {
    case CAN_VALUE_HOMBRE_MUERTO_ON:
        Rx_Peripherals->hombre_muerto = kHOMBRE_MUERTO_ON;
        break;
    case CAN_VALUE_HOMBRE_MUERTO_OFF:
        Rx_Peripherals->hombre_muerto = kHOMBRE_MUERTO_OFF;
    }

    /* Decodifica las variables analógicas de Periféricos */
    Rx_Peripherals->pedal = (rx_var_t)bus_can_input.pedal;
}
