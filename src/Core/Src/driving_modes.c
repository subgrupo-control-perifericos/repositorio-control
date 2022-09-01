/**
 * @file driving_modes.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Implementación máquina modos de manejo
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "driving_modes.h"

/***********************************************************************************************************************
 * Private macros
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

/** @brief Estados posibles de la máquina de estados */
enum DrivingModes_States
{
    kINIT = 0, /**< Estado de init */
    kECO,      /**< Estado modo de manejo ECO */
    kNORMAL,   /**< Estado modo de manejo NORMAL */
    kSPORT     /**< Estado modo de manejo SPORT */
};

/** @brief Estado de la máquina de estados */
static uint8_t driving_modes_state = kINIT;

/** @brief Puntero a estructura de tipo rx_peripherals_vars_t que contiene los valores de las variables decodificadas de periféricos */
static rx_peripherals_vars_t* Rx_Peripherals = &bus_data.Rx_Peripherals;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void DRIVING_MODES_StateMachine(void);

static void DRIVING_MODES_Send_DrivingMode(driving_mode_t to_send, typedef_bus2_t* bus_can_output);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función principal máquina de modos de manejo.
 *
 * Llama a la función máquina de estados de modos de manejo. 
 * 
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void DRIVING_MODES_Process(void)
{
    DRIVING_MODES_StateMachine();
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

/**
 * @brief Máquina de estados de modo de manejo.
 *
 * Se encarga de permitir las transiciones entre los diferentes modos de manejo
 * de acuerdo a los botones de periféricos y a la máquina de fallas.
 *
 * Lee la variable botones_cambio_estado de la estructura de variables decodificadas
 * de periféricos, es decir, la estructura de tipo rx_peripherals_vars_t que se encuentra
 * en el bus_data.
 *
 */
static void DRIVING_MODES_StateMachine(void)
{
    switch (driving_modes_state)
    {
    case kINIT:
        if (bus_data.driving_mode == kDRIVING_MODE_ECO)
        {
            driving_modes_state = kECO;
        }
        else if(bus_data.driving_mode == kDRIVING_MODE_NORMAL)
        {
            driving_modes_state = kNORMAL;
        }
        else if(bus_data.driving_mode == kDRIVING_MODE_SPORT)
        {
            driving_modes_state = kSPORT;
        }
        break;

    case kECO:

        /* Actualiza modo de manejo a ECO en bus de datos */
        bus_data.driving_mode = kDRIVING_MODE_ECO;

        /* Actualiza modo de manejo a ECO en bus de salida CAN */
        DRIVING_MODES_Send_DrivingMode(bus_data.driving_mode, &bus_can_output);

        if (Rx_Peripherals->botones_cambio_estado == kBTN_NORMAL && (bus_data.failure == kFAILURE_OK || bus_data.failure == kFAILURE_CAUTION1))
        {
            driving_modes_state = kNORMAL;
        }
        else if (Rx_Peripherals->botones_cambio_estado == kBTN_SPORT && bus_data.failure == kFAILURE_OK)
        {
            driving_modes_state = kSPORT;
        }
        break;

    case kNORMAL:

        /* Actualiza modo de manejo a NORMAL en bus de datos */
        bus_data.driving_mode = kDRIVING_MODE_NORMAL;

        /* Actualiza modo de manejo a NORMAL en bus de salida CAN */
        DRIVING_MODES_Send_DrivingMode(bus_data.driving_mode, &bus_can_output);

        if (Rx_Peripherals->botones_cambio_estado == kBTN_ECO || bus_data.failure == kFAILURE_CAUTION2)
        {
            driving_modes_state = kECO;
        }
        else if (Rx_Peripherals->botones_cambio_estado == kBTN_SPORT && bus_data.failure == kFAILURE_OK)
        {
            driving_modes_state = kSPORT;
        }
        break;

    case kSPORT:

        /* Actualiza modo de manejo a SPORT en bus de datos */
        bus_data.driving_mode = kDRIVING_MODE_SPORT;

        /* Actualiza modo de manejo a SPORT en bus de salida CAN */
        DRIVING_MODES_Send_DrivingMode(bus_data.driving_mode, &bus_can_output);

        if (Rx_Peripherals->botones_cambio_estado == kBTN_ECO || bus_data.failure == kFAILURE_CAUTION2)
        {
            driving_modes_state = kECO;
        }
        else if (Rx_Peripherals->botones_cambio_estado == kBTN_NORMAL || bus_data.failure == kFAILURE_CAUTION1)
        {
            driving_modes_state = kNORMAL;
        }
        break;

    default:
        break;
    }
}

/**
 * @brief Envío de modo de manejo a bus de salida CAN.
 *
 * @param to_send           Modo de manejo a enviar
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void DRIVING_MODES_Send_DrivingMode(driving_mode_t to_send, typedef_bus2_t* bus_can_output)
{
    /* Envío a bus de salida CAN */
    switch (to_send)
    {
    case kDRIVING_MODE_ECO:
        bus_can_output->estado_manejo = CAN_VALUE_DRIVING_MODE_ECO;
        break;
    case kDRIVING_MODE_NORMAL:
        bus_can_output->estado_manejo = CAN_VALUE_DRIVING_MODE_NORMAL;
        break;
    case kDRIVING_MODE_SPORT:
        bus_can_output->estado_manejo = CAN_VALUE_DRIVING_MODE_SPORT;
        break;
    default:
        break;
    }
}
