#include <avr/io.h>
#define F_CPU 8000000L
#define EEPROM_H

void EEPROM_Write(uint8_t adres, uint8_t data) {
	while(EECR&(1 << EEPE));
	EECR = (1 << EEPM1) | (0 << EEPM0);
	EEAR = adres;
	EEDR = data;
	EECR |= (1 << EEMPE);
	EECR |= (1 << EEPE);	
}

unsigned char EEPROM_Read(uint8_t adres) {
	while(EECR&(1 << EEPE));
	EEAR = adres;
	EECR |= (1 << EERE);
	return EEDR;
}

int main(void)
{
    EEPROM_Write(0, 170);
	EEPROM_Write(2, 170);
    while (1) 
    {
    }
}

