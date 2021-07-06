/*	Author: ALyssa Zepeda
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: https://youtu.be/Kn28OSsDSVs
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states {start, loop1, loop2} state;
unsigned char i = 0x00;
unsigned char arr[] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x07, 0x38};

int TickFct() {
	unsigned char A = ~PINA & 0x01;
	switch(state) { //transitions
		case start:
			if(A == 0x01) {
				state = loop1;
			}
			break;
		case loop1:
			if(A == 0x01) {
				state = loop2;
				i++;
			}
			else {
				state = loop1;
			}
			break;
		case loop2:
			if(A == 0x01) {
				state = loop2;
			}
			else {
				state = loop1;
			}
			break;
		default: state = start; break;
	}
	switch(state) { //actions
		case start:
			PORTC = 0x00;
			i = 0x00;
			break;
		case loop1: 
			if(i == 0x0A) {
				i = 0x00;
			}
			PORTC = arr[i];
			break;
		case loop2: break;
		default: i = 0x00; break;
	}
}


int main(void){
	DDRA = 0X00; PINA = 0X0F; //A IS INPUT
	DDRC = 0XFF; PINC = 0X00; //B IS OUTPUT
    	state = start;
	i = 0x00;
	while (1) {
		TickFct();
    	}
    return 1;
}
