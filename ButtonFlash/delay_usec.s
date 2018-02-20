/*
 * delay_usec.s
 *
 * Created: 1/25/2018 2:53:16 PM
 *  Author: john
 */ 

		.text
		.global delay_usec

delay_usec:
		dec		r24		// 1 cycle
		brlt	L3		//if false 1 cycle else 2
		brge	L4		
L1:		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
L4:		dec		r24		
		nop			
		nop			
		nop
		nop
		nop
		brge	L1	
L2:  	ret				// 5 cycles
L3:		adiw	r24, 33 // 1 cycle
		lsl		r24
		lsl		r24
		lsl		r24
		mul		r24, r24 // 2 cycles
		dec		r24
		brge	L1