/*
 * File: buzzer.c
 * Author: Adham Muhammed
 * Description:
 *   This file contains the implementation of the Buzzer driver.
 *   It initializes the buzzer and provides functions to turn it on and off.
 */

#include "buzzer.h"
#include "gpio.h"

/*
 * Function: Buzzer_init
 * ---------------------
 * Initializes the buzzer by setting the corresponding pin as an output and turning it off.
 *
 * Parameters: None
 *
 * Returns: None
 */
void Buzzer_init(void)
{
    /* Set the buzzer pin as output */
    GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);

    /* Turn off the buzzer initially */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, BUZZER_OFF);
}

/*
 * Function: Buzzer_on
 * -------------------
 * Turns the buzzer on by setting the corresponding pin to logic high.
 *
 * Parameters: None
 *
 * Returns: None
 */
void Buzzer_on(void)
{
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, BUZZER_ON);
}

/*
 * Function: Buzzer_off
 * --------------------
 * Turns the buzzer off by setting the corresponding pin to logic low.
 *
 * Parameters: None
 *
 * Returns: None
 */
void Buzzer_off(void)
{
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, BUZZER_OFF);
}
