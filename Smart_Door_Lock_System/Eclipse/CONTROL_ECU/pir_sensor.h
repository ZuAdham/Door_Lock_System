/******************************************************************************
 *
 * Module: PIR Sensor
 *
 * File Name: pir_sensor.h
 *
 * Description: Header file for the Flame Sensor
 *
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PIR_SENSOR_PORT_ID   PORTC_ID
#define PIR_SENSOR_PIN_ID    PIN2_ID

#define MOTION                  LOGIC_HIGH  /* Fire detected */
#define NO_MOTION               LOGIC_LOW   /* No fire detected */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initializes the Flame Sensor by setting up the corresponding pin as input.
 */
void PIR_init(void);

/*
 * Description :
 * Reads the flame sensor value to detect fire presence.
 *
 * Returns:
 *  - FIRE if fire is detected.
 *  - NO_FIRE if no fire is detected.
 */
uint8 PIR_getState(void);

#endif /* FLAME_SENSOR_H_ */
