# ESC-Latency-Project

This repository contains code to test the latency of PWM and I2C ESCs. Latency refers to the time between sending a command to change RPM of a motor and reading the desired RPM using a tachometer.

## Wiring Diagram:
1. Connect motor to ESC, and ESC to Power Supply/LiPo
2. For PWM:
    - connect ESC signal and ground to Adafruit Driver 
    - Connect Adafruit Driver VCC, SDA, SCL, and GND pins to Arduino
3. For I2C:
    - Connect SDA and SCL to respective pins on Arduino (20 and 21 on Mega)
    - NOTE: you may need pull up resistors for SDA and SCL
4. Wire the Digital Tachometer to a digital pin on Arduino (https://www.aliexpress.com/i/2251832549134134.html?gatewayAdapt=4itemAdapt).
5. Attach an encoder wheel (or black wheel with spokes) to the motor shaft.
6. Place tachometer so that wheel passes through IR sensor of the tachometer.
<br><br>

## PWM ESC: 
- Using Adafruit 16-channel 12-bit PWM Driver to convert I2C to PWM signal (https://www.adafruit.com/product/815).
- Use adafruit_pwm_lat.ino and esc_latency.py. When viewing the terminal output of the python script, there will be two latency values from the arduino (values greater than 8000) which are printed around the time of the increase in motor speed. These are the beginning and end times of the arduino's latency calculation, and their difference is the latency in milliseconds.
- adafruit_pwm.ino only includes the python latency value, not the arduino one (which is more precise).
- ESC Used: Multistar BLHeli-S 20A 2-4s V3.0
<br><br>

## I2C ESC: 
- Use i2c_lat.ino and i2c_esc_latency.py. When viewing the terminal output of the python script, there will be two latency values from the arduino (values greater than 8000) which are printed around the time of the increase in motor speed. These are the beginning and end times of the arduino's latency calculation, and their difference is the latency in milliseconds.
- i2c.ino only includes the python latency value, not the arduino one (which is more precise).
- ESC Used: MikroKopter Bl-Ctrl 2.0 controller
<br><br>

## Replication 
- change pulseCount variable depending on number of spokes on encoder wheel (.ino)
- For I2C: change I2C address (.ino)
- change serial port (.py)
- adjust command variable (.py)
- change RPM threshold (.py, .ino)
- change digitalPinToInterrupt to correct pin (.ino)

## Common Issues:
- For PWM escs, when arming, you must first send a pwm signal of 700 followed by a signal of 1000 to the esc. If the esc doesn't receive the second signal while it beeps HIGH, it will beep LOW and won't begin spinning. If the esc receives the the second signal before it beeps, it will not spin.
- When restarting a test, press reset on arduino board.