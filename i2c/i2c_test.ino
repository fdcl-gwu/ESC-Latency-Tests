#include <Wire.h>

#define TWI_BLCTRL_BASEADDR 0x2D

int motor_command = 0; //the motor speed that esc_latency sends
int pulseCount = 0;
int lastMeasured = 0;
int lastEvent = 0; //debouncing variable

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(100);
}

void loop() {
  //set motor RPM
  send_command(motor_command);

}

void send_command(int cmd){
    Wire.beginTransmission(TWI_BLCTRL_BASEADDR);
    Wire.write(cmd);
    Wire.endTransmission();
}
