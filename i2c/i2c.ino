#include <Wire.h>

#define TWI_BLCTRL_BASEADDR 0x2D

int motor_command = 0; //the motor speed that esc_latency sends
int pulseCount = 0;
int lastMeasured = 0;
int lastEvent = 0; //debouncing variable

double period;
double freq;
//double num_events = 0;
double RPM;
//double RPM_avg = 0;


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
  double cur_millis = millis();    
  if(cur_millis-lastEvent <= 1){
    return;
  }
//  Serial.println(pulseCount);
  if(pulseCount == 12){ //interrupt occurring on rising and falling?
    //get period for one revolution
    period = cur_millis - lastMeasured;
    freq = 1000/period;
    RPM = freq*60;
    Serial.println(RPM);
//    RPM_avg += RPM;
//    if(num_events == 5){ //send avg of data to serial
//      Serial.println(RPM_avg/5);
//      RPM_avg = 0;
//      num_events = -1;
//    }
    lastMeasured = cur_millis;
    lastEvent = cur_millis;
    pulseCount = 0;
//    num_events++;
  }
  else{
    lastEvent = cur_millis;
    pulseCount++;
  }
}