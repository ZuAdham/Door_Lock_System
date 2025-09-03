 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the TIMER AVR driver
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

typedef enum
{
	TIMER_0,TIMER_1,TIMER_2
}Timer_ID_Type;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXT_CLOCK_FALLING,EXT_CLOCK_RISING,
	TIMER2_F_CPU_32, TIMER2_F_CPU_128
}Timer_ClockType;
typedef enum
{
  NORMAL_MODE,
  CTC_MODE_OC_DISABLED=8,CTC_MODE_OC_TOGGLE,CTC_MODE_OC_CLEAR,CTC_MODE_OC_SET,
}Timer_ModeType;
typedef struct
{
uint16 timer_InitialValue;
uint16 timer_compare_MatchValue; /*it will be used in compare mode only*/
Timer_ID_Type timer_ID;
Timer_ClockType timer_clock;
Timer_ModeType timer_mode;
}Timer_ConfigType;

void Timer_init(const Timer_ConfigType * Config_Ptr);
void Timer_deInit(Timer_ID_Type timer_type);
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );

#endif /* TIMER_H_ */
