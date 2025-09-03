 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the TIMER AVR driver
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/
#include "timer.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile void (*g_Timer0_CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer1_CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer2_CallBackPtr)(void) = NULL_PTR;

ISR(TIMER0_OVF_vect)
{
	if(g_Timer0_CallBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_CallBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER0_COMP_vect)
{
	if(g_Timer0_CallBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_CallBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_CallBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_CallBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_CallBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_CallBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER2_OVF_vect)
{
	if(g_Timer2_CallBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_CallBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER2_COMP_vect)
{
	if(g_Timer2_CallBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_CallBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	uint8 timer_clock = 0;
	switch(Config_Ptr->timer_ID)
	{
	case TIMER_0:

		if((Config_Ptr->timer_mode) > 0)
		{
			OCR0 = (Config_Ptr->timer_compare_MatchValue);
			TIMSK |= 0x01;
		}else
		{
			TIMSK |= 0x02;
		}
		TCNT0 = (uint8)(Config_Ptr->timer_InitialValue);

		TCCR0 = (1 << FOC0) | ((((Config_Ptr->timer_mode) & 0x08) >> 3) << WGM01) | (((Config_Ptr->timer_mode) & 0x03) << COM00) | ((Config_Ptr->timer_clock) & 0x07);

		break;
	case TIMER_1:

		if((Config_Ptr->timer_mode) > 0)
		{
			OCR1A = (Config_Ptr->timer_compare_MatchValue);
			TIMSK |= 0x10;
		}else
		{
			TIMSK |= 0x04;
		}
		TCNT1 = (Config_Ptr->timer_InitialValue);
		TCCR1A = (1<<FOC1A) |  (((Config_Ptr->timer_mode) & 0x03) << COM1A0);
		TCCR1B = ((Config_Ptr->timer_clock) & 0x07) | ((((Config_Ptr->timer_mode) & 0x08) >> 3) << WGM12);

		break;
	case TIMER_2:

		if((Config_Ptr->timer_mode) > 0)
		{
			OCR2 = (Config_Ptr->timer_compare_MatchValue);
			TIMSK |= 0x40;
		}else
		{
			TIMSK |= 0x80;
		}
		TCNT2 = (uint8)(Config_Ptr->timer_InitialValue);
		if((Config_Ptr->timer_clock) == TIMER2_F_CPU_128)
		{

			timer_clock = (uint8)0x05;

		}else if((Config_Ptr->timer_clock) == TIMER2_F_CPU_32)
		{
			timer_clock = (uint8)0x03;
		}else if((Config_Ptr->timer_clock) > 3)
		{
			timer_clock = (uint8)((Config_Ptr->timer_mode) + 2);
		}else if((Config_Ptr->timer_clock) == F_CPU_64)
		{
			timer_clock = (uint8)((Config_Ptr->timer_mode) + 1);
		}else
		{
			timer_clock = (uint8)(Config_Ptr->timer_mode);
		}

		TCCR2 = (1 << FOC2) | ((((Config_Ptr->timer_mode) & 0x08) >> 3) << WGM21) | (((Config_Ptr->timer_mode) & 0x03) << COM20) | (timer_clock & 0x07);

		break;
	}
}

void Timer_deInit(Timer_ID_Type timer_type)
{
	switch(timer_type)
	{
	case TIMER_0:
		OCR0 = 0;
		TCNT0 = 0;
		TCCR0 = 0;
		TIMSK &= 0xFC;
		g_Timer0_CallBackPtr = NULL_PTR;
		break;
	case TIMER_1:
		OCR1A = 0;
		TCNT1 = 0;
		TCCR1A = 0;
		TCCR1B = 0;
		TIMSK &= 0xC3;
		g_Timer1_CallBackPtr = NULL_PTR;
		break;
	case TIMER_2:
		OCR2 = 0;
		TCNT2 = 0;
		TCCR2 = 0;
		TIMSK &= 0x3F;
		g_Timer2_CallBackPtr = NULL_PTR;
		break;
	}
}
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID )
{
	switch(a_timer_ID)
		{
		case TIMER_0:
			g_Timer0_CallBackPtr = (volatile void *)a_ptr;
			break;
		case TIMER_1:
			g_Timer1_CallBackPtr = (volatile void *)a_ptr;
			break;
		case TIMER_2:
			g_Timer2_CallBackPtr = (volatile void *)a_ptr;
			break;
		}
}

