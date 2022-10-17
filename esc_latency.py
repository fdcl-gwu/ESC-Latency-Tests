import serial
import numpy as np
import matplotlib.pyplot as pyplot
import time

ser = serial.Serial('/dev/cu.usbmodem14101',9600)
time.sleep(2)
ser.flushInput()
ser.flushOutput()

arm = 700
data = []

# to get time, use time.time()
t = time.time()
print(t)

# send command to arm motor
ser.write(str(arm).encode())
time.sleep(1)
while 1:
    new_speed = input("Enter value between 1000 and 2000: ")
    ser.write(str(new_speed).encode())
    time.sleep(1)

ser.close()