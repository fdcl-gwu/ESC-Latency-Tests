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
    String input = Serial.readString(); //default setTimeout() == 1000ms
    motor_command = input.toInt();

    pwm.setPWM(0, 0, motor_command);
    Serial.println(motor_command);
  }
  //spin motor at selected RPM
  else {
    Serial.println("here");
    pwm.setPWM(0, 0, motor_command);
  }

}

void event(){
//    //TODO: improve RPM calculation
//  if (millis() - lastMeasured > 1000){
//    pulseCount = (pulseCount/6)*60; //RPM = RPS * 60
//    Serial.println(pulseCount);
//    lastMeasured = millis();
//    pulseCount = 0;
//  }
//  else {
//    pulseCount++;
//  }
}
