/**
 * @file failures.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Implementación máquina de fallas
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "failures.h"

/***********************************************************************************************************************
 * Private macros
 **********************************************************************************************************************/

/* Número de módulos en estado PROBLEM para triggering de autokill */
#define NUM_OF_PROBLEM_MODULES 		2

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

/** @brief Estados posibles de la máquina de estados */
enum FailuresStates
{
    kOK = 0,   /**< Estado falla OK */
    kCAUTION1, /**< Estado falla CAUTION1 */
    kCAUTION2, /**< Estado falla CAUTION2 */
    kAUTOKILL  /**< Estado falla AUTOKILL */
};

/** @brief Estado de la máquina de estados */
static uint8_t failures_state = kCAUTION1;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void FAILURES_StateMachine(void);

static void FAILURES_Send_Failure(failure_t to_send, typedef_bus2_t* bus_can_output);

static void FAILURES_Send_ControlInfo(module_info_t to_send, typedef_bus2_t* bus_can_output);

static void FAILURES_Send_Autokill(typedef_bus2_t* bus_can_output);

static bool FAILURES_Is_Autokill(void);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función principal máquina de fallas.
 *
 * Determina estado general de cada uno de los modulos segun el estado de las
 * variables decodificadas.
 *
 * Llama a la función máquina de estados de fallas.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void FAILURES_Process(void)
{
    FAILURES_StateMachine();
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función máquina de estado de fallas.
 *
 * Se encarga de realizar transiciones entre diferentes fallas de acuerdo al estado
 * de las variables del vehículo, con ello establece el tope de modo de manejo. Más
 * especificamente, la máquina de fallas verifica el estado general de los módulos BMS,
 * DCDC e inversor y conforme a ello realiza las transiciones entre las diferentes fallas
 * posibles: OK, CAUTION1, CAUTION2, y AUTOKILL.
 *
 * Lee las variables bms_status, dcdc_status e inversor_status del bus_data.
 *
 * Escribe en la variable failure del bus_data.
 *
 * Escribe en la variable estado_falla del bus_can_output.
 *
 * Escribe en la variable autokill del bus_can_output.
 *
 */
static void FAILURES_StateMachine(void)
{
    switch (failures_state)
    {
    case kOK:

        /* Actualiza falla a OK en bus de datos */
        bus_data.failure = kFAILURE_OK;

        /* Actualiza falla a OK en bus de salida CAN */
        FAILURES_Send_Failure(bus_data.failure, &bus_can_output);

        if (FAILURES_Is_Autokill()) 
        {
            failures_state = kAUTOKILL;
        }
        else if (bus_data.bms_status == kMODULE_STATUS_PROBLEM
            || bus_data.dcdc_status == kMODULE_STATUS_PROBLEM
            || bus_data.inversor_status == kMODULE_STATUS_PROBLEM)
        {
            failures_state = kCAUTION2;
        }
        else if (bus_data.bms_status == kMODULE_STATUS_REGULAR
            || bus_data.dcdc_status == kMODULE_STATUS_REGULAR
            || bus_data.inversor_status == kMODULE_STATUS_REGULAR)
        {
            failures_state = kCAUTION1;
        }
        break;

    case kCAUTION1:

        /* Actualiza falla a CAUTION1 en bus de datos */
        bus_data.failure = kFAILURE_CAUTION1;

        /* Actualiza falla a CAUTION1 en bus de salida CAN */
        FAILURES_Send_Failure(bus_data.failure, &bus_can_output);

        if (FAILURES_Is_Autokill()) 
        {
            failures_state = kAUTOKILL;
        }
        else if (bus_data.bms_status == kMODULE_STATUS_PROBLEM
            || bus_data.dcdc_status == kMODULE_STATUS_PROBLEM
            || bus_data.inversor_status == kMODULE_STATUS_PROBLEM)
        {
            failures_state = kCAUTION2;
        }
        else if (bus_data.bms_status == kMODULE_STATUS_OK
            && bus_data.dcdc_status == kMODULE_STATUS_OK
            && bus_data.inversor_status == kMODULE_STATUS_OK)
        {
            failures_state = kOK;
        }
        break;

    case kCAUTION2:

        /* Actualiza falla a CAUTION2 en bus de datos */
        bus_data.failure = kFAILURE_CAUTION2;

        /* Actualiza falla a CAUTION2 en bus de salida CAN */
        FAILURES_Send_Failure(bus_data.failure, &bus_can_output);

        if (FAILURES_Is_Autokill()) 
        {
            failures_state = kAUTOKILL;
        }
        else if ((bus_data.bms_status == kMODULE_STATUS_REGULAR || bus_data.bms_status == kMODULE_STATUS_OK)
            && (bus_data.dcdc_status == kMODULE_STATUS_REGULAR || bus_data.dcdc_status == kMODULE_STATUS_OK)
            && (bus_data.inversor_status == kMODULE_STATUS_REGULAR || bus_data.inversor_status == kMODULE_STATUS_OK))
        {
            failures_state = kCAUTION1;
        }
        break;

    case kAUTOKILL:

        /* Actualiza falla a AUTOKILL en bus de datos */
        bus_data.failure = kFAILURE_AUTOKILL;

        /* Actualiza falla a AUTOKILL en bus de salida CAN */
        FAILURES_Send_Failure(bus_data.failure, &bus_can_output);

        /* Actualiza info de control a ERROR en bus de salida CAN */
        FAILURES_Send_ControlInfo(kMODULE_INFO_ERROR, &bus_can_output);

        /* Actualiza variable autokill en bus de salida CAN */
        FAILURES_Send_Autokill(&bus_can_output);

        break;

    default:
        break;
    }
}

/**
 * @brief Condición para evento de AUTOKILL
 *
 * @retval true     Se cumple condición autokill
 * @retval false    No se cumple condición autokill
 */
static bool FAILURES_Is_Autokill(void)
{
    int count = 0;

	if (bus_data.bms_status == kMODULE_STATUS_PROBLEM) count++;

	if (bus_data.dcdc_status == kMODULE_STATUS_PROBLEM) count++;

	if (bus_data.inversor_status == kMODULE_STATUS_PROBLEM) count++;

    return count >= NUM_OF_PROBLEM_MODULES ? true : false;
}

/**
 * @brief Envío de status de control a bus de salida CAN.
 *
 * @param to_send           Status de control a enviar
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void FAILURES_Send_ControlInfo(module_info_t to_send, typedef_bus2_t* bus_can_output)
{
    /* Envío a bus de salida CAN */
    switch (to_send)
    {
    case kMODULE_INFO_OK:
        bus_can_output->control_ok = CAN_VALUE_MODULE_OK;
        break;
    case kMODULE_INFO_ERROR:
        bus_can_output->control_ok = CAN_VALUE_MODULE_ERROR;
        break;
    default:
        break;
    }
}

/**
 * @brief Envío de falla a bus de datos y a bus de salida CAN.
 *
 * @param to_send           Falla a enviar
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void FAILURES_Send_Failure(failure_t to_send, typedef_bus2_t* bus_can_output)
{
    /* Envío a bus de salida CAN */
    switch (to_send)
    {
    case kFAILURE_OK:
        bus_can_output->estado_falla = CAN_VALUE_FAILURE_OK;
        break;
    case kFAILURE_CAUTION1:
        bus_can_output->estado_falla = CAN_VALUE_FAILURE_CAUTION1;
        break;
    case kFAILURE_CAUTION2:
        bus_can_output->estado_falla = CAN_VALUE_FAILURE_CAUTION2;
        break;
    case kFAILURE_AUTOKILL:
        bus_can_output->estado_falla = CAN_VALUE_FAILURE_AUTOKILL;
        break;
    default:
        break;
    }
}

/**
 * @brief Envío de evento autokill a bus de salida CAN.
 *
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void FAILURES_Send_Autokill(typedef_bus2_t* bus_can_output)
{
    bus_can_output->autokill = CAN_VALUE_AUTOKILL_EVENT;
}
