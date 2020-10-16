#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void USI_SPI_init() {
	DDRB |= (1 << PORTB4) | (1 << PORTB6) | (1 << PORTB7);
	DDRB &= ~(1 << PORTB5);
	PORTB &= ~(1 << PORTB4) | (1 << PORTB6) | (1 << PORTB7);
}

void Send_byte(unsigned char n) {
	USIDR = n;
	USISR |= (1 << USIOIF);
	while(!(USISR & (1 << USIOIF))) {
		USICR |=(1 << USIWM0) | (1 << USICLK) | (1 << USICS1) | (1 << USITC);
		_delay_us(10);
	}
}

int main(void)
{
    unsigned char n = 5;
	USI_SPI_init();
	
    while (1) 
    {
		Send_byte(n);
		_delay_us(50);
    }
}

