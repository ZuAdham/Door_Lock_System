/*
 * File: pir_sensor.c
 * Author: Adham Muhammed
 * Description:
 *   This file contains the implementation of the flame sensor driver.
 *
 */

#include "pir_sensor.h"
#include "gpio.h"

/*
 * Function: FlameSensor_init
 * --------------------------
 * Initializes the flame sensor by setting the sensor pin as input.
 *
 * Parameters: None
 *
 * Returns: None
 */
void PIR_init(void)
{
    /* Set the flame sensor pin as input */
    GPIO_setupPinDirection(PIR_SENSOR_PORT_ID, PIR_SENSOR_PIN_ID, PIN_INPUT);
}

/*
 * Function: FlameSensor_getValue
 * ------------------------------
 * Reads the current status of the flame sensor.
 *
 * Parameters: None
 *
 * Returns:
 *   uint8 - FIRE (LOGIC_HIGH) if fire is detected, NO_FIRE (LOGIC_LOW) otherwise.
 */
uint8 PIR_getState(void)
{
    return GPIO_readPin(PIR_SENSOR_PORT_ID, PIR_SENSOR_PIN_ID);
}
