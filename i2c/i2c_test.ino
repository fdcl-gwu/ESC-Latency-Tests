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
  if (Serial.available()){ //we receive signal to change motor RPM
    String input = Serial.readStringUntil('\n');
    Serial.println(1234); //test input to see if serial comm. is working
    motor_command = input.toInt();

    send_command(motor_command);
    Serial.println(motor_command);
  }
  send_command(motor_command);
}

void send_command(int cmd){
    Wire.beginTransmission(TWI_BLCTRL_BASEADDR);
    Wire.write(cmd);
    Wire.endTransmission();
}