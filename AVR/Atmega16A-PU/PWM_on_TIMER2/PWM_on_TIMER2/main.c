#include <avr/io.h>

void PWM2_Ini(void) {
	ASSR = 0x00;
	TCCR2 = (1 << CS22) | (1 << CS21) | (1 << COM21) | (1 << WGM21) | (1 << WGM20);
	TCNT2 =0x00;
	OCR2 = 0xff;
}

int main(void)
{
    DDRD = 0xff;
	PORTD = 0xff;
	PWM2_Ini();
	OCR2 = 0x9f;
    while (1) 
    {
		
    }
}

