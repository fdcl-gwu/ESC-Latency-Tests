#include <Wire.h>

#define TWI_BLCTRL_BASEADDR 0x2D

unsigned long motor_command = 0; //the motor speed that esc_latency sends
int pulseCount = 0;
unsigned long lastMeasured = 0;

double period;
double freq;
double RPM;

int milli_i = 0;
int milli_f = 0;

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
    Serial.println(motor_command);
    
    send_command(motor_command);
  }
  send_command(motor_command);

}

void send_command(int cmd){
    if(motor_command == 40 && milli_i == 0){
      milli_i = millis();
      Serial.println(milli_i); //start of latency
    }
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
    if(RPM >=2500 && milli_f == 0){
      milli_f = cur_millis;
      Serial.println(milli_f);
    }
    Serial.println(RPM);
    lastMeasured = cur_millis;
    pulseCount = 0;
  }
  else{
    pulseCount++;
  }
}