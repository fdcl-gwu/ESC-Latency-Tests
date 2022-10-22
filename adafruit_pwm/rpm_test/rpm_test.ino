//Sketch to test RPM sensor, and increase accuracy
int pulseCount = 0;
int lastMeasured = 0;
double num_events = 0;

double period;
double freq;
double RPM;
double RPM_avg = 0;


void setup() {
  Serial.begin(9600);

  //for RPM sensor
  attachInterrupt(digitalPinToInterrupt(2), event, FALLING);
  delay(100);
}

void loop() {

}

void event(){
if(pulseCount == 6){
    //get period for one revolution
    double cur_millis = millis();
    period = cur_millis - lastMeasured;
    freq = 1000/period;
    RPM = freq*60;
    RPM_avg += RPM;
    if(num_events == 5){ //send avg of data to serial
      Serial.println(RPM_avg/5);
      RPM_avg = 0;
      num_events = -1;
    }
    lastMeasured = cur_millis;
    pulseCount = 0;
    num_events++;
  }
  else{
    pulseCount++;
  }
}
