/*
 * ButtonFlash.c
 *
 * Created: 2/18/2018 10:11:41 PM
 * Author : Andy
 */ 

#include <avr/io.h>
#include <util/delay.h>


static int state;

int button0[] = {1,0,1};
int button1[] = {2,2,0};

void off();
void rotate();
void flash();

int main(void)
{
	DDRF = 0xcf;
	PORTF = 0xc0;
	int prevState;
    /* Replace with your application code */
    while (1) 
    {
		/*
		if(prevState != state) {
			prevState = state;
			
		}
		*/
		//wait for button 1 to be pressed
		while((PORTF & 0x80));
		while(~(PORTF & 0x80));
		PORTF |= 3;
		/*
		switch(state) {
			case 0:
				off();
				break;
			case 1:
				rotate();
				break;
			case 2:
				flash();
		}
		*/
	}
		
}

//lights are off
void off() {
	PORTF &= 0xf0;
}

//rotate the lights being on from 0 - 4 each in turn
void rotate() {
	while(0) { //a button has not been pressed
		PORTF |= 0x01;
		_delay_ms(1000);
		PORTF &= 0x00;
		PORTF |= 0x02;
		_delay_ms(1000);
		PORTF &= 0x00;
		PORTF |= 0x04;
		_delay_ms(1000);
		PORTF &= 0x00;
		PORTF |= 0x08;
		_delay_ms(1000);
	}
}

// flash the lights for 200 mSec and off for 1 sec
void flash() {
	_delay_ms(200);
	_delay_ms(1000);
}

