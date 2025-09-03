/*
 * File: dcmotor.c
 * Author: Adham Muhammed
 * Description:
 *   This file contains the implementation of the DC Motor driver.
 *   It initializes the motor and provides a function to control its rotation direction and speed.
 */

#include "dcmotor.h"
#include "gpio.h"
#include "pwm.h"

/*
 * Function: DcMotor_Init
 * ----------------------
 * Initializes the DC Motor by setting the control pins as output and stopping the motor initially.
 *
 * Parameters: None
 *
 * Returns: None
 */
void DcMotor_Init(void)
{
	/* Set the motor control pins as output */
	GPIO_setupPinDirection(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_EN1_PORT_ID, DC_MOTOR_EN1_PIN_ID, PIN_OUTPUT);

	/* Stop the motor initially */
	GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
}

/*
 * Function: DcMotor_Rotate
 * ------------------------
 * Controls the rotation direction and speed of the DC Motor.
 *
 * Parameters:
 *   state - The desired rotation state (CLOCKWISE, ANTICLOCKWISE, STOP).
 *   speed - The speed of the motor (0-100% duty cycle).
 *
 * Returns: None
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
	/* Start PWM with the specified speed */
	PWM_Timer0_Start(speed);

	/* Set motor rotation direction */
	switch(state)
	{
	case CLOCKWISE:
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_HIGH);
		break;
	case ANTICLOCKWISE:
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	case STOP:
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	}
}
