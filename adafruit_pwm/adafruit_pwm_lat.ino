// Desctiption: similar to adafruit_pwm.ino, but latency calculation is done 
// in this file, and not just the python script (see README). 
// Prints result to terminal.

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int motor_command = 0; //the motor speed that esc_latency sends
int pulseCount = 0;
unsigned long lastMeasured = 0;
unsigned long lastEvent = 0; //debouncing variable

double period;
double freq;
//double num_events = 0;
double RPM;
//double RPM_avg = 0;

int milli_i = 0;
int milli_f = 0;

void setup() {
  Serial.begin(9600);

  //for i2c driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  //for RPM sensor
  attachInterrupt(digitalPinToInterrupt(2), event, RISING);
  delay(100);
}

void loop() {
  //set motor RPM
  if (Serial.available()){ //we receive signal to change motor RPM
    String input = Serial.readStringUntil('\n');
    motor_command = input.toInt();
    if(motor_command == 1010 && milli_i == 0){
      milli_i = millis();
      Serial.println(milli_i); //start of latency
    }
    pwm.setPWM(0, 0, motor_command);
  }
  pwm.setPWM(0, 0, motor_command);

}
 
void event(){
  unsigned long cur_millis = millis();    
//  Serial.println(pulseCount);
  if(pulseCount == 2){ //interrupt occurring on rising and falling?
    //get period for one revolution
    period = cur_millis - lastMeasured;
    freq = 1000/period;
    RPM = freq*60;
    if(RPM >=3000 && milli_f == 0){
      milli_f = cur_millis;
      Serial.println(milli_f);
    }
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
