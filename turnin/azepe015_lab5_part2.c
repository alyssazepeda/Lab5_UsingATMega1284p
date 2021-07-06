/*	Author: ALyssa Zepeda
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: https://youtu.be/sopIyCBKbXk 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

//start, off, off release, on press, on release, off press
enum states {start, check, inc, dec, wait1, wait2} state;

int TickFct() {
	switch(state) { //transitions
		case start:
			PORTC = 0X07;
			state = check;
		       	break;
		case check:
			if((~PINA & 0x03) == 0x01) {
				state = inc;
			}
			else if((~PINA & 0x03) == 0x02) {
				state = dec;
			}
			else {
				state = check;
			}
			break;
		case inc:
			state = wait1;
			break;
		case dec:
			state = wait2;
			break;
		case wait1:
			state = ((~PINA & 0x03) == 0x01) ? wait1 : check;
			break;
		case wait2:
			state = ((~PINA & 0x03) == 0x02) ? wait2 : check;
			break;
		default:
			state = start;
			break;	
	}
	switch(state) { //actions
		case start:
			break;
		case check:
			if((~PINA & 0x03) == 0x03) {
				PORTC = 0;
			}
			break;
		case inc:
			if(PORTC < 0x09) {
				PORTC += 1;
			}
			break;
		case dec:
			if(PORTC > 0x00) {
				PORTC -=1;
			}
			break;
		case wait1:
		case wait2:
			if((~PINA & 0x03) == 0x03) {
				PORTC = 0;
			}
			break;
		default: break;
	}
}


int main(void){
	state = start;
 	DDRA = 0X00; PINA = 0X0F; //A IS INPUT
	DDRC = 0X0F; PINC = 0X00; //B IS OUTPUT
    	while (1) {
		TickFct();
    	}
    return 1;
}
