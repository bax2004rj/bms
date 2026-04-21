#include <avr/io.h>
#include <avr/interrupt.h>

int num[10] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};//default number font for use with setNumericalValue()
int digits = 3;//digit count
int digitData[3] = {0b00000110,0b01011011,0b01001111};//What each individual digit of the display is showing, as direct segment data.
int i = 0;//Keep track of the number being multiplexed (not running in for loop, using interrupts)

void init7sd(){
    DDRB = 0XFF;
    DDRD |= 0b11110000;
    TCNT0 = -100;
    TCCR0A = 0x00;
    TCCR0B = 0x02;
    TIMSK0 = (1<<TOIE0);
    sei();
}

void updateDigits(){
    if(i<digits-1){
        PORTD &= ~(1<<(i+4));
        i++;
    }else{
        i=0;
        PORTD &= ~(1<<digits+3);
    }
    PORTB = ~(digitData[i]>>1);
    PORTD |= (1<<7);
    PORTD |= (1<<i+4);
    PORTD &= ~(digitData[i]<<7);
    TCNT0 = -100;
}

void setNumericalValue(int data){ //Set the numerical value using an integer.
    for(int j = 0;j<digits;j++){
        if(j!=0&&data<10&&data%10==0){//Show nothing for trailing zeroes.
            digitData[digits-j-1]=0b00000000;
        }else{
            digitData[digits-j-1]=num[data%10];
        }
        data = data/10;
    }
}

void setDirectData(int digit, int data){ //Directly edit the byte holding the value in the display. Last 7 bytes are segments G-A, and first bit
    digitData[digit] = data;
}
