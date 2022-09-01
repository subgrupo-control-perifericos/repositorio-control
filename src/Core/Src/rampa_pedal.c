/**
 * @file rampa_pedal.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Implementación rampa pedal
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "rampa_pedal.h"

/***********************************************************************************************************************
 * Private macros
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

/** Puntero a estructura de tipo rx_peripherals_vars_t que contiene los valores de las variables decodificadas de periféricos */
static rx_peripherals_vars_t* Rx_Peripherals = &bus_data.Rx_Peripherals;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static float RAMPA_PEDAL_Get_Rampa_Eco(rx_var_t pedal);

static float RAMPA_PEDAL_Get_Rampa_Normal(rx_var_t pedal);

static float RAMPA_PEDAL_Get_Rampa_Sport(rx_var_t pedal);

static float RAMPA_PEDAL_Get_Rampa_HombreMuerto(rx_var_t pedal);

static void RAMPA_PEDAL_Send_Velocidad(float to_send, typedef_bus2_t* bus_can_output);

static void RAMPA_PEDAL_Send_HM_State(hm_state_t to_send, typedef_bus2_t* bus_can_output);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función principal de bloque rampa pedal.
 *
 * Se encarga de transformar el valor de pedal registrado de periféricos a un valor de
 * velocidad que será empleado por inversor. Para cada modo de manejo se tiene una
 * función de transferencia diferente para determinar el valor de velocidad asociado al
 * valor de pedal registrado desde periféricos.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param   None
 * @retval  None
 */
void RAMPA_PEDAL_Process(void)
{
    if (Rx_Peripherals->hombre_muerto == kHOMBRE_MUERTO_ON)
    {
        /* Actualiza velocidad inversor en bus de datos */
        bus_data.velocidad_inversor = RAMPA_PEDAL_Get_Rampa_HombreMuerto(Rx_Peripherals->pedal);
    }
    else if (Rx_Peripherals->hombre_muerto == kHOMBRE_MUERTO_OFF)
    {
        switch (bus_data.driving_mode)
        {
        case kDRIVING_MODE_ECO:
            /* Actualiza velocidad inversor en bus de datos */
            bus_data.velocidad_inversor = RAMPA_PEDAL_Get_Rampa_Eco(Rx_Peripherals->pedal);
            break;
        
        case kDRIVING_MODE_NORMAL:
            /* Actualiza velocidad inversor en bus de datos */
            bus_data.velocidad_inversor = RAMPA_PEDAL_Get_Rampa_Normal(Rx_Peripherals->pedal);
            break;
        
        case kDRIVING_MODE_SPORT:
            /* Actualiza velocidad inversor en bus de datos */
            bus_data.velocidad_inversor = RAMPA_PEDAL_Get_Rampa_Sport(Rx_Peripherals->pedal);
            break;
        
        default:
            break;
        }
    }

    /* Actualiza velocidad inversor en bus de salida CAN */
    RAMPA_PEDAL_Send_Velocidad(bus_data.velocidad_inversor, &bus_can_output);

	/* Actualiza estado hombre muerto a bus de salida CAN */
	RAMPA_PEDAL_Send_HM_State(Rx_Peripherals->hombre_muerto, &bus_can_output);
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/


/**
 * @brief Rampa pedal para modo ECO
 *
 * @param pedal     Pedal de periféricos
 * @return float  Velocidad [0:100]
 */
static float RAMPA_PEDAL_Get_Rampa_Eco(rx_var_t pedal) {

    float velocidad = 0;

    if (pedal >= 0 && pedal < 20)
    {
        velocidad = pedal * 0.25;
    }
    else if (pedal >= 20 && pedal < 40)
    {
        velocidad = (0.5 * pedal) - 5;
    }
    else if (pedal >= 40 && pedal < 60)
    {
        velocidad = (0.75 * pedal) - 15;
    }
    else if (pedal >= 60 && pedal < 80)
    {
        velocidad = (1.5 * pedal) - 60;
    }
    else if (pedal >= 80 && pedal < 100)
    {
        velocidad = (2 * pedal) - 100;
    }

    return velocidad;
}

/**
 * @brief Rampa pedal para modo NORMAL
 *
 * @param pedal     Pedal de periféricos
 * @return float  Velocidad [0:100]
 */
static float RAMPA_PEDAL_Get_Rampa_Normal(rx_var_t pedal) {

    float velocidad = 0;

    if (pedal >= 0 && pedal < 20)
    {
        velocidad = pedal * 0.5;
    }
    else if (pedal >= 20 && pedal < 40)
    {
        velocidad = pedal - 10;
    }
    else if (pedal >= 40 && pedal < 60)
    {
        velocidad = (2 * pedal) - 50;
    }
    else if (pedal >= 60 && pedal < 80)
    {
        velocidad = pedal + 10;
    }
    else if (pedal >= 80 && pedal < 100)
    {
        velocidad = (0.5 * pedal) + 50;
    }

    return velocidad;
}

/**
 * @brief Rampa pedal para modo SPORT
 *
 * @param pedal     Pedal de periféricos
 * @return float  Velocidad [0:100]
 */
static float RAMPA_PEDAL_Get_Rampa_Sport(rx_var_t pedal) {

    float velocidad = 0;

    if (pedal >= 0 && pedal < 20)
    {
        velocidad = pedal * 1.5;
    }
    else if (pedal >= 20 && pedal < 40)
    {
        velocidad = (1.25 * pedal) + 5;
    }
    else if (pedal >= 40 && pedal < 60)
    {
        velocidad = (1 * pedal) + 15;
    }
    else if (pedal >= 60 && pedal < 80)
    {
        velocidad = (0.75 * pedal) + 30;
    }
    else if (pedal >= 80 && pedal < 100)
    {
        velocidad = (0.5 * pedal) + 50;
    }

    return velocidad;
}

/**
 * @brief Rampa pedal en caso de hombre muerto presionado.
 *
 * @param pedal     Pedal de periféricos
 * @return float  Velocidad [0:100]
 */
static float RAMPA_PEDAL_Get_Rampa_HombreMuerto(rx_var_t pedal) {
    return 0.0;
}

/**
 * @brief Envío de velocidad a bus de datos y a bus de salida CAN.
 *
 * @param to_send           Velocidad a enviar
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void RAMPA_PEDAL_Send_Velocidad(float to_send, typedef_bus2_t* bus_can_output)
{
    bus_can_output->nivel_velocidad = (uint8_t)round(to_send);
}

/**
 * @brief Envío de estado de hombre muerto a bus de salida CAN.
 *
 * @param to_send           Estado de hombre muerto a enviar
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void RAMPA_PEDAL_Send_HM_State(hm_state_t to_send, typedef_bus2_t* bus_can_output)
{
    /* Envío a bus de salida CAN */
    switch (to_send)
    {
    case kHOMBRE_MUERTO_ON:
        bus_can_output->hombre_muerto = CAN_VALUE_HOMBRE_MUERTO_ON;
        break;
    case kHOMBRE_MUERTO_OFF:
        bus_can_output->hombre_muerto = CAN_VALUE_HOMBRE_MUERTO_OFF;
        break;
    default:
        break;
    }
}
