/*
 * ButtonFlash.c
 *
 * Created: 2/18/2018 10:11:41 PM
 * Author : Andy
 */ 

#include <avr/io.h>

int stateTable[2][3] = {{1,0,1},
					  {2,2,0}};
int state;
int button;

void off();
void rotate();
void flash();


void delay_usec(unsigned int);
int delay(unsigned int);
void changeState();
void buttonPressed();

int main(void)
{
	DDRF = 0x0f;
	PORTF = 0xc0;
	state = 0;
	
    while((PINF & 0x40) && (PINF & 0x80));	//wait for a button to be pressed
    if((PINF & 0x40) == 0){ 		//if button0 was pressed
	    while(!(PINF & 0x40));  		//wait for button0 to be released
	    button = 0;
    } else { 				//button1 was pressed
	    while(!(PINF & 0x80));  		//wait for button1 to be released
	    button = 1;
    }
	
    while (1) 
    {
	        buttonPressed();
    }
}

//lights are off
void off() {
	if((PORTF & 0x0f) != 0)
		PORTF &= 0xf0;
	
    while((PINF & 0x40) && (PINF & 0x80)); 	//wait for a button to be pressed
    if((PINF & 0x40) == 0){ 		//if button0 was pressed
	    while(!(PINF & 0x40));  		//wait for button0 to be released
	    button = 0;
    } else { 				//button1 was pressed
	    while(!(PINF & 0x80));  		//wait for button1 to be released
	    button = 1;
    }
}

//rotate the lights being on from 0 - 3 each in turn
void rotate() {
	while(1) {
		PORTF |= 0x1;
		button = delay(1000);
		PORTF &= 0x0;
		if(button >= 0)
			return;
		
		PORTF |= 0x2;
		button = delay(1000);
		PORTF &= 0x0;
		if(button >= 0)
			return;
		
		PORTF |= 0x4;
		button = delay(1000);
		PORTF &= 0x0;
		if(button >= 0)
			return;
		
		PORTF |= 0x8;
		button = delay(1000);
		PORTF &= 0x0;
		if(button >= 0)
			return;
	}
}

// flash the lights for 200 mSec and off for 1 sec
void flash() {
	while(1) {
		PORTF |= 0xf;
		button = delay(200);
		PORTF &= 0x0;
		if(button >= 0)
			return;
		button = delay(1000);
		PORTF &= 0x0;
		if(button >= 0)
			return;
	}
}

int delay(unsigned int msec) {
	unsigned int count = msec / 5;
	for(int i = 0; i < count; i++) {
		if((PINF & 0x40) && (PINF & 0x80)) //if a button was not pressed
			delay_usec(5);
		else {
			if((PINF & 0x40) == 0) //if button0 was pressed
				return 0;
			else 		//else button1 was pressed
				return 1;
		}
	}
	return -1;
}

void changeState() {
	switch(state) {
		case 1:
			rotate();
			break;
		case 2:
			flash();
			break;
		default:
			off();
			break;
	}	
}

void buttonPressed() {
	if(button == 0){ 	//if button0 was pressed
		state = stateTable[button][state]; //set state to new state based on button0;
		changeState();
	} else { 		//button1 was pressed
		state = stateTable[button][state]; //set state to new state based on button1;
		changeState();
	}	
}

