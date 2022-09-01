/**
 * @file can_wrapper.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Implementaciones funciones wrapper CAN para tarjeta Control
 * @version 0.1
 * @date 2022-18-05
 *
 * @copyright Copyright (c) 2022
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "can_wrapper.h"

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

/* STM32 CAN Tx message header structure instance */
static CAN_TxHeaderTypeDef TxHeader;

/* STM32 CAN Rx message header structure definition */
static CAN_RxHeaderTypeDef RxHeader;

/* STM32 CAN filter configuration structure instance */
static CAN_FilterTypeDef sFilterConfig;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void CAN_FilterConfig(void);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función wrapper inicialización de periférico CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param   None
 * @retval  None
 */
can_status_t CAN_Wrapper_Init(void)
{
	/*
	 *  STM32 CAN initialization
	 */

	/* Initialize time base timer for CAN triggering */
	MX_TIM7_Init();

	/* Initialize CAN1 */
	MX_CAN1_Init();

	/* Disable debug freeze */
	CAN1->MCR &= (~CAN_MCR_DBF);

	/* CAN filter configuration */
	CAN_FilterConfig();

	/* Start CAN module */
	if (HAL_CAN_Start(&hcan1) != HAL_OK)
	{
		Error_Handler();
	}

	/* Activate CAN notification (enable interrupts) */
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		Error_Handler();
	}
	
	/* Start time base trigger CAN timer */
	HAL_TIM_Base_Start_IT(&htim7);

	return CAN_STATUS_OK;
}

/**
 * @brief Función wrapper transmisión de datos CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param id Standard identifier
 * @param ide Type of identifier
 * @param rtr Type of frame
 * @param dlc Length of frame
 * @param data Data to transmit
 * @retval None
 */
can_status_t CAN_Wrapper_TransmitData(uint32_t id, uint8_t ide, uint8_t rtr, uint8_t dlc, uint8_t *data)
{
	/*
	 *  STM32 CAN transmit message
	 */

    uint32_t TxMailbox;

    /* CAN message transmission configuration */
	TxHeader.StdId = id;            			// standard identifier value
	TxHeader.DLC = dlc; 						// length of frame
	TxHeader.IDE = CAN_ID_STD; 					// type of identifier
	TxHeader.RTR = CAN_RTR_DATA;    			// type of frame
	TxHeader.TransmitGlobalTime = DISABLE;

	/* Start CAN transmission process */
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, data, &TxMailbox);

	return CAN_STATUS_OK;
}

/**
 * @brief Función wrapper recepción de datos CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param id Received identifier
 * @param data Received data
 * @retval  None
 */
can_status_t CAN_Wrapper_ReceiveData(uint32_t *id, uint8_t *data)
{
	/*
	 *  STM32 CAN receive message
	 */

	/* Get CAN received message */
    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, data);

    /* Received standard identifier */
    *id = RxHeader.StdId;

	return CAN_STATUS_OK;
}

/**
 * @brief Función wrapper conteo dato recibido por CAN.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @return can_status_t
 */
can_status_t CAN_Wrapper_DataCount(void)
{
	return CAN_STATUS_OK;
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

/**
 * @brief CAN Filter Configuration Function
 *
 * @param None
 * @retval None
 */
static void CAN_FilterConfig(void)
{
	/*
	 *  STM32 CAN filter configuration
	 */

	/*
	 * For single CAN instance the are 14 dedicated filter banks.
	 * The FilterBank parameter must be a number between 0 and 13.
	 *
	 * In Mask mode the identifier registers are associated with
	 * mask registers specifying which bits of the identifier are
	 * handled as "must watch" or as "don't care".
	 *
	 * One 32-bit filter register per filter bank in Identifier Mask mode.
	 * One 32-bit mask register per filter bank in Identifier Mask mode.
	 *
	 * CAN standard format: 11-bit identifier.
	 *
	 * 5-bit shifting for standard identifier mapping.
	 */

	/* CAN filter configuration shared among all configured filter banks */
	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;

	/* CAN filter configuration structure for Filter Bank 1 */
	sFilterConfig.FilterBank = 1;
	sFilterConfig.FilterIdHigh = 0x00 << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = (0xFFFF << 3) << 5;
	sFilterConfig.FilterMaskIdLow = 0x0000;

	/* Configure CAN filter */
	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig)!= HAL_OK)
	{
		Error_Handler();
	}

	/* CAN filter configuration structure for Filter Bank 2 */
	sFilterConfig.FilterBank = 2;
	sFilterConfig.FilterIdHigh = 0x20 << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = (0xFFFF << 3) << 5;
	sFilterConfig.FilterMaskIdLow = 0x0000;

	/* Configure CAN filter */
	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig)!= HAL_OK)
	{
		Error_Handler();
	}

	/* CAN filter configuration structure for Filter Bank 3 */
	sFilterConfig.FilterBank = 3;
	sFilterConfig.FilterIdHigh = 0x30 << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = (0xFFFF << 3) << 5;
	sFilterConfig.FilterMaskIdLow = 0x0000;

	/* Configure CAN filter */
	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig)!= HAL_OK)
	{
		Error_Handler();
	}

	/* CAN filter configuration structure for Filter Bank 4 */
	sFilterConfig.FilterBank = 4;
	sFilterConfig.FilterIdHigh = 0x40 << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = (0xFFFF << 3) << 5;
	sFilterConfig.FilterMaskIdLow = 0x0000;

	/* Configure CAN filter */
	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig)!= HAL_OK)
	{
		Error_Handler();
	}
}
