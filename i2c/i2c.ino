#include <Wire.h>

#define TWI_BLCTRL_BASEADDR 0x2D

unsigned long motor_command = 0; //the motor speed that esc_latency sends
int pulseCount = 0;
unsigned long lastMeasured = 0;

double period;
double freq;
double RPM;


void setup() {
  Serial.begin(9600);
  Wire.begin();

  //for RPM sensor
  attachInterrupt(digitalPinToInterrupt(2), event, RISING);
  delay(100);
}

void loop() {
  //set motor RPM
  if (Serial.available()){ //we receive signal to change motor RPM
    String input = Serial.readStringUntil('\n');
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
 
void event(){
  unsigned long cur_millis = millis();    
//  Serial.println(pulseCount);
  if(pulseCount == 2){
    //get period for one revolution
    period = cur_millis - lastMeasured;
    freq = 1000/period;
    RPM = freq*60;
    Serial.println(RPM);
    lastMeasured = cur_millis;
    pulseCount = 0;
  }
  else{
    pulseCount++;
  }
}