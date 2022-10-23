//Sketch to test RPM sensor, and increase accuracy
int pulseCount = 0;
int lastMeasured = 0;
int lastEvent = 0; //debouncing variable
double num_events = 0;

double period;
double freq;
double RPM;
//double RPM_avg = 0;


void setup() {
  Serial.begin(9600);

  //for RPM sensor
  attachInterrupt(digitalPinToInterrupt(2), event, FALLING);
  delay(100);
}

void loop() {

}

void event(){
  double cur_millis = millis();    
//  Serial.println(cur_millis);
//  Serial.print("last event = ");
//  Serial.println(lastEvent);
  if(cur_millis-lastEvent <= 1){
    Serial.println("returned");
    return;
  }
  Serial.println(pulseCount);
  if(pulseCount == 12){ //interrupt occurring on rising and falling?
    //get period for one revolution
    period = cur_millis - lastMeasured;
    freq = 1000/period;
    RPM = freq*60;
//    RPM_avg += RPM;
//    if(num_events == 5){ //send avg of data to serial
//      Serial.println(RPM_avg/5);
//      RPM_avg = 0;
//      num_events = -1;
//    }
    lastMeasured = cur_millis;
    lastEvent = cur_millis;
    pulseCount = 0;
    num_events++;
  }
  else{
    lastEvent = cur_millis;
    pulseCount++;
  }
}
