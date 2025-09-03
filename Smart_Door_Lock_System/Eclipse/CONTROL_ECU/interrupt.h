/******************************************************************************
 *
 * Module: Interrupt
 *
 * File Name: interrupt.h
 *
 * Description: Header file for enabling and disabling global interrupts
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/io.h> /* Include the AVR register definitions */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Description: Macro to enable global interrupts by setting bit 7 in SREG.
 */
#define Enable_Global_Interrupt() (SREG |= (1<<7))

/*
 * Description: Macro to disable global interrupts by clearing bit 7 in SREG.
 */
#define Disable_Global_Interrupt() (SREG &= ~(1<<7))

#endif /* INTERRUPT_H_ */
