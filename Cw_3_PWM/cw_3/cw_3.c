/*
 * cw_3.c
 * Created: 2013-11-13 16:18:39
 *  Author: Nicole G³uszak, Adrian Motyka
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL

/*void SETUP_TIMEOUT(int us){	
	TCCR0 &= ~(1 << WGM00); // zmiana trybu pracy na CTC
	TCCR0 |= (1 << WGM01);
	
	TCCR0 |= (1 << COM00); // ustawienie zachowania pinu OC
	TCCR0 &= ~(1 << COM01); 
	
	TCCR0 &= ~(1 << CS00); // ustawienie zegara
	TCCR0 |= (1 << CS01);
	TCCR0 &= ~(1 << CS02);
	
	OCR0 = us*0x10;
	
	TIMSK |= (1 << OCIE0);
	
	sei();	// w³¹cznie przerwañ
}*/

void SETUP_PWM(){		
	TCCR0 |= (1 << WGM00); // zmiana trybu pracy na FastPWM
	TCCR0 |= (1 << WGM01);
	
	TCCR0 |= (1 << COM01); // ustawienie zachowania pinu OC
	TCCR0 &= ~(1 << COM00);
	
	TCCR0 |= (1 << CS00); // ustawienie zegara
	TCCR0 &= ~(1 << CS01);
	TCCR0 &= ~(1 << CS02);
	
	OCR0 = 0x10;
}

void SET_PWM(int x){
	OCR0 = x % 256;
}

/*ISR(TIMER0_OVF_vect){	
	
}*/

int main(void)
{
	int i = 0;
	SETUP_PWM();
	//SETUP_TIMEOUT(10);
    while(1)
    {
		DDRB |= (1 << PB3);
		i++;
		i = i % 256;
		SET_PWM(i);
        _delay_ms(10);
    }
}