#include <avr/io.h>

void initADC(){
    //Init ADC
    ADCSRA=(1<<ADEN)|(1<<ADPS0);
    ADMUX=(1<<REFS0);
}

int analogRead(int pin){
    ADMUX = (ADMUX & 0xF0)|(pin&0x0F);
    for(int i =0;i<2;i++){// Run a dummy sample
        ADCSRA |= (1<<ADSC);
        while((ADCSRA&(1<<ADIF))==0);
    }
    return ADC;
}
