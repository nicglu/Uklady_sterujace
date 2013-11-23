/*
 * CW5.c
 *
 * Created: 2013-11-20 15:37:38
 *  Author: Adrian Motyka, Nicole Gluszak
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#define MAX_TASKS 10
#define NO_PERIODIC 0
#define NOT_READY 0

#define F_CPU 16000000UL

typedef struct task Task;
typedef void (*TASK_PTR) (void);

 struct task{
	 
	TASK_PTR tsk;
	uint8_t ready;
	uint16_t interval;
	uint16_t toGo;
	uint8_t priority;
} ;

Task tasks[MAX_TASKS];

uint8_t TASK_COUNT = 0;


void schedule(){
	
	// timer
	//TIMSK &= ~(1 << OCIE0);
	//TIMSK |= (1 << TOIE0);
	TIMSK |= (1 << OCIE0);
	TIMSK &= ~(1 << TOIE0);
	TCCR0 |= (1 << WGM01);
	TCCR0 &= ~(1 << WGM00);
	TCCR0 |= (1 << CS00);
	TCCR0 |= (1 << CS01);
	TCCR0 &= ~(1 << CS02);
	
	OCR0 = 1000;
	
	//przerwania
	sei();
	
	Task * tsk;
	while( TASK_COUNT > 0){
		int i;
		tsk = 0;
		for(i = 0; i < TASK_COUNT; i++){
			if(tasks[i].ready != NOT_READY){
				if(tsk != 0){
					if(tsk->priority > tasks[i].priority){
						tsk = & tasks[i];
					}
				}else{
					tsk = & tasks[i];
				}
			}
		}
		if(tsk != 0){
			tsk->ready--;
			tsk->tsk();
		}
	}
}

void AddTask(TASK_PTR tsk, uint16_t interval, uint8_t priority){
	if(TASK_COUNT + 1 < MAX_TASKS){
		tasks[TASK_COUNT].tsk = tsk;
		tasks[TASK_COUNT].ready = 1;
		tasks[TASK_COUNT].toGo = 1;
		tasks[TASK_COUNT].priority = priority;
		tasks[TASK_COUNT++].interval = interval;		
	}
}


void Set0(){
	PORTA ^= 1<<0;
}

void Set1(){
	PORTA ^= 1<<1;
}

void Set2(){
	PORTA ^= 1<<2;
}

void Set3(){
	PORTA ^= 1<<3;
}


int main(void)
{
	DDRA = 0xFF;
	//PORTA = 0b11111111; // AtMega 16
	PORTA = 0b00000000;
	
	AddTask(Set0, 1, 0);
	AddTask(Set1, 2, 1);
	AddTask(Set2, 3, 2);
	AddTask(Set3, 4, 3);
	
    schedule();
}


ISR(TIMER0_COMP_vect){
//ISR(TIMER0_OVF_vect){
	uint8_t i;
	Task * tsk;
	for(i = 0; i < TASK_COUNT; i++){
		tsk = & tasks[i];
		if(tsk->interval != NO_PERIODIC){
			tsk->toGo--;
			if(tsk->toGo == 0){
				tsk->toGo = tsk->interval;
				tsk->ready++;
			}
		}else if(tsk->toGo > 0){
			tsk->toGo--;
			if(tsk->toGo == 0){
				tsk->ready++;
			}
		}
	}	
}