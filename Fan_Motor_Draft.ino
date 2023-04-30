//Fan Motor Code

#define ENABLE 5
#define DIRA 3
#define DIRB 4

int i;
 
void setup() {

// !!! NEEDS TO BE CHANGED TO ... NOT PINMODE !!!

  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);

}

void loop() {

// !!! NEEDS TO BE CHANGED TO ... NOT DIGITALWRITE !!!
  for (i=255;i>100;i--) {
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,LOW);
  analogWrite(ENABLE,i); 
  delay(1);
  }
  
}