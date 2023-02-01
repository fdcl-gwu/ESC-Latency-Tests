#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

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

    pwm.setPWM(0, 0, motor_command);
    Serial.println(motor_command);
  }
  pwm.setPWM(0, 0, motor_command);

}
 
void event(){
  unsigned long cur_millis = millis();    
//  Serial.println(pulseCount);
  if(pulseCount == 6){ //interrupt occurring on rising and falling?
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
