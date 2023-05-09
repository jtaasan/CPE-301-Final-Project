 // pin 28
  volatile unsigned char* port_a = (unsigned char*) 0x22;
  volatile unsigned char* ddr_a = (unsigned char*) 0x21;
  volatile unsigned char* pin_a  = (unsigned char*) 0x20;

// // pin 30
  volatile unsigned char* port_c = (unsigned char*) 0x28  ;
  volatile unsigned char* ddr_c  = (unsigned char*) 0x27 ;
  volatile unsigned char* pin_c = (unsigned char*) 0x26  ;


// // pin 38
  volatile unsigned char* port_d = (unsigned char*) 0x2B  ;
  volatile unsigned char* ddr_d = (unsigned char*) 0x2A ;
  volatile unsigned char* pin_d = (unsigned char*) 0x29  ;


// //pin 39
  volatile unsigned char* port_g = (unsigned char*) 0x34;
  volatile unsigned char* ddr_g = (unsigned char*) 0x33;
  volatile unsigned char* pin_g  = (unsigned char*) 0x32;





void setup() {


// assign 28 as output
  *ddr_a |= 0b01000000;

// //assign 30 as output
  *ddr_c |= 0b10000000;

// // assign 38 as output
  *ddr_d |= 0b10000000;

// //assign 39 as output
  *ddr_g |= 0b00000100;



}

void loop() {
  delay(5000);
  //turn on
  *port_a |= (0b01000000);
  *port_c |= (0b10000000);
  *port_d |= (0b10000000);
  *port_g |= (0b00000100);
  delay(5000) ;
  //turn off
  *port_a &= (0b10111111);
  *port_c &= (0b01111111);
  *port_d &= (0b01111111);
  *port_g &= (0b11111011);



}
