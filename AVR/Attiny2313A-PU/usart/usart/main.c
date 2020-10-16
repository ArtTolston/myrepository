#include "main.h"
#include "stdint.h"

void USART_Init(unsigned int speed) {
	UBRRH = (unsigned char)(speed >> 8);
	UBRRL = (unsigned char)(speed);
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRB |= (1 << RXCIE);
	UCSRA |= (1 << U2X);
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0) | (1 << UPM0) | (1 << UPM1);
}

void USART_Transmit(unsigned char data) {
	while( !(UCSRA & (1 << UDRE) ));
	UDR = data;
}

unsigned char USART_Reception(void) {
	while( !(UCSRA&(1 << RXC) ));
	return UDR;
}

ISR(USART_RX_vect) {
	PORTB = 0xff;
	_delay_ms(500);
	PORTB = 0x00;
}

int main(void)
{
	int speed = 3;
	unsigned char data;
    USART_Init(speed); // baudrate 
	sei();
    while (1) 
    {
		    USART_Transmit('X');//Передаем при включении
		    USART_Transmit('Y');//сообщение "Ok!", что свидетельствует
		    USART_Transmit('I');//о правильно работе программы
			USART_Transmit('_');
			USART_Transmit('s');
			USART_Transmit('o');
			USART_Transmit('S');
			USART_Transmit('E');
			USART_Transmit('H');
		    USART_Transmit(0x0d);//переход в начало строки
		    USART_Transmit(0x0a); // new line
		    _delay_ms(500);
// 			data = USART_Reception();
// 			PORTB |= data;
// 			_delay_ms(1000);
// 			PORTB &= ~(data);
    }
}

