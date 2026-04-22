# 3S LIPO battery BMS board
This is a project that allows you to monitor the voltage of a LIPO battery arranged in a 3S configuration. It features auto switch-off by way of MOSFETs, some current monitoring capabilities, and communication with a computer using a UART. This project was designed for use with a [GooseBot](https://github.com/lznfjv/goose). The system is controlled using an Arduino Nano.
## Features
- State of Charge monitoring
- UART/Serial computer communication
- Support for current monitoring with current shunt
- Automatic shutoff on dead battery
Watch the demo video [here](https://raw.githubusercontent.com/bax2004/bms/main/demos/bmsDemo.mp4).
## Installation and building
### Building hardware
Replicate the design shown in the schematics in the /pcb/ folder. PCB designs may become available at a later date.
### Building Firmware
#### Windows
- Download the Arduino IDE to help locate your Arduino, using the Board selector menu.
- Find your copy of `avrdude` (you will need this to upload this code to the Arduino). This is typically found as part of the Arduino IDE, usually under the path `C:\Users\<your username>\AppData\Local\Arduino15\packages\arduino\tools\avrdude\8.0.0-arduino1\bin\avrdude.exe`.
- Clone or download this Git repository.
- In terminal, go to the `firmware/` folder where the code was downloaded to, by running the following command:
```powershell
cd <path/to/file>
```
- Run the following command to upload it to the Arduino (bms.c has already been compiled), replacing the `path\to\board` with the location of your copy of `avrdude`, and the `<location of board>` with your Arduino's serial port:
```powershell
C:\path\to\avrdude.exe -c arduino -p m328p -P <location of board> -U flash:w:build/main.hex
```
#### Linux & MacOS
##### Prerequisites
You will need `avr-gcc` and `avrdude` to get this working.
On Ubuntu/Debian, run:
```bash
$ sudo apt install avr-gcc avrdude
```
if you don't have these tools.
##### Build Instructions
- Clone this project off Github:
```bash
$ git clone github.com/bax2004rj/bms
```
- Go to the Firmware folder under where the repo copied to:
```bash
$ cd ~/bms/firmware
```
- Provided you are not running the other demos found in `/firmware/` the code (`bms.c`) should already be built, and ready to upload to the Arduino. Plug in your Arduino, and locate it using:
```bash
$ ls /dev/ | grep tty
```
- For most Arduinos, the USB connection is typically located at `/dev/ttyACM*` where `*` is the device number. Some Nano boards, such as those used in testing with the CH340 serial driver are located at `/dev/ttyUSB*`.
>[!NOTE]
>You can also use the Arduino IDE for this task as well.

- Run the following command to upload the firmware to the board:
```bash
$ avrdude -c arduino -p m328p -P <location of board> -U flash:w:build/main.hex
```
>[!TIP]
>To compile the demos or recompile the main code (bms.c), use the following command:
>```bash
>$ avr-gcc <filename.c> -o build/main -mmcu=atmega328p -O1 $flags
>```
>Then rerun the avrdude command to upload it to the board.
