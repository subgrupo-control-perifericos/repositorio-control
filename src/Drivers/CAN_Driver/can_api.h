/**
 * @file can_api.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Archivo header para can_api.c
 * @version 0.1
 * @date 2022-02-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _CAN_API_H_
#define _CAN_API_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/** @brief Maximum length in bytes for the payload */
#define PAYLOAD_MAX_LENGTH          8

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/**
 * @brief CAN identifier type declaration
 *
 */
typedef enum
{
    STANDARD_FRAME = 0,
    EXTENDED_FRAME
} can_id_t;

/**
 * @brief CAN remote transmission request type declaration
 *
 */
typedef enum
{
    NORMAL_MSG = 0,
    RTR_MSG
} can_rtr_t;

/**
  * @brief CAN Status type declaration
  *
  */
typedef enum
{
    CAN_STATUS_OK    = 0x00U,
    CAN_STATUS_ERROR = 0x01U,
} can_status_t;

/**
 * @brief CAN Frame structure declaration
 *
 */
typedef struct
{
    uint32_t id;        /**< Standard or extended identifier value */

    uint8_t IDE;        /**< Type of identifier */

    uint8_t RTR;        /**< Type of frame */

    uint8_t DLC;        /**< Length of frame */

    uint8_t payload_buff[PAYLOAD_MAX_LENGTH];   /**< Payload */

    uint8_t payload_length;     /**< Length of payload in bytes */

} can_frame_t;

/**
 * @brief CAN initialization driver function type declaration
 *
 */
typedef can_status_t (*init_ll_can_t)(void);

/**
 * @brief CAN send data driver function type declaration
 *
 */
typedef can_status_t (*send_can_data_t)(uint32_t, uint8_t, uint8_t, uint8_t, uint8_t *);

/**
 * @brief CAN read data driver function type declaration
 *
 */
typedef can_status_t (*read_can_data_t)(uint32_t *, uint8_t *);

/**
 * @brief CAN get message count driver function type declaration
 *
 */
typedef can_status_t (*get_msg_count_t)(void);

/**
 * @brief CAN structure declaration
 *
 */
typedef struct
{
    can_frame_t Frame;                  /**< CAN frame structure */

    init_ll_can_t Fn_Init_Can;        /**< CAN initialization driver function */

    send_can_data_t Fn_Send_Can_Data;   /**< CAN send data driver function */

    read_can_data_t Fn_Read_Can_Data;   /**< CAN read data driver function */

    get_msg_count_t Fn_Get_Msg_Count;   /**< CAN get message count driver function */

} CAN_t;

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief CAN initialization function.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param obj CAN structure instance
 * @param IDE Type of identifier
 * @param RTR Type of frame
 * @param Fn_Init_Can CAN initialization driver function
 * @param Fn_Send_Can_Data CAN send data driver function
 * @param Fn_Read_Can_Data CAN read data driver function
 * @param Fn_Get_Msg_Count CAN get message driver function
 * @return can_status_t
 */
can_status_t CAN_API_Init(  CAN_t *obj,
                        	can_id_t IDE,
							can_rtr_t RTR,
							init_ll_can_t Fn_Init_Can,
							send_can_data_t Fn_Send_Can_Data,
							read_can_data_t Fn_Read_Can_Data,
							get_msg_count_t Fn_Get_Msg_Count);

/**
 * @brief CAN send message function.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param obj
 * @return can_status_t
 */
can_status_t CAN_API_Send_Message( CAN_t *obj);

/**
 * @brief CAN read message function.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param obj
 * @return can_status_t
 */
can_status_t CAN_API_Read_Message( CAN_t *obj);

/**
 * @brief CAN get message count function.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param obj
 * @return can_status_t
 */
can_status_t CAN_API_Get_Message_Count( CAN_t *obj);

/***********************************************************************************************************************
 * Global variables declarations
 **********************************************************************************************************************/

/** @brief CAN structure instance */
extern CAN_t can_obj;

#endif /* _CAN_API_H_ */
