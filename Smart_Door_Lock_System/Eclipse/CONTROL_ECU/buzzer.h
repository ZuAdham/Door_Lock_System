/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver, providing initialization
 *              and control functions.
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID    PORTC_ID
#define BUZZER_PIN_ID     PIN7_ID

#define BUZZER_ON         LOGIC_HIGH
#define BUZZER_OFF        LOGIC_LOW

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initializes the buzzer by setting up the corresponding pin as an output.
 */
void Buzzer_init(void);

/*
 * Description :
 * Turns the buzzer ON.
 */
void Buzzer_on(void);

/*
 * Description :
 * Turns the buzzer OFF.
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
