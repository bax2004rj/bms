/*
    Simple program that cycles through various numbers that may show up incorrectly on the seven segment display if 7sd.h's leading zero detection is faulty.
    Copyright (C) 2026 Richard Carter (bax2004rj)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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
