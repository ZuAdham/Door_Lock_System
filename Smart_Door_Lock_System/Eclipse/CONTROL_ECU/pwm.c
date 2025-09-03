/*
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description:
 *   This file contains the implementation of the PWM driver using Timer0 in Fast PWM mode.
 *
 * Author: Adham Muhammed
 */

#include "pwm.h"
#include "common_macros.h"
#include "avr/io.h"

/*
 * Function: PWM_Timer0_Start
 * --------------------------
 * Initializes Timer0 in Fast PWM mode and starts generating a PWM signal
 * with the specified duty cycle.
 *
 * Parameters:
 *   duty_cycle - The desired duty cycle (0-100%).
 *
 * Returns:
 *   None
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
    /* Ensure duty cycle is within valid range */
    if (duty_cycle > 100)
    {
        duty_cycle = 100;
    }

    /* Calculate and set OCR0 value (without floating-point calculations) */
    uint8 ocr_value = (uint8)(((uint16)duty_cycle * 255) / 100);
    WRITE_REG(OCR0, ocr_value);

    /* Set OC0 (PB3) as output for PWM signal */
    SET_BIT(DDRB, PB3);

    /* Reset Timer0 counter */
    CLEAR_REG(TCNT0);

    /*
     * Configure Timer0 for Fast PWM Mode:
     *   - WGM00 = 1, WGM01 = 1: Fast PWM Mode
     *   - COM01 = 1: Non-Inverting Mode
     *   - CS00 = 1, CS02 = 1: Prescaler of 1024
     */
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00) | (1 << CS02);
}
