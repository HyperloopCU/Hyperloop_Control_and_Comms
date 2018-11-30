import serial
import time

ser = serial.Serial("/dev/ttyS0")
ser.baudrate = 9600
time.sleep(2)

a = raw_input()
ser.write(a)

while True:
   x = ser.readline()
   print x
   # a = raw_input()
   # ser.write(a)

