#define F_CPU 4000000L
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#define e0 PORTB &= ~(1 << PORTB3)
#define e1 PORTB |= (1 << PORTB3)
#define rs0 PORTB &= ~(1 << PORTB2)
#define rs1 PORTB |= (1 << PORTB2)

void port_ini() {
	PORTB = 0x00;
	DDRB = 0xff;
}

void send_low_halfbyte(unsigned char c) {
	c <<= 4;
	e1;
	_delay_us(50);
	PORTB &= 0b00001111;
	PORTB |= c;
	e0;
	_delay_us(50);
}

void send_byte(unsigned char c, int mode) {
	if(mode) {rs1;}
	else {rs0;}
	unsigned char hc = c >> 4;
	send_low_halfbyte(hc);
	send_low_halfbyte(c);
}

void setpos(unsigned int x, unsigned int y) {
	char address = 0x40 * y + x;
	address |= 0b10000000;
	send_byte(address, 0);
}

void LCD_ini() {
	_delay_ms(15);
	send_low_halfbyte(0b00000011);
	_delay_ms(4);
	send_low_halfbyte(0b00000011);
	_delay_us(100);
	send_low_halfbyte(0b00000011);
	_delay_ms(1);
	send_low_halfbyte(0b00000010);
	_delay_ms(1);
	send_byte(0b00101000, 0);
	_delay_ms(1);
	send_byte(0b00001110, 0); //cursor is turned on
	_delay_ms(1);
	send_byte(0b00000110, 0);
	_delay_ms(1);	
}


int main(void)
{
	port_ini();
	LCD_ini();
	setpos(8,1);
	send_byte('m', 1);
	setpos(4,0);
	send_byte('a', 1);
    while (1) 
    {
    }
}

