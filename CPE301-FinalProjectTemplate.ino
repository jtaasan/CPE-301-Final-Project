//Final Project Template
//Jonathan Taasan, Tara Hartman, Rachel Lykins, Alex Hsueh

//barebones/structure

//includes (put libraries in here)
#include <Stepper.h>

volatile unsigned char* port_e = (unsigned char*) 0x2E; 
volatile unsigned char* ddr_e  = (unsigned char*) 0x2D; 
volatile unsigned char* pin_e  = (unsigned char*) 0x2C;

//water variables
int waterlevel;
int resval = 0;  // holds the value for reservoir
int respin = A5; // sensor pin used for reservoir

//Vent Stepper Motor Variables
const int StepsPerRev = 100; 
Stepper myMotor(StepsPerRev, 42, 44, 46, 48);
int Pval = 0;
int potenVal = 0;

void setup (){
  U0init(9600);
  
  //vent speed
    myMotor.setSpeed(200);
  
  //fan motor
  *ddr_e |= 0b00001000; //FAN MOTOR PIN 5
  *ddr_e |= 0b00000100; //FAN MOTOR PIN 4
  *ddr_e |= 0b00000010; //FAN MOTOR PIN 3
}

void loop (){



/*
  if button pressed, then disable system{
    RTC timestamps disabled
    Yellow LED on
  }
  //else, do either idle, error, or running{

    //Do these Anyways
    waterlevel = watercheck();    //Water Level Monitoring 
    Templevel = dhtfunction();    //Humidity and Temperature Displayed
    Vent_control();             //Change Vent Position if Needed

    if(waterlevel == 1){
      display error
      RED LED on
      RTC timestamps error state
      Turn Fan off
    }
    else if(water level == 0){
      if(Templevel == 1){
      display error
      Blue LED on
      RTC timestamps running
      }
      else{
      Green LED on
      RTC timestamps idle
      }
    }
  }
*/
}

/*
  int watercheck(){
    int level = ALEX'S FUNCTION();
    if(level =< threshold){
      display error
      Serial.println("water level is too low");
      return(1);
    }
    else{
      clear error
      return(0);
    }
  }

  int dhtfunction(){
    int T_level = Jonathan's Function();
    hum thing
    lcd display both
    if(T_level > threshold){
      //turn on fan
      
      return(1);
    }
    else{
      //turn off fan
     
      return(0);
    }
  }

  void lcd function(){
    insert lcd function here to display things
  }

  void RTC function(){
    insert RTC function here to keep track of time
  }

//controls vent stepper motor
  void Vent_control(){
    potenVal = map(analogRead(A0),0,1023,0,500);
  
  //turns vent based on potentiometer
    if(potenVal>Pval)
      myMotor.step(5);
    if(potenVal<Pval)
      myMotor.step(-5);
   Pval = potenVal;

  }

  //NEED TO INCLUDE UART FUNCTIONS THAT REPLACE SERIAL FUNCTIONS


*/

void U0init(unsigned int U0baud)
{
 unsigned long FCPU = 16000000;
 unsigned int tbaud;
 tbaud = (FCPU / 16 / U0baud - 1);
 // Same as (FCPU / (16 * U0baud)) - 1;
 *myUCSR0A = 0x20;
 *myUCSR0B = 0x18;
 *myUCSR0C = 0x06;
 *myUBRR0  = tbaud;
}

int watercheck(){
    resval = analogRead(respin);
    if(resval <= 75){
      return(1);
    }
    else{
      return(0);
    }
}
