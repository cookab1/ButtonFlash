/*
 * ButtonFlash.c
 *
 * Created: 2/18/2018 10:11:41 PM
 * Author : Andy
 */ 

#include <avr/io.h>


static int state;

int button0[] = {1,0,1};
int button1[] = {2,2,0};

void off();
void rotate();
void flash();

void delay_usec(unsigned int);
void delay(unsigned int);

int main(void)
{
	DDRF = 0x0f;
	PORTF = 0xc0;
	state = 2;
	
    while (1) 
    {
	    */
	    while((PINF & 0x40) && (PINF & 0x80));
	    if((PINF & 0x40) == 0){ //if button0 was pressed
		    //wait for button to be released
		    while(!(PINF & 0x40));
		    PORTF |= 0xf;
		    state = button0[state]; //set state to new state based on button0;
		} else { //button1 was pressed
		    //wait for button1 to be released
		    while(!(PINF & 0x80));
		    PORTF &= 0x0;
		    state = button0[state]; //set state to new state based on button1;
	    }
		*/
		//wait for a button to be pressed
		while((PINF & 0x40) && (PINF & 0x80)) {
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
		//PORTF = 0;
		if((PINF & 0x40) == 0){ //if button0 was pressed
			//wait for button to be released
			while(!(PINF & 0x40));
			PORTF |= 0x4;
			state = button0[state]; //set state to new state based on button0;
		} else { //button1 was pressed
			//wait for button1 to be released
			while(!(PINF & 0x80));
			PORTF |= 0x2;
			state = button0[state]; //set state to new state based on button1;
		}
		
    }
}

//lights are off
void off() {
	if((PORTF & 0x0f) != 0)
		PORTF &= 0xf0;
}

//rotate the lights being on from 0 - 3 each in turn
void rotate() {
	PORTF |= 0x1;
	delay(1000);
	PORTF &= 0x0;
	PORTF |= 0x2;
	delay(1000);
	PORTF &= 0x0;
	PORTF |= 0x4;
	delay(1000);
	PORTF &= 0x0;
	PORTF |= 0x8;
	delay(1000);
	PORTF &= 0x0;
}

// flash the lights for 200 mSec and off for 1 sec
void flash() {
	PORTF |= 0xf;
	delay(200);
	PORTF &= 0x0;
	delay(1000);
}

void delay(unsigned int msec) {
	unsigned int count = msec / 5;
	for(int i = 0; i < count; i++)
		if((PINF & 0x40) && (PINF & 0x80))
			delay_usec(5);
		else
			changeState();
}

