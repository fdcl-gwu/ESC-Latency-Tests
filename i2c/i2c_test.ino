#include <Wire.h>

#define TWI_BLCTRL_BASEADDR 0x2A

int motor_command = 0; //the motor speed that esc_latency sends
double lastEvent = 0;
double startMillis = millis();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  delay(100);
}

void loop() {
  //set motor RPM
  Serial.println(millis());
  if(millis()-startMillis <= 5000){
    motor_command = 10;
  }
  else{
    motor_command = 20;
  }
  send_command(motor_command);

}

void send_command(int cmd){
    Wire.beginTransmission(TWI_BLCTRL_BASEADDR);
    Wire.write(cmd);
    Wire.endTransmission();
}