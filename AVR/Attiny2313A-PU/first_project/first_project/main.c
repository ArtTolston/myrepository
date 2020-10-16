#define F_CPU 4000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void timer_init() {
	OCR1AH = 0b01111010;
	OCR1AL = 0b00010010;
	TCCR1B |= (1 << WGM12);
	TIMSK |= (1 << OCIE1A);
	TCCR1B |= (1 << CS12);
}

ISR(TIMER1_COMPA_vect) {
		if(PIND&0b00000001) {
			PORTD = 0x00;
		} else {
			PORTD = 0x7f;
		}
}

int main(void)
{
	timer_init();
	
    DDRD = 0b00000111;
	PORTD = 0b00000111;
	sei();
    while (1) 
    {
    }
}

