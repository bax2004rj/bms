# 3S LIPO battery BMS board
This is a project that allows you to monitor the voltage of a LIPO battery arranged in a 3S configuration. It features auto switch-off by way of MOSFETs, some current monitoring capabilities, and communication with a computer using a UART. This project was designed for use with a [GooseBot](https://github.com/lznfjv/goose). The system is controlled using an Arduino Nano.

## Installation and building
### Building hardware
Replicate the design shown in the schematics in the /pcb/ folder. PCB designs may become available at a later date.
### Building Firmware
#### Linux
##### Prerequisites
You will need `avr-gcc` and `avrdude` to get this working.
On Ubuntu/Debian, run:
```bash
$ sudo apt install avr-gcc avrdude
```
##### Build Instructions
Clone this project off Github:
```bash
$ git clone github.com/bax2004rj/bms
```
Go to the Firmware folder under where the repo copied to:
```bash
$ cd ~/bms/firmware
```
Provided you are not running the other demos found in /firmware/ the code should already be built, and ready to upload to the Arduino. PLug in your Arduino, and locate it using:
```bash
$ ls /dev/ | grep tty
```
For most Arduinos, the USB connection is typically located at `/dev/ttyACM*` where `*` is the device number. Some Nano boards, such as those used in testing with the CH340 serial driver are located at `/dev/ttyUSB*`.
Run the following command to upload the data to the board:
```bash
$ avrdude -c arduino -p m328p -P <location of board> -U flash:w:build/main.hex
```
>[!TIP]
>To compile the demos or recompile the main code (bms.c), use the following command:
>```bash
>$ avr-gcc <filename.c> -o build/main -mmcu=atmega328p -O1 $flags
>```
>Then rerun the avrdude command to upload it to the board.
