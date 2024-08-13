# T2408_OC_Serial_WS2812
System level documentation of my OC serial communication and WS2812 Interface 

## Legacy Transistor Solution
I have used NPN transistors in my old solutions. With appropriate transistors and resistors this solution can support at least bit rtes up to 115200 bps. The drawback is that it requires quite many discrete components.

### Transistor Circuit
![Transistor Circuit](/images/U2U_transistor.png)

### Test Results as 115200 bps
![Serial Transistor Results](/images/20240813-P8130280.jpg)
* Yellow MCU 1 TX pin
* Magenta Transistor Circuit Output
* Cyan MCU 2 TX Pin Echoing data
* Green TX signal after the 74HC07 buffer

All signal seems to handle the 115200 bps quite well

## New 74HC07 Solution

### 74HC07 Circuit

![74HC07 Circuit](/images/U2U_RGB_RST.png)

### Test Results
![Serial Transistor Results](/images/20240813-P8130281.jpg)

The rising edge is sligtly worse than with the transistor solution but is still accepted by the receiving MCU 1. The 115200 is the absolute max bitrate used as basis for the design. 



* https://github.com/infrapale/T2401_LightControl

