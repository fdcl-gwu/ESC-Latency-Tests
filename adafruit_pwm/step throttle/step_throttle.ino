// Description: this code tests multiple motor speeds in a step-wise fashion. 
// Used without python script to determine latency, and motor speeds are
// determined by time intervals rather than commands from a python script.

// Note that latency is calculated and printed to output (see line 102).
// Note: the code here tests 4 motors through pwm.setPWM(0-3, intial_cmd, final_cmd),
// with 0-3 representing pins 0,1,2,3 on the Adafruit 16 channel PWM driver board. 

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int motor_command = 0; //the motor speed that esc_latency sends
int pulseCount = 0;
unsigned long lastMeasured = 0;

double period;
double freq;
double RPM;

int motor_command_0 = 0;   //motor off
int motor_command_1 = 700; //motor arm
int motor_command_2 = 820; //initial motor speed
int motor_command_3 = 850; //second motor speed

unsigned long start_time;
unsigned long cur_time;
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
  cur_time = millis();
//  Serial.println(cur_time);
  if(cur_time-start_time < 2000){      
    pwm.setPWM(0, 0, motor_command_0);
    pwm.setPWM(1, 0, motor_command_0);
    pwm.setPWM(2, 0, motor_command_0);
    pwm.setPWM(3, 0, motor_command_0);
  }
  else if(cur_time-start_time >= 2000 && cur_time-start_time < 4800){ //arm
    pwm.setPWM(0, 0, motor_command_1);
    pwm.setPWM(1, 0, motor_command_1);
    pwm.setPWM(2, 0, motor_command_1);
    pwm.setPWM(3, 0, motor_command_1);
  }
  else if(cur_time-start_time >= 4800 && cur_time-start_time < 10000){ //spin
    pwm.setPWM(0, 0, motor_command_2);
    pwm.setPWM(1, 0, motor_command_2);
    pwm.setPWM(2, 0, motor_command_2);
    pwm.setPWM(3, 0, motor_command_2);
  }
  else{
    for(int i=0; i<200; i+=5){
      pwm.setPWM(0, 0, motor_command_2-i);
      pwm.setPWM(1, 0, motor_command_2-i);
      pwm.setPWM(2, 0, motor_command_2-i);
      pwm.setPWM(3, 0, motor_command_2-i);
      Serial.println(motor_command_2-i);
      delay(1000);
    }
  }
//  Alternate else-condition below (use for constant 2nd motor speed)

//  else{
//    if(milli_i == 0){
//      milli_i = millis();
//      Serial.println(milli_i); //start of latency
//    }
//    pwm.setPWM(0, 0, motor_command_3);
//    pwm.setPWM(1, 0, motor_command_3);
//    pwm.setPWM(2, 0, motor_command_3);
//    pwm.setPWM(3, 0, motor_command_3);
//  }
}
 
void event(){
  double cur_millis = millis();    
//  Serial.println(pulseCount);
  if(pulseCount == 2){
    //get period for one revolution
    period = cur_millis - lastMeasured;
    freq = 1000/period;
    RPM = freq*60;
    if(RPM >=4250 && milli_f == 0){
      milli_f = cur_millis;
      Serial.println(milli_f-milli_i);
    }    
    Serial.println(RPM);
    lastMeasured = cur_millis;
    pulseCount = 0;
  }
  else{
    pulseCount++;
  }
}
