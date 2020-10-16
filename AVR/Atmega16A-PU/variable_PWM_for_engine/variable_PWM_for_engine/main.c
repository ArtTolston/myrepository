#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void ADC_init() {
	ADMUX = (1 << REFS0) | (1 << ADLAR);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIE) | (1 << ADATE);
}

void ADC_Conversion(void) {
	ADCSRA |= (1 << ADSC);
}

void PWM_var_init(void) {
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS12);
	TCNT1 = 0x00;
	//TIMSK = (1 << TOIE1);
}

ISR(ADC_vect) {
	OCR1A = ADCH >> 1;
}

int main(void)
{
	DDRD = 0b00111000;
	PORTD = (1 << PORTD4);
    PWM_var_init();
	ADC_init();
	sei();
	ADC_Conversion();
	ICR1H = 0x00;
	ICR1L = 0xff;
	OCR1A = 0x00;
	  //1,5mc = 0x2e   , 2mc = 0x3e, 1mc = 0x20
    while (1) 
    {

    }
}

