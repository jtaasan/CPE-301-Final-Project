//iteration 5: pin 8,7,6
volatile unsigned char* port_h = (unsigned char*) 0x102; 
volatile unsigned char* ddr_h  = (unsigned char*) 0x101; 
volatile unsigned char* pin_h  = (unsigned char*) 0x100;

void setup(){
  Serial.begin(9600);
  *ddr_h |= 0b000111000;
}

void loop(){
  *port_h |= 0b000101000;

  delay(1000);

  *port_h &= (0b000000000);
  
  delay(1000);
}










//iteration 4
//volatile unsigned char* port_d = (unsigned char*) 0x102; 
//volatile unsigned char* ddr_d  = (unsigned char*) 0x101; 
//volatile unsigned char* pin_d  = (unsigned char*) 0x100;

//void setup() {
  // put your setup code here, to run once:
//Serial.begin(9600); //set baud rate

//*ddr_d |= 0b00100000; //enable pin 5 as output
//*ddr_d |= 0b00010000; //enable pin 4 as output
//}

//void loop() {
  // put your main code here, to run repeatedly:

  //Serial.println("Turning the motor off") ;
  //*port_e |= 0b0000100; //set pin 5 to HIGH
  //*port_d &= ~(0b00110000); //set pin 4 to LOW
  //*port_e |= 0b00000010;
  //delay(5000);

  //Serial.println("Turning the motor on");
  //*port_d |= (0b00110000);
  //delay(5000);
//}









// Fan motor iteration 3 

//volatile unsigned char* port_e = (unsigned char*) 0x2E; 
//volatile unsigned char* ddr_e  = (unsigned char*) 0x2D; 
//volatile unsigned char* pin_e  = (unsigned char*) 0x2C;

//void setup() {
  // put your setup code here, to run once:
//Serial.begin(9600); //set baud rate

//*ddr_e |= 0b00001000; //enable pin 5 as output
//*ddr_e |= 0b00000100; //enable pin 4 as output
//*ddr_e |= 0b00000010; //enable pin 3 as output


//}

//void loop() {
  // put your main code here, to run repeatedly:

  //*port_e |= 0b0000100; //set pin 5 to HIGH
  //*port_e &= ~(0b000001000); //set pin 4 to LOW
  //*port_e |= 0b00000010;
  
  //delay(1000);
  //*port_e |= ~(0b00000010);
  //delay(1000);
//}

//


//Fan motor iteration 2

// volatile unsigned char* port_e = (unsigned char*) 0x2E; 
// volatile unsigned char* ddr_e  = (unsigned char*) 0x2D; 
// volatile unsigned char* pin_e  = (unsigned char*) 0x2C;

// void setup() {
  // put your setup code here, to run once:
// Serial.begin(9600); //set baud rate

// *ddr_e |= 0b00001000; //enable pin 5 as output
// *ddr_e |= 0b00000100; //enable pin 4 as output
// *ddr_e |= 0b00000010; //enable pin 3 as output

// }

// void loop() {
  // put your main code here, to run repeatedly:

  // *port_e |= 0b00001000; //set pin 5 to HIGH
  // *port_e &= ~(0b00000100); //set pin 4 to LOW
  // analogWrite(3, 200); //set pin 3 to a speed (full speed = 255)
  
  // delay(1000);

// }





//Fan motor iteration 1

// #define ENABLE 5
// #define DIRA 3
// #define DIRB 4

// int i;
 
// void setup() {

// // !!! NEEDS TO BE CHANGED TO ... NOT PINMODE !!!

//   pinMode(ENABLE,OUTPUT);
//   pinMode(DIRA,OUTPUT);
//   pinMode(DIRB,OUTPUT);
//   Serial.begin(9600);

// }

// void loop() {

// // !!! NEEDS TO BE CHANGED TO ... NOT DIGITALWRITE !!!
//   for (i=255;i>100;i--) {
//   digitalWrite(DIRA,HIGH);
//   digitalWrite(DIRB,LOW);
//   analogWrite(ENABLE,i); 
//   delay(1);
//   }
  
// }
