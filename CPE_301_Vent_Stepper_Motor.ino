#include <Stepper.h>

//vent variables
const int StepsPerRev = 100; 
Stepper myMotor(StepsPerRev, 42, 44, 46, 48);
int Pval = 0;
int potenVal = 0;

void Vent_control();

void setup() {
  myMotor.setSpeed(200);
  Serial.begin(9600);
}

void loop() {
  Vent_control();
}

void Vent_control(){
  potenVal = map(analogRead(A0),0,1023,0,500);
  
  if(potenVal>Pval)
    myMotor.step(5);
  if(potenVal<Pval)
    myMotor.step(-5);
 Pval = potenVal;
}
