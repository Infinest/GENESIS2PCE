/*
 * millis.c
 *
 * Created: 02.05.2020 14:42:24
 *  Author: Infinest
 */ 

#include "millis.h"

ISR(TIMER0_OVF_vect)
{
		// copy these to local variables so they can be stored in registers
		// (volatile variables must be read from memory on every access)
		unsigned long m = timer0_millis;
		unsigned int f = timer0_fract;
		m += MILLISECOND_INCREMENT;
		f += FRACT_INCREMENT;
		//Once fraction is big enough to make up an entire millisecond we increment m by one and decrement f by 1000
		if(1000 <= f)
		{
			m++;
			f -= 1000;
		}
		timer0_millis = m;
		timer0_fract = f;
}

void initTimer()
{
	//Enable global interrupts
	sei();
	//Prescale by Clock / 64
	TCCR0B |= 1<<(CS01) | 1<<CS00;
	//Timer/Counter0 Overflow interrupt enable
	TIMSK0  |= 1<<TOIE0;
}

unsigned long millis()
{
	unsigned long m;
	uint8_t oldSREG = SREG;
	cli();
	m = timer0_millis;
	SREG = oldSREG;
	return m;
}