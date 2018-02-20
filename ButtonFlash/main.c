/*
 * ButtonFlash.c
 *
 * Created: 2/18/2018 10:11:41 PM
 * Author : Andy
 */ 

#include <avr/io.h>
#include <util/delay.h>

int stateTable[2][3] = {{1,0,1},
					  {2,2,0}};
int state;
int button;
int pressed;

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
	PORTF |= 0xc0;
	state = 0;
	pressed = 0;
	
	/*
    while((PINF & 0x40) && (PINF & 0x80));	//wait for a button to be pressed
    if((PINF & 0x40) == 0){ 		//if button0 was pressed
	    while(!(PINF & 0x40));  		//wait for button0 to be released
	    button = 0;
    } else { 				//button1 was pressed
	    while(!(PINF & 0x80));  		//wait for button1 to be released
	    button = 1;
    }
	*/	
	
    while (1) 
    {
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
			while((PINF & 0x40) && (PINF & 0x80));	//wait for a button to be pressed
			if((PINF & 0x40) == 0){ 		 //if button0 was pressed
				while(!(PINF & 0x40));  		//wait for button0 to be released
				PORTF |= 0xf;
				_delay_ms(200);
				PORTF &= 0xf0;
				_delay_ms(200);
				PORTF |= 0xf;
			} else if ((PINF & 0x80) == 0) { //button1 was pressed
				while(!(PINF & 0x80));  		//wait for button1 to be released
				PORTF &= 0xf0;
			}
			//buttonPressed();
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
    } else { 						//button1 was pressed
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
	//decrement counter 40 for 200 ms
	while(1) {
		PORTF |= 0xf;
		for(int i = 40; i > 0; i--) {
			if((PINF & 0x40) && (PINF & 0x80))
				_delay_ms(5);
			else {
				_delay_ms(5);
				if (PINF)
			}
		}
		button = delay(200);
		PORTF &= 0x0;
		if(button >= 0)
			return;
		button = delay(1000, ((PINF >> 6) & 0x3));
		PORTF &= 0x0;
		if(button >= 0)
			return;
	}
}

int delay(unsigned int msec, int prev) {
	int newState;
	unsigned int count = msec / 5;
	switch (prev) {
	case 0x3:
		for(int i = 0; i < count; i++) {
			if((PINF & 0x40) && (PINF & 0x80)) //if a button was not pressed
				_delay_ms(5);
			else {
				if((PINF & 0x40) == 0) //if button0 was pressed
					return 0;
				else 		//else button1 was pressed
					return 1;
			}
		}
		break;
	case 0x2:
		 
	}
	return newState;
}

void changeState() {
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

