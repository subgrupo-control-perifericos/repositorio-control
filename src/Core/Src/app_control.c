/**
 * @file app_control.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Código aplicativo de tarjeta Control
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "app_control.h"

#include "buses.h"
#include "decode_data.h"
#include "driving_modes.h"
#include "failures.h"
#include "rampa_pedal.h"
#include "monitoring.h"
#include "indicators.h"
#include "can_app.h"

#include "main.h"

/***********************************************************************************************************************
 * Private macros
 **********************************************************************************************************************/

/** @brief Duración de la espera hasta timeout en ms */
#define TIMEOUT_VALUE_MS       	5000U

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

/** @brief Estados posibles de la máquina de estados */
enum App_States
{
	kWAITING_ECHO_RESPONSE = 0,      	/**< Estado WAITING_ECHO_RESPONSE */
    kRUNNING,       					/**< Estado RUNNING */
};

/** @brief Estado de la máquina de estados */
static uint8_t app_state = kWAITING_ECHO_RESPONSE;

/** Para conteo de timeout en estado kWAITING_ECHO_RESPONSE */
static uint32_t tickstart;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void MX_APP_Send_Echo(typedef_bus2_t* bus_can_output);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

void MX_APP_Init(void)
{
    /* Initialize board LEDs */
    BSP_LED_Init(LED1);
    BSP_LED_Init(LED2);
    BSP_LED_Init(LED3);

    /* Initialize board buzzer */
    BSP_BUZZER_Init();

    /* Initialize hardware */
    CAN_HW_Init();

    /* Indicate that initialization was completed */
    for(int i=0; i<3; i++)
    {
    	BSP_LED_On(LED1);
    	BSP_LED_On(LED2);
    	BSP_LED_On(LED3);

    	HAL_Delay(200);

    	BSP_LED_Off(LED1);
    	BSP_LED_Off(LED2);
    	BSP_LED_Off(LED3);

    	HAL_Delay(200);
    }
}

void MX_APP_Process(void)
{
	switch (app_state)
	{

	/* Estado esperando respuesta ECHO a tarjetas: BMS, DCDC, Inversor, Perifericos */
	case kWAITING_ECHO_RESPONSE:

		HAL_Delay(2000);

		/* Envía echo a demás tarjetas */
		MX_APP_Send_Echo(&bus_can_output);

		/* Get ticks for timeout counting */
		tickstart = HAL_GetTick();

		while(1)
		{
		    /* Recibió mensaje CAN */
		    if (flag_rx_can == CAN_MSG_RECEIVED)
		    {
		        CAN_APP_Store_ReceivedMessage();

		        flag_rx_can = CAN_MSG_NOT_RECEIVED;
		    }

			/* LEDs para indicar confirmación de cada módulo */
			INDICATORS_Update_ModulesLEDs();

			/* Si todos los módulos respondieron OK, Control está listo */
			if (bus_can_input.bms_ok == CAN_VALUE_MODULE_OK &&
                bus_can_input.dcdc_ok == CAN_VALUE_MODULE_OK &&
                bus_can_input.inversor_ok == CAN_VALUE_MODULE_OK &&
                bus_can_input.perifericos_ok == CAN_VALUE_MODULE_OK)
			{
				HAL_Delay(500);

				/* Indicate that start up has finished */
				INDICATORS_Finish_StartUp();

				app_state = kRUNNING;

				break;
			}
			else if((HAL_GetTick() - tickstart) > TIMEOUT_VALUE_MS)
			{
				/* Envía echo a demás tarjetas, de nuevo */
				MX_APP_Send_Echo(&bus_can_output);

				tickstart = HAL_GetTick();
			}
		}

		break;

	/* Estado tarjeta de Control running */
	case kRUNNING:

		CAN_APP_Process();

		DECODE_DATA_Process();

		MONITORING_Process();

		FAILURES_Process();

		DRIVING_MODES_Process();

		RAMPA_PEDAL_Process();

	    INDICATORS_Process();

		break;
	}
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

static void MX_APP_Send_Echo(typedef_bus2_t* bus_can_output)
{
	bus_can_output->control_ok = CAN_VALUE_MODULE_OK;

	/* Set up can_obj for message transmission */
	can_obj.Frame.id = CAN_ID_CONTROL_OK;
	can_obj.Frame.payload_length = 1;
	can_obj.Frame.payload_buff[0] = bus_can_output->control_ok;

	/* Send message */
	CAN_API_Send_Message(&can_obj);
}
