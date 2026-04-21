#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "7sd.h"
#include "uart.h"

int main(){
    init7sd();

    while(1){
        setNumericalValue(9);
        _delay_ms(500);
        setNumericalValue(109);
        _delay_ms(500);
        setNumericalValue(0);
        _delay_ms(500);
    }
    return 0;
}
ISR(TIMER0_OVF_vect){
    updateDigits();
}
