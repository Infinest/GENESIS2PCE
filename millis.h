/*
 * millis.h
 *
 * Created: 02.05.2020 15:43:24
 *  Author: Infinest
 */ 


#ifndef MILLIS_H_
#define MILLIS_H_

#define F_CPU 16000000L
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define MICROSECONDS_EACH_TIMER0_OVERFLOW (64*256 / clockCyclesPerMicrosecond())
#define MILLISECOND_INCREMENT MICROSECONDS_EACH_TIMER0_OVERFLOW / 1000
#define FRACT_INCREMENT (MICROSECONDS_EACH_TIMER0_OVERFLOW % 1000)

volatile unsigned long timer0_millis;
volatile unsigned int timer0_fract;

volatile unsigned long timer0_millis;
volatile unsigned int timer0_fract;
void initTimer();
unsigned long millis();

#endif /* MILLIS_H_ */