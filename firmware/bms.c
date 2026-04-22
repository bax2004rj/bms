/*
 *  3S Battery management system
 *  Copyright (C) 2026 Richard Carter (bax2004rj)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#define F_CPU 16000000UL
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "7sd.h"
#include "uart.h"
#include "adc.h"

int percent = 50;
const double maximumVoltage= 12.6;//12.6V = 100% battery for 3S.
const double mininumVoltage= 10.0;//10V = 0% battery for 3S.
const double voltageChange=maximumVoltage-mininumVoltage;
int dataSent = 0;

char cmd[32];
int cmdChars = 0;
int cmdStatus = 0x03;//bit 0: command ready, bit 1: ready indicator generated, bit 2: newline sent, bit 3: echo off, bit 4: power off, bit 5: monitor loop enabled
int dispMode = 0;//0: percentage (default), 1: voltage, 2+ off

int main(){
    init7sd();
    initADC();
    initUart();
    DDRD |= (1<<3); //MOSFET pin
    while(1){
        //Check battery voltage
        int adcVal = analogRead(0);
        float voltage = ((double)adcVal/1023)*15.84;
        if(voltage<maximumVoltage&&voltage>mininumVoltage){
            double p = ((voltage-mininumVoltage)/voltageChange)*100;
            percent = (int) p;
        } else if (voltage<=mininumVoltage){
            percent = 0;
        } else {
            percent = 100;
        }
        if(dispMode==0){
            setNumericalValue(percent);
        } else if(dispMode==1){
            setNumericalValue(voltage);
        }
        if(percent == 1&&dataSent==0){ //Send shutdown request over UART before battery dies
            printf("\n\rshutdown\n\r");
            dataSent = 1;
        }
        if((percent <= 0||cmdStatus&(1<<4))==!0){ //0% or command shutoff
            PORTD &= ~(1<<3);
        }else{
            PORTD |= (1<<3);
        }
        //Current monitoring
        int currentADC=analogRead(1);
        //UART printing
        printf("ADC: %d, Voltage: %f, Battery Percentage: %d, ADC1 (Current):%d \n\r",adcVal,voltage,percent,currentADC);
    }
    return 0;
}
ISR(TIMER0_OVF_vect){
    updateDigits();
}
