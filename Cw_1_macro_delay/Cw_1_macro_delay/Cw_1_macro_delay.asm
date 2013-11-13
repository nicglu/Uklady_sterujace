/*
 * Cw_1_macro_delay.asm
 *
 *  Created: 2013-10-30 17:24:59
 *   Author: Adrian Motyka, Nicole Gluszak
 */ 

//.def F_CPU = 6000000UL

 .MACRO delay_time
	
	LDI R16, @0 // 1
	INC R16	// inkrementuje ¿eby porównywaæ za pomoc¹ SUBI i BREQ
	LOOP:	
		SUBI R16, 1 // 1
		BREQ END // 1/2	- nadmiarowoœæ o 5 cykli przy ostatnim wykonaniu
		LDI R17, 23 // 1
		LOOP2:
			SUBI R17, 1 // 1
			BREQ LOOP // 1/2
			NOP		// 1
			LDI R18, 145 //1
			LOOP3:
				SUBI R18, 1 // 1
				BREQ LOOP2 // 1/2			
				JMP LOOP3 // 3
	END:
 .ENDM

 ; wyliczone za pomoc¹ równania kwadratowego parametry do pêtli z rejestrów R17 i R18 z uwzglêdnieniem nadmiarowych taktów
 delay_time 10
 NOP ; sprawdzenie iloœci cykli