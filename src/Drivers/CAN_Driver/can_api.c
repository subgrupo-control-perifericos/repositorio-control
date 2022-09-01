/**
 * @file can_api.c
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Implementación driver capa de alto nivel CAN
 * @version 0.1
 * @date 2022-02-05
 *
 * @copyright Copyright (c) 2022
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "can_api.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

#define SIZE_OF_ARRAY(a) (sizeof(a)/sizeof(a[0]));

/***********************************************************************************************************************
 * Public functions implementation
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
							get_msg_count_t Fn_Get_Msg_Count)
{
    can_status_t status;

    obj->Fn_Init_Can = Fn_Init_Can;

    obj->Fn_Send_Can_Data = Fn_Send_Can_Data;

    obj->Fn_Read_Can_Data = Fn_Read_Can_Data;

    obj->Fn_Get_Msg_Count = Fn_Get_Msg_Count;

    obj->Frame.IDE = IDE;
    obj->Frame.RTR = RTR;
    obj->Frame.payload_length = 0;

    status = obj->Fn_Init_Can();

    return status;
}

/**
 * @brief CAN send message function.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param obj CAN structure instance
 * @return can_status_t
 */
can_status_t CAN_API_Send_Message( CAN_t *obj)
{
    can_status_t status;

    obj->Frame.DLC = (obj->Frame.payload_length>PAYLOAD_MAX_LENGTH) ? obj->Frame.payload_length=PAYLOAD_MAX_LENGTH : obj->Frame.payload_length;

    status = obj->Fn_Send_Can_Data( obj->Frame.id,
                                    obj->Frame.IDE,
                                    obj->Frame.RTR,
                                    obj->Frame.DLC,
                                    (obj->Frame.payload_buff) );

    return status;
}

/**
 * @brief CAN read message function.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param obj CAN structure instance
 * @return can_status_t
 */
can_status_t CAN_API_Read_Message( CAN_t *obj)
{
    can_status_t status;

    status = obj->Fn_Read_Can_Data( &obj->Frame.id,
                                    obj->Frame.payload_buff);

    return status;
}

/**
 * @brief CAN get message count function.
 *
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param obj CAN structure instance
 * @return can_status_t
 */
can_status_t CAN_API_Get_Message_Count( CAN_t *obj)
{
    can_status_t status;

    status = obj->Fn_Get_Msg_Count();

    return status;
}
