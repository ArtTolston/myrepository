#include "usart.h"

void USART_Init(unsigned int speed) {
	UBRRH = (unsigned char)(speed >> 8);
	UBRRL = (unsigned char)(speed);
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRB |= (1 << RXCIE);
	UCSRA |= (1 << U2X);
	UCSRC = (1 << USBS) | (1 << UCSZ1) | (1 << UCSZ0);
}

void USART_Transmit(unsigned char data) {
	while( !(UCSRA & (1 << UDRE) ));
	UDR = data;
}