import serial
import numpy as np
import matplotlib.pyplot as plt
import time

ser = serial.Serial('/dev/cu.usbmodem14101',9600)
time.sleep(5)
ser.flushInput()
ser.flushOutput()

command = 700
data = []

print('write arm')
ser.write((str(command)+'\n').encode()) #arm motor
time.sleep(2.5)

command = 1000
ser.write((str(command)+'\n').encode()) #spin motor

input("Enter value to begin reading")
#read serial for 5 seconds
start = time.time()
# while (time.time() - start) <  10:
#     input_byte = serial.readline()
#     string = input_byte.decode()
#     string = string.rstrip()
#     RPM = float(string)
#     data.append(RPM)

# plt.plot(data)
# plt.xlabel('Time')
# plt.ylabel('RPM')
# plt.title('')
# plt.show()

ser.close()