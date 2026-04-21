#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

int sendUartChar(char,FILE *);//This will be defined later

FILE uartFile = FDEV_SETUP_STREAM(sendUartChar, NULL, _FDEV_SETUP_WRITE);//Make the UART a file so stdout can replace it.

void initUart(){//Set up UART for 9600,8,N,1
    UCSR0B=(1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);
    UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
    UBRR0L=103;
    stdout = &uartFile; //Use printf to send data out of the serial port instead of for loop chicanery.
}

int sendUartChar(char data, FILE *stream){
    while(!(UCSR0A&(1<<UDRE0)));
    UDR0=data;
    return 0;
}

int sendChar(char data){ //Identical to the above command, but with the FILE varible missing.
    while(!(UCSR0A&(1<<UDRE0)));
    UDR0=data;
    return 0;
}
