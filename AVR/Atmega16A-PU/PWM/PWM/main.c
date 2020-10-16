#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
void Port_Ini() {
	DDRD = 0xff;
	PORTD = 0xff;
}

void PWM1_Ini() {
	TCCR1A |= (1 << COM1A1)| (1 << WGM10);
	TCCR1B |= (1 << WGM12) | (1 << CS12);
	TCNT1 = 0x00;
	OCR1A = 0x00;
}

int main(void)
{
    Port_Ini();
	PWM1_Ini();
	int i;
    while (1) 
    {
		 for (i=0;i<255;i++)		//ѕлавно повышаем €ркость
		 {OCR1A++; _delay_us(200);}
		 for (i=0;i<255;i++)		//ѕлавно понижаем €ркость
		 {OCR1A--; _delay_us(200);}
    }
}

