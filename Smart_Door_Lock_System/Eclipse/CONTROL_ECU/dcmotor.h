/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dcmotor.h
 *
 * Description: Header file for the DC Motor driver, providing initialization
 *              and control functions.
 *
 * Author:Adham Muhammed
 *
 *******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DC_MOTOR_IN1_PORT_ID  PORTD_ID
#define DC_MOTOR_IN1_PIN_ID   PIN6_ID

#define DC_MOTOR_IN2_PORT_ID  PORTD_ID
#define DC_MOTOR_IN2_PIN_ID   PIN7_ID

#define DC_MOTOR_EN1_PORT_ID  PORTB_ID
#define DC_MOTOR_EN1_PIN_ID   PIN3_ID

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/

/*
 * Description :
 * Enum for DC Motor rotation states.
 */
typedef enum
{
	CLOCKWISE,      /* Rotate in clockwise direction */
	ANTICLOCKWISE,  /* Rotate in anti-clockwise direction */
	STOP            /* Stop the motor */
} DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initializes the DC Motor by setting the control pins as output.
 */
void DcMotor_Init(void);

/*
 * Description :
 * Rotates the DC Motor in a specified direction with a given speed.
 *
 * Parameters:
 *  - state: Direction of rotation (CLOCKWISE, ANTICLOCKWISE, or STOP).
 *  - speed: Speed of rotation (0 to 100%).
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DCMOTOR_H_ */
