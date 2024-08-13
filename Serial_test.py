from machine import Pin,UART
import time
uart = UART(0, baudrate=115200, tx=Pin(0), rx=Pin(1))
uart.init(bits=8, parity=None, stop=2)
led = Pin("LED", Pin.OUT)
b = bytearray(b'\xAA')
print(b)

while True:
    uart.write(b)
    if uart.any(): 
        data = uart.read() 
        if data== b'm':
            led.toggle() 
    time.sleep(1)