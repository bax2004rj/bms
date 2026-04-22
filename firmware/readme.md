# Firmware code for BMS
This directory contains the source code and binaries for the Arduino used on the BMS project. There are some demos used during development to test the included header files. These can be compiled and put on the Arduino.
These files are as follows:
- `7sd_trail0test.c`: Simple program that cycles through various numbers that may show up incorrectly on the seven segment display if `7sd.h`'s leading zero detection is faulty.
- `7sd_counttest.c`: Counts from 0-200 using the seven segment display.
- `7sd_uart_counttest`: Version of `7sd_counttest.c` that prints the expected number over the serial port.
- `bms_uart+.c`: Version of `bms.c` that contains a failed, but more advanced serial interaction system. Not recommended to evaluate the hardware.
