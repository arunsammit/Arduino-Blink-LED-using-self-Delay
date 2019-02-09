volatile unsigned int tot_overflow=0;
#include <math.h>
#define F_CPU 16000000UL 
#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))
#include <avr/io.h>
#include <avr/interrupt.h>
ISR(TIMER0_OVF_vect){
	tot_overflow++;
}
void timer0_init(){
	sei();
	TCCR0B|=(1<<CS02);
	TCNT0=0;
	TIMSK0|=(1<<TOIE0);
}
void delay(float t){
	timer0_init();
	int maxOverFlow=floor(t/4.096);
	int registerCounter=floor((t/4.096-maxOverFlow)/.016);
	while(1){
		if(tot_overflow>=maxOverFlow){
			if(TCNT0>=registerCounter){
				tot_overflow=0;
				return;
			}
		}
	}
}
int main(void)
{
	int unsigned i=0;
	DDRB=255;
	while(1){
		for(i=0;i<=5;i++)
		{
			PORTB|=(1<<i);
			delay(200);
		}
		for (i=0;i<=5;i++)
		{
			PORTB&=~(1<<i);
			delay(200);
		}
		
		
	}
}

