/*	Author: ALyssa Zepeda
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: https://youtu.be/jAP9L-eh0Y0
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
     /* Insert DDR and PORT initializations */
	DDRA = 0X00; PORTA = 0XFF; //Config port A's 8 pins to inputs
	DDRC = 0XFF; PORTC = 0X00; //Config port C's 8 pins to output
	unsigned char fuelLevel = 0x00;
	unsigned char LED = 0x00;
    /* Insert your solution below */
    while (1) {
	fuelLevel = ~PINA & 0x0F; //only read PA3-PA0
	if(fuelLevel == 0) {
		LED = 0x40; // low fuel light turns on
	} 
	else if(fuelLevel < 3) {
		LED = 0x60; //low fuel & PC5
	} 
	else if(fuelLevel < 5) {
		LED = 0x70; //low fuel, PC5 & PC4
	} 
	else if(fuelLevel < 7) {
		LED = 0x38; //PC5-3
	} 
	else if(fuelLevel < 10) {
		LED = 0x3C; //PC5-2
	} 
	else if(fuelLevel < 13) {
	       LED = 0x3E; //PC5-1
	}
	else {
		LED = 0x3F; //PC5-0
	}
	PORTC = LED;	
    }
    return 1;
}
