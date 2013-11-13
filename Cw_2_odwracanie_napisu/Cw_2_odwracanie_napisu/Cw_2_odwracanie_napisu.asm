/*
 * Cw_2_odwracanie_napisu.asm
 *
 *  Created: 2013-11-06 17:04:00
 *   Author: Adrian Motyka, Nicole Gluszak
 */ 

.DEF stos=R20


LDI R16, 9 ; dane sprzed wywo≥ania procedury
LDI R17, 11

ldi stos, low(FLASHEND)	
out	SPL, stos			
ldi stos, high(FLASHEND)
out SPH, stos

LDI ZL, Low(NAPIS*2)	; Ustawienie wskaünika Z na napis
LDI ZH, High(NAPIS*2)

CALL PROC
JMP FINISH
 PROC: 

	PUSH R0
	PUSH R4
	PUSH R5
	PUSH R16
	PUSH R17
	PUSH R26
	PUSH R28
	PUSH R30


	LDI R17, 0 ; inicjalizowanie licznika liter

	LDI XH, HIGH(0x0060) ; wskaünik w SRAM na napis
	LDI XL, LOW(0x0060)

	LDI YH, HIGH(0x0060) ; wskaünik w SRAM na napis
	LDI YL, LOW(0x0060)

	LOAD:
		LPM
		LD R16, Z+ ; oszustwo, inkrementacja Z
		MOV R16, R0
		CPI R16, 0 ; if R16 == 0
		BREQ DIV
		ST X+, R0
		INC R17 ; zliczanie liter
		JMP LOAD

	DIV:	; znalezienie po≥owy
		ROR R17 
		JMP STORE

	STORE:	; zamiana 'w miejscu'
		
		LD R5, Y 
		PUSH R5
		LD R4, -X
		ST Y+, R4
		POP R5
		ST X, R5
		DEC R17
		BREQ END
		JMP STORE

	END:

		POP R30
		POP R28
		POP R26
		POP R17	; przywrÛcenie poprzednich wartoúci
		POP R16
		POP R5
		POP R4
		POP R0

	RET

FINISH:

.CSEG
NAPIS:
	.db "HELLO WORLD",0

