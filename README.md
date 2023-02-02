# ESC-Latency-Project

This repository contains code to test the latency of PWM and I2C ESCs. Latency refers to the time between sending a command to change RPM of a motor and reading the desired RPM using a tachometer.
<br><br>
## PWM ESC: 
- use adafruit_pwm_lat.ino and esc_latency.py. When viewing the terminal output of the python script, there will be two latency values from the arduino (values greater than 8000) which are printed around the time of the increase in motor speed. These are the beginning and end times of the arduino's latency calculation, and their difference is the latency in milliseconds.
- adafruit_pwm.ino only includes the python latency value, not the arduino one (which is more precise).
<br><br>
## I2C ESC: 
- use i2c_lat.ino and i2c_esc_latency.py. When viewing the terminal output of the python script, there will be two latency values from the arduino (values greater than 8000) which are printed around the time of the increase in motor speed. These are the beginning and end times of the arduino's latency calculation, and their difference is the latency in milliseconds.
- i2c.ino only includes the python latency value, not the arduino one (which is more precise).
<br><br>
Replication:
I2C:
    - change pulseCount variable depending on number of spokes on encoder wheel (.ino)
    - change I2C address (.ino)
    - change serial port (.py)
    - adjust command variable (.py)
    - change RPM threshold (.py, .ino)
    - change digitalPinToInterrupt to correct pin (.ino)


## Common Issues:
- For PWM escs, when arming, you must first send a pwm signal of 700 followed by a signal of 1000 to the esc. If the esc doesn't receive the second signal while it beeps HIGH, then it won't begin spinning.
- When restarting a test, press reset on arduino board.