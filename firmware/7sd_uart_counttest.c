#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "7sd.h"
#include "uart.h"

int main(){
    init7sd();
    initUart();
    while(1){
        //setNumericalValue(109);
        //setDirectData(1,0b011111111);
        for(int n=0;n<200;n++){
            setNumericalValue(n);
            printf("%d\n\r",n);
            _delay_ms(500);
        }
    }
    return 0;
}
ISR(TIMER0_OVF_vect){
    updateDigits();
}
