#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

#define SERVOARM  700  // pulse length to arm motor
#define SERVOMIN  1000 // minimum pulse length
#define SERVOMAX  1500 // maximum pulse length

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int motor_command = 0; //the motor speed that esc_latency sends
int pulseCount = 0;
int lastMeasured = 0;

double period;
double freq;
double num_events = 0;
double RPM;
double RPM_avg = 0;


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
  if(pulseCount == 6){
    //get period for one revolution
    double micro = millis();
    period = micro - lastMeasured;
    freq = 1000/period;
    RPM = freq*60;
    RPM_avg += RPM;
    if(num_events == 5){ //send avg of data to serial
      Serial.println(RPM_avg/5);
      RPM_avg = 0;
      num_events = -1;
    }
    lastMeasured = micro;
    pulseCount = 0;
    num_events++;
  }
  else{
    pulseCount++;
  }
}
