/*
* GENESIS2PCE.c
*
* Created: 02.05.2020 14:36:24
* Author : Infinest
*/

#include "main.h"

int main(void)
{
	/*
		Initialize Ports
		PORTC is used for Inputs from Genesis controller and Genesis select pin as output
		PORT B is used for PCE mode output and PCE pad output pins. PB5 is used as input for Genesis Pin 9
		PORD is exclusively used for PCE pad output pins
	*/
	DDRC =  0x1;
	DDRB = 0xDF;
	DDRD = 0xFF;
	
	PORTC = 0xFF;
	PORTB = 0xEF; // LED should be off and PCE mode on 2-Button on init
	PORTD = 0xFF;

	//initialize Timer0
	initTimer();
	while (1)
	{
		if(millis() - lastReadTime > MS_DELAY)
		{
			cli();
			readController();
			bitWrite(PORTB, PCE_MODE_AND_LED, sixButtonMode);
			setPCE();
		}
		sei();
	}
}

/*
	Sets PCE buttons according to current pad mode
*/
void setPCE()
{
	bitWrite(PORTD, PC_PIN_I, bitRead(state, STATE_C));
	bitWrite(PORTD, PC_PIN_II, bitRead(state, STATE_B));
	bitWrite(PORTD, PC_PIN_LEFT, bitRead(state, STATE_LEFT));
	bitWrite(PORTB, PC_PIN_RIGHT, bitRead(state, STATE_RIGHT));
	bitWrite(PORTB, PC_PIN_SELECT, bitRead(state, STATE_START));
	bitWrite(PORTB, PC_PIN_UP, bitRead(state, STATE_UP));
	bitWrite(PORTB, PC_PIN_DOWN, bitRead(state, STATE_DOWN));
	if(sixButtonMode)
	{
		bitWrite(PORTD, PC_PIN_RUN, bitRead(state, STATE_MODE));
		bitWrite(PORTD, PC_PIN_III, bitRead(state, STATE_A));
		bitWrite(PORTD, PC_PIN_IV, bitRead(state, STATE_X));
		bitWrite(PORTD, PC_PIN_V, bitRead(state, STATE_Y));
		bitWrite(PORTD, PC_PIN_VI, bitRead(state, STATE_Z));
	}
	else
	{
		bitWrite(PORTD, PC_PIN_RUN, bitRead(state, STATE_A));
		bitWrite(PORTD, PC_PIN_III, 1);
		bitWrite(PORTD, PC_PIN_IV, 1);
		bitWrite(PORTD, PC_PIN_V, 1);
		bitWrite(PORTD, PC_PIN_VI, 1);
	}
}

/*
	Performs one controller read.
	One controller read consists of 8 read cycles.
	See "https://segaretro.org/Six_Button_Control_Pad_(Mega_Drive)#Technical_information"
*/
void readController()
{
	for(uint8_t cycle = 1; cycle <= CYCLES_PER_READ; cycle++)
	{
		if(!doReadCycle(cycle))
		{
			break;
		}
	}
}

/*
	Performs a single read cycle for the Genesis Pad
*/
bool doReadCycle(uint8_t cycle)
{
	bitWrite(PORTC, GEN_7, cycle % 2);
	switch(cycle)
	{
		case 2:
		if((GEN_3 | GEN_4) == 0)
		{
			bitWrite(state, STATE_A, GEN_6);
			bitWrite(state, STATE_START, GEN_9);
		}
		else
		{
			state = 0b1111111111111111;
			sixButtonMode = false;
			return false;
		}
		break;
		case 3:
		bitWrite(state, STATE_UP, GEN_1);
		bitWrite(state, STATE_DOWN, GEN_2);
		bitWrite(state, STATE_LEFT, GEN_3);
		bitWrite(state, STATE_RIGHT, GEN_4);
		bitWrite(state, STATE_B, GEN_6);
		bitWrite(state, STATE_C, GEN_9);
		break;
		case 4:
		_delay_us(1); // MCU is reading the controller too fast. Unless we wait a microsecond we do not get the correct information about the six button mode
		sixButtonMode = GEN_1 == 0 && GEN_2 == 0;
		break;
		case 5:
		if(sixButtonMode)
		{
			bitWrite(state, STATE_Z, GEN_1);
			bitWrite(state, STATE_Y, GEN_2);
			bitWrite(state, STATE_X, GEN_3);
			bitWrite(state, STATE_MODE, GEN_4);
		}
		else
		{
			state |= 0b0000111100000000;
		}
		break;
		case 8:
		lastReadTime = millis();
		break;
	}
	return true;
}

