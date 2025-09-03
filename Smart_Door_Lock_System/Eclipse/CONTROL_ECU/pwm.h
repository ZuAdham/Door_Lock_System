/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the PWM driver using Timer0.
 *
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initializes Timer0 in PWM mode and starts generating a PWM signal
 * with the specified duty cycle.
 *
 * Parameters:
 *   duty_cycle - The duty cycle of the PWM signal (0-100%).
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
