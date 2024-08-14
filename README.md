# Open Drain UART 2 UART Solution and WS2812 Adapter

System level documentation of my open-drain MCU interconnection UART to UART communication and WS2812 Interface.

I have been using the open drain interface to connect multiple MCU's to the same lines. The circuit can also adapt between 3.3V and 5V. 
---
## Topology

### Single Main 2 Line
![Single Main](/images/SingleMain-2-Line.png)

### All 2 All 1 Line
![All 2 All](/images/All2All-1-Line.png)
---
## Test Setup

![Test Setup](/images/U2U_Test_Setup.png)

MCU 1 is continiously send 0xAA to MCU 2. MCU 2 is echoing the received code back to MCU 1.  I have used the bitrate 115200 bps for the stress test. 

### MCU 1 Micropython Code
```
from machine import Pin,UART
import time
uart = UART(0, baudrate=115200, tx=Pin(0), rx=Pin(1))
uart.init(bits=8, parity=None, stop=2)
b = bytearray(b'\xAA')
print(b)

while True:
    uart.write(b)
    if uart.any(): 
        data = uart.read() 
    time.sleep(1)
```
### MCU 2 Arduino Code
```
/*
  Serial HW Test
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialPassthrough
*/

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  if (Serial1.available()) {       // If anything comes in Serial1 (pins 0 & 1)
    char c = Serial1.read();  // read it and send it out Serial (USB)
    Serial1.write(c);
    Serial.write(c);
  }
}
```
---

## Legacy Transistor Solution
I have used NPN transistors in my old solutions. With appropriate transistors and resistors this solution can support at least bit rtes up to 115200 bps. The drawback is that it requires quite many discrete components.

### Transistor Circuit
![Transistor Circuit](/images/U2U_transistor.png)
![Transistor PCB](/images/Transistor_U2U_Module.jpg)

### Test Results as 115200 bps
![Serial Transistor Results](/images/20240813-P8130280.jpg)
* Yellow MCU 1 TX pin
* Magenta Transistor Circuit Output
* Cyan MCU 2 TX Pin Echoing data
* Green TX signal after the 74HC07 buffer

All signal seems to handle the 115200 bps quite well

## New 74HC07 Solution

The 74HC07 IC is an open drain non-inverting buffer which is perfect for my needs here

![74HC07 IC](/images/74HC07.jpg)


### 74HC07 Circuit

![74HC07 Circuit](/images/U2U_RGB_RST.png)
![Pico Combo](/images/Pico_Combo_PCB.jpg)

### Test Results
![74HC07 Results](/images/20240813-P8130281.jpg)

The rising edge is sligtly worse than with the transistor solution but is still accepted by the receiving MCU 1. The 115200 is the absolute max bitrate used as basis for the design. 
---
## Bonus Feature

The 74HC07 IC can also be used for:
* Level shifter for WS2812 (RGB LED) 
* Reset output for connected MCU's or sensors

### Driving WS2812 LED strips

THe voltage level shift is implemented using a pullup resistor connected to 5 Volts. The data rate (800 kHz) is high and some previous attempts to make a level shifter did not work out satisfactory.

![RGB Level Shifter](/images/WS2812_Level_Shifter.png)

![WS2812 data](/images/20240813-P8130285.jpg)
*Yellow MCU output pin
*Magenta Level shifted signal to the LED strip



