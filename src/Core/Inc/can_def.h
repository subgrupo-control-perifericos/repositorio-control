/**
 * @file can_def.h
 * @author Subgrupo Control y Periféricos - Elektron Motorsports
 * @brief Definiciones para IDs y valores de CAN
 * @version 0.1
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _CAN_DEF_H_
#define _CAN_DEF_H_

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/********************************************************************************
 *                                  CAN IDs                                     *
 *******************************************************************************/

/* ================================ Control ================================== */

#define CAN_ID_CONTROL_AUTOKILL                 	0x001
#define CAN_ID_CONTROL_ESTADO_MANEJO 		    	0x010
#define CAN_ID_CONTROL_ESTADO_FALLA			    	0x011
#define CAN_ID_CONTROL_NIVEL_VELOCIDAD		    	0x012
#define CAN_ID_CONTROL_HOMBRE_MUERTO		    	0x013
#define CAN_ID_CONTROL_OK			    			0x014

/* =============================== Perifericos =============================== */

#define CAN_ID_PERIFERICOS_PEDAL					0x002
#define CAN_ID_PERIFERICOS_HOMBRE_MUERTO			0x003
#define CAN_ID_PERIFERICOS_BOTONES_CAMBIO_ESTADO	0x004
#define CAN_ID_PERIFERICOS_OK						0x005

/* ================================== BMS ==================================== */

#define CAN_ID_BMS_VOLTAJE							0x020
#define	CAN_ID_BMS_CORRIENTE						0x021
#define CAN_ID_BMS_VOLTAJE_MIN_CELDA 				0x022
#define CAN_ID_BMS_POTENCIA             			0x023
#define CAN_ID_BMS_T_MAX							0x024
#define	CAN_ID_BMS_NIVEL_BATERIA					0x025
#define CAN_ID_BMS_OK								0x026

/* ================================== DCDC =================================== */

#define CAN_ID_DCDC_VOLTAJE_BATERIA					0x030
#define CAN_ID_DCDC_VOLTAJE_SALIDA      			0x031
#define CAN_ID_DCDC_T_MAX							0x032
#define CAN_ID_DCDC_OK								0x033
#define CAN_ID_DCDC_POTENCIA            			0x034

/* ================================ Inversor ================================= */

#define CAN_ID_INVERSOR_VELOCIDAD					0x040
#define CAN_ID_INVERSOR_V							0x041
#define CAN_ID_INVERSOR_I							0x042
#define CAN_ID_INVERSOR_TEMP_MAX					0x043
#define CAN_ID_INVERSOR_TEMP_MOTOR					0x044
#define CAN_ID_INVERSOR_POTENCIA					0x045
#define CAN_ID_INVERSOR_OK							0x046

/********************************************************************************
 *                                CAN values                                    *
 *******************************************************************************/

/* --------- control_ok, perifericos_ok, bms_ok, dcdc_ok, inversor_ok -------- */

#define CAN_VALUE_MODULE_IDLE                       0x00
#define CAN_VALUE_MODULE_OK          	            0x01
#define CAN_VALUE_MODULE_ERROR       	            0x02

/* -------------------------------- autokill --------------------------------- */

#define CAN_VALUE_AUTOKILL_OFF		                0x00
#define CAN_VALUE_AUTOKILL_EVENT 	                0x01

/* ------------------------------ estado_manejo ------------------------------ */

#define CAN_VALUE_DRIVING_MODE_ECO		            0x03
#define CAN_VALUE_DRIVING_MODE_NORMAL 	            0x02
#define CAN_VALUE_DRIVING_MODE_SPORT	            0x04

/* ------------------------------ estado_falla ------------------------------- */

#define CAN_VALUE_FAILURE_OK			            0x00
#define CAN_VALUE_FAILURE_CAUTION1     	            0x01
#define CAN_VALUE_FAILURE_CAUTION2		            0x02
#define CAN_VALUE_FAILURE_AUTOKILL		            0x03

/* ----------------------------- hombre_muerto ------------------------------- */

#define CAN_VALUE_HOMBRE_MUERTO_OFF                 0x00
#define CAN_VALUE_HOMBRE_MUERTO_ON                  0x01

/* -------------------------- botones_cambio_estado -------------------------- */

#define CAN_VALUE_BTN_NONE				            0x04
#define CAN_VALUE_BTN_ECO				            0x02
#define CAN_VALUE_BTN_NORMAL			            0x01
#define CAN_VALUE_BTN_SPORT				            0x03

#endif /* _CAN_DEF_H_ */
