 /******************************************************************************
 *
 *
 *
 * File Name: HMI_ECU
 *
 * Description: APPLICATION FILE
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#include "lcd.h"
#include "keypad.h"
#include "interrupt.h"
#include "std_types.h"
#include <util/delay.h>
#include "uart.h"
#include "timer.h"

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

#define BUTTON_DEBOUNCE     250
#define MILLISECONDS_TO_TICKS(ms)  (((F_CPU / 1024) * (ms)) / 1000)

UART_ConfigType UART_CONFIG = {EIGHT_BITS,NO_PARITY,ONE_STOP_BIT,4800};
Timer_ConfigType TIMER1_CONFIG = {0,(uint16)(MILLISECONDS_TO_TICKS(1000)),TIMER_1,F_CPU_1024,CTC_MODE_OC_DISABLED};

volatile uint8 received_key;
static volatile uint8 time = 0;

void HMI_enterPassword(uint8 * password)
{
	volatile uint8 digits = 0;
	volatile uint8 key;
	LCD_moveCursor(1,0);
	while(digits < PASSWORD_DIGITS)
	{
		key = KEYPAD_getPressedKey();
		if((key <= 9) && (key >= 0))
		{
			password[digits] = key;
			LCD_displayCharacter('#');
			digits++;

		}
		_delay_ms(BUTTON_DEBOUNCE);
	}
	while(key != ENTER)
	{
		key = KEYPAD_getPressedKey();
	}
	LCD_clearScreen();

}
void HMI_countSeconds(void)
{
	time++;
}
void HMI_delaySeconds(uint8 seconds)
{
	time = 0;
	Timer_setCallBack(HMI_countSeconds,TIMER_1);
	Timer_init(&TIMER1_CONFIG);
	while(time < seconds);
	time = 0;
	Timer_deInit(TIMER_1);
}

void HMI_sendPassword(uint8 * password,uint8 command)
{
	UART_sendByte(command);
	volatile uint8 digits = 0;
	while(digits < 5){
		UART_sendByte(password[digits]);
		while(UART_recieveByte() != NEXT_DIGIT);
		digits++;
	}
	UART_sendByte('#');
}

void HMI_unlockDoor(void)
{
	UART_sendByte(UNLOCK_DOOR);

	LCD_clearScreen();
	LCD_displayString("   DOOR IS");
	LCD_moveCursor(1,2);
	LCD_displayString("UNLOCKING");

	HMI_delaySeconds(15);

	LCD_clearScreen();
	LCD_displayString("WAIT FOR PEOPLE");
	LCD_moveCursor(1,4);
	LCD_displayString("TO ENTER");

	while(UART_recieveByte() != LOCK_DOOR);

	LCD_clearScreen();
	LCD_displayString("   DOOR IS");
	LCD_moveCursor(1,2);
	LCD_displayString("LOCKING");

	HMI_delaySeconds(15);
}

int main(void)
{
	volatile uint8 key;
	volatile uint8 step;
	volatile uint8 system_status;
	volatile uint8 pass_status = 0;
	uint8 password[PASSWORD_DIGITS+1];
	uint8 attempts;

	Enable_Global_Interrupt();

	UART_init(&UART_CONFIG);
	LCD_init();

	while(received_key != MC2_READY)
	{
		received_key = UART_recieveByte();
	}

	UART_sendByte(GET_STATUS);

	system_status = UART_recieveByte();

	if(system_status != PASSWORD_SAVED)
	{
		step = 1;
	}
	else
	{
		step = 2;
	}
	while(1)
	{

		attempts = 0;
		LCD_clearScreen();

		switch(step)
		{
		case 1:

			LCD_displayString("ENTER PASS: ");

			HMI_enterPassword(password);

			HMI_sendPassword(password,SET_NEW_PASS);

			LCD_displayString("RE-ENTER PASS: ");

			HMI_enterPassword(password);

			HMI_sendPassword(password,CONFIRM_PASS);

			pass_status = UART_recieveByte();

			if(pass_status == PASS_MATCH){

				LCD_displayString("PASS MATCH");

				step = 2;
			}else
			{
				LCD_displayString("PASS DONT MATCH");


			}

			_delay_ms(1000);

			break;
		case 2:

			LCD_displayString("+ : Open Door");
			LCD_moveCursor(1,0);
			LCD_displayString("- : Change Pass");
			key = 0;
			while((key != '+') && (key != '-'))
			{
				key = KEYPAD_getPressedKey();
			}
			if(key == '+')
			{
				step = 3;
			}else step = 4;

			break;

		case 3:

			pass_status = 0;

			while(pass_status != PASS_MATCH){
				if(attempts == 3)
				{
					step = 5;
					break;
				}
				LCD_displayString("ENTER PASS: ");

				HMI_enterPassword(password);

				HMI_sendPassword(password,CHECK_PASS);

				pass_status = UART_recieveByte();
				if(pass_status == PASS_MATCH){

					attempts = 0;

					LCD_displayString("PASS MATCH");

					_delay_ms(500);

					HMI_unlockDoor();

					step = 2;

				}else
				{
					attempts++;
					LCD_displayString("PASS DONT MATCH");
					_delay_ms(1000);
					LCD_clearScreen();

				}
			}

			break;

		case 4:

			pass_status = 0;

			while(pass_status != PASS_MATCH)
			{

				if(attempts == 3)
				{
					UART_sendByte(ATTEMPTS_ENDED);
					LCD_displayString("SYSTEM LOCKED");
					HMI_delaySeconds(60);
					break;
				}
				LCD_displayString("ENTER PASS: ");

				HMI_enterPassword(password);

				HMI_sendPassword(password,CHECK_PASS);

				pass_status = UART_recieveByte();

				if(pass_status == PASS_MATCH){

					LCD_displayString("PASS MATCH");
					_delay_ms(1000);
					system_status = 0;
					step = 1;

				}else
				{
					attempts++;
					LCD_displayString("PASS DONT MATCH");
				}
				_delay_ms(1000);

			}

			break;

		case 5:

			UART_sendByte(ATTEMPTS_ENDED);

			LCD_displayString("SYSTEM LOCKED");

			HMI_delaySeconds(60);

			step = 2;

			break;
		}

	}
	return 0;
}
