#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void ADC_init() {
	ADMUX = (1 << REFS0) | (1 << MUX0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

unsigned int ADC_Conversion(unsigned char regime) {
	if(regime == 'X') {
		ADMUX |= (1 << MUX0);
	} else if(regime == 'Y') {
		ADMUX &= ~(1 << MUX0);
	}
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	return (unsigned int)ADC;
}

void USART_Init(unsigned int speed) {
	UBRRH = (unsigned char)(speed >> 8);
	UBRRL = (unsigned char)(speed);
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC =  (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void USART_Transmit(unsigned char data) {
	while( !(UCSRA & (1 << UDRE) ));
	UDR = data;
}

unsigned char USART_Reception(void) {
	while( !(UCSRA&(1 << RXC) ));
	return UDR;
}

void PWM_Init() {
	TCNT1 = 0x00;
	TCCR1A |= (1 << WGM11) | (1 << COM1A1);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS12);
	ICR1H = 0x02;
	ICR1L = 0x71;
}


int main(void)
{
// 	ADC_init();
// 	int speed = 51;
//  	USART_Init(speed); //9600
//  	USART_Transmit('F');
//  	USART_Transmit('K');
	PWM_Init();
	OCR1AH = 0x00;
	OCR1AL = 0x2e;
// 	DDRC = 0xff;
// 	PORTC = 0x00;
	unsigned int num = 0;
	while (1)
	{
// 		num = ADC_Conversion('X');
// 		PORTC = 0x00;
// 		USART_Transmit('X');
// 		USART_Transmit((unsigned char)(num >> 2));
// 		num = 0;
// 		num = ADC_Conversion('Y');
// 		USART_Transmit('Y');
// 		USART_Transmit((unsigned char)(num >> 2));
// 		if(num > 800) {
// 			PORTC |= (1 << PORTC0);
// 			PORTC &= ~(1 << PORTC1);
// 		} else if(num < 200) {
// 			PORTC |= (1 << PORTC1);
// 			PORTC &= ~(1 << PORTC0);
// 		}
// 		num = 0;
// 		_delay_ms(500);
	}
}



