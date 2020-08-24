/*
 * main.h
 *
 * Created: 02.05.2020 17:10:04
 *  Author: Infinest
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "millis.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/fuse.h>
#include <util/delay.h>
#include <avr/eeprom.h>

FUSES =
{
	.low = 0xDF,
	.high = 0xFE,
	.extended = 0xFC,
};

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define MS_DELAY  3
#define CYCLES_PER_READ 8

#define GEN_1 bitRead(PINC, PINC3)
#define GEN_2 bitRead(PINC, PINC2)
#define GEN_3 bitRead(PINC, PINC1)
#define GEN_4 bitRead(PINC, PINC0)
#define GEN_6 bitRead(PINC, PINC5)
#define GEN_7 PINB5
#define GEN_9 bitRead(PINC, PINC4)

#define PCE_MODE_AND_LED PINB4

//1Y
#define PC_PIN_I PIND0//PIND5
#define PC_PIN_UP PIND6//PINB1
//2Y
#define PC_PIN_II PIND1//PIND4
#define PC_PIN_RIGHT PIND7//PINB3
//4Y
#define PC_PIN_RUN PINB3//PIND7
#define PC_PIN_LEFT PINB1//PIND6
//3Y
#define PC_PIN_SELECT PINB2//PINB0
#define PC_PIN_DOWN PINB0//PINB2
// 2 1Y
#define PC_PIN_III PIND2//PIND3
// 2 2Y
#define PC_PIN_IV PIND3//PIND2
// 2 3Y
#define PC_PIN_V PIND4//PIND1
// 2 4Y
#define PC_PIN_VI PIND5//PIND0

#define SWAP_TIMER_TRIGGER_VALUE 0xA00

enum
{
	STATE_UP                      = 0,
	STATE_DOWN                    = 1,
	STATE_LEFT                    = 2,
	STATE_RIGHT                   = 3,
	STATE_START                   = 4,
	STATE_A                       = 5,
	STATE_B                       = 6,
	STATE_C                       = 7,
	STATE_X                       = 8,
	STATE_Y                       = 9,
	STATE_Z                       = 10,
	STATE_MODE                    = 11,
};

unsigned long lastReadTime = 0;
uint16_t state = 0b1111111111111111;
bool sixButtonMode = false;
uint8_t swapState;
uint8_t PC_SWAPPABLE_1;
uint8_t PC_SWAPPABLE_2;
uint16_t swapTimer = 0;

int main(void);
void setPCE();
bool doReadCycle(uint8_t cycle);
void readController();
void writeBit(uint16_t *port, uint8_t pin, uint8_t bit);
void configureSwappableButtons();

#endif /* MAIN_H_ */
