#include <avr/io.h>


int main(void)
{
    DDRB = 0b10110001;
	PORTB = 0b01001111;
	SPCR = (1 << SPE) | (1 << MSTR);
	SPDR = 0b10000001;
	while(! (SPSR & (1 << SPIF)));
	PORTB |= (1 << PORTB4);
	PORTB &= ~(1 << PORTB4);
    while (1) 
    {
    }
}

