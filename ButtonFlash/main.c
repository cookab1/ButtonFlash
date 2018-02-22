/*
 * ButtonFlash.c
 *
 * Created: 2/18/2018 10:11:41 PM
 * Author : Andy
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "buttonFlash.h"


int main(void)
{
	DDRF = 0x0f;
	PORTF |= 0xc0;
	state = 0;
	
    while (1) 
    {
	    switch(state) {
			case 0:
				off();
				break;
		    case 1:
				rotate();
				break;
		    case 2:
				flash();
				break;
	    }
    }
}

