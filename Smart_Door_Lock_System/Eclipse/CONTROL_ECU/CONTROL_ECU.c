/*
 * CONTROL_ECU.c
 *
 *  Created on: Apr 8, 2025
 *      Author: Adham Muhammed
 */
#include "uart.h"
#include "interrupt.h"
#include "buzzer.h"
#include "external_eeprom.h"
#include "dcmotor.h"
#include "timer.h"
#include "pir_sensor.h"
#include <util/delay.h>

#define MILLISECONDS_TO_TICKS(ms)  (((F_CPU / 1024) * (ms)) / 1000)

#define PASSWORD_DIGITS 	5
#define MC2_READY      		0xE0
#define GET_STATUS     		0xE1
#define SET_NEW_PASS   		0xE2
#define NEXT_DIGIT     		0xE3
#define CONFIRM_PASS   		0xE4
#define PASS_MATCH     		0xE5
#define PASS_NO_MATCH  		0xE6
#define CHECK_PASS          0xE7
#define RECIEVED            0xE9
#define ATTEMPTS_ENDED      0xF0
#define UNLOCK_DOOR         0xF1
#define LOCK_DOOR           0xF2
#define PASSWORD_SAVED      0x23
#define PASSWORD_BASE_ADDRESS 0x0311

static volatile uint8 * ptr_to_pass = (uint8 *)PASSWORD_BASE_ADDRESS;

volatile uint8 received_key;



UART_ConfigType UART_CONFIG = {EIGHT_BITS,NO_PARITY,ONE_STOP_BIT,4800};
Timer_ConfigType TIMER1_CONFIG = {0,(uint16)(MILLISECONDS_TO_TICKS(1000)),TIMER_1,F_CPU_1024,CTC_MODE_OC_DISABLED};

static volatile uint8 time = 0;
void CONTROL_countSeconds(void)
{
	time++;
}

void CONTROL_delaySeconds(uint8 seconds)
{
	time = 0;
	Timer_setCallBack(CONTROL_countSeconds,TIMER_1);
	Timer_init(&TIMER1_CONFIG);
	while(time < seconds);
	time = 0;
	Timer_deInit(TIMER_1);
}

void CONTROL_updatePassword(uint8 * password)
{
	volatile uint8 digits = 0;
	while(digits < PASSWORD_DIGITS)
	{
		EEPROM_readByte((uint16)(ptr_to_pass+digits),password+digits);
		_delay_ms(10);
		digits++;
	}

	password[digits] = '#';
}

void CONTROL_receivePassword(uint8 * password)
{
	volatile uint8 digits = 0;
	while(digits < PASSWORD_DIGITS)
	{

		password[digits] = UART_recieveByte();
		UART_sendByte(NEXT_DIGIT);
		digits++;
	}
	password[digits] = UART_recieveByte();
}
void CONTROL_savePassword(uint8 * password)
{
	uint8 digits = 0;
	while(digits < PASSWORD_DIGITS)
	{
		EEPROM_writeByte((uint16)(ptr_to_pass+digits),password[digits]);
		_delay_ms(10);
		digits++;
	}
	EEPROM_writeByte((uint16)(ptr_to_pass+PASSWORD_DIGITS),password[digits]);
}
uint8 CONTROL_comparePasswords(uint8 *password,uint8 * other_password)
{
	int i = 0;
	while(i < 5)
	{
		if(password[i] != other_password[i]) return FALSE;
		i++;
	}
	return TRUE;
}

int main(void)
{
	uint8 status = 0;
	uint8 new_password[PASSWORD_DIGITS+1];
	uint8 current_password[PASSWORD_DIGITS+1];
	uint8 confirm_password[PASSWORD_DIGITS+1];

	Enable_Global_Interrupt();

	UART_init(&UART_CONFIG);
	UART_sendByte(MC2_READY);
	Buzzer_init();
	DcMotor_Init();
	PIR_init();




	while(1)
	{
		received_key = UART_recieveByte();
		if(received_key != 0xFF){
			if(received_key == GET_STATUS)
			{
				EEPROM_readByte((uint16)(ptr_to_pass+5),&status);
				_delay_ms(10);
				UART_sendByte(status);
				if(status == PASSWORD_SAVED)
				{
					CONTROL_updatePassword(current_password);
				}

			}else if(received_key == SET_NEW_PASS)
			{

				CONTROL_receivePassword(new_password);

				while(UART_recieveByte() != CONFIRM_PASS);

				CONTROL_receivePassword(confirm_password);


				if(CONTROL_comparePasswords(new_password,confirm_password) == TRUE)
				{
					UART_sendByte(PASS_MATCH);
					CONTROL_savePassword(new_password);
					_delay_ms(30);
					CONTROL_updatePassword(current_password);
				}else
				{
					UART_sendByte(PASS_NO_MATCH);
				}



			}else if(received_key == CHECK_PASS)
			{

				CONTROL_receivePassword(confirm_password);
				if(CONTROL_comparePasswords(confirm_password,current_password) == TRUE)
				{
					UART_sendByte(PASS_MATCH);
				}else
				{
					UART_sendByte(PASS_NO_MATCH);
				}
			}else if(received_key == ATTEMPTS_ENDED)
			{
				Buzzer_on();
				CONTROL_delaySeconds(60);
				Buzzer_off();
			}else if(received_key ==  UNLOCK_DOOR)
			{
				DcMotor_Rotate(CLOCKWISE,100);

				CONTROL_delaySeconds(15);

				DcMotor_Rotate(STOP,0);

				while(PIR_getState() == MOTION);

				UART_sendByte(LOCK_DOOR);

				DcMotor_Rotate(ANTICLOCKWISE,100);

				CONTROL_delaySeconds(15);

				DcMotor_Rotate(STOP,0);
			}

			received_key = 0xFF;

		}

	}
}
