//Final Project Template
//Jonathan Taasan, Tara Hartman, Rachel Lykins, Alex Hsueh

//barebones/structure

volatile unsigned char* port_e = (unsigned char*) 0x2E; 
volatile unsigned char* ddr_e  = (unsigned char*) 0x2D; 
volatile unsigned char* pin_e  = (unsigned char*) 0x2C;

//includes (put libraries in here)
#include <Stepper.h>


//water variables
int waterlevel;
int resval = 0;  // holds the value for reservoir
int respin = A5; // sensor pin used for reservoir


void setup (){
  U0init(9600);
}

void loop (){
*ddr_e |= 0b00001000; //enable pin 5 as output
*ddr_e |= 0b00000100; //enable pin 4 as output
*ddr_e |= 0b00000010; //enable pin 3 as output


/*
  if button pressed, then disable system{
    RTC timestamps disabled
    Yellow LED on
  }
  //else, do either idle, error, or running{

    //Do these Anyways
    waterlevel = watercheck();    //Water Level Monitoring 
    Templevel = dhtfunction();    //Humidity and Temperature Displayed
    vent function();              //Change Vent Position if Needed

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
      *port_e |= 0b00001000; //set pin 5 to HIGH
      *port_e &= ~(0b00000100); //set pin 4 to LOW
      *port_e |= 0b00000010;
  
      delay(1000);
      *port_e |= ~(0b00000010);
      delay(1000);
  
  
      return(1);
    }
    else{
      //turn off fan
      *port_e |= 0b00000100; //set pin 5 to HIGH
      *port_e &= ~(0b00001000); //set pin 4 to LOW
      *port_e |= 0b00000010;
  
      delay(1000);
      *port_e |= ~(0b00000010);
      delay(1000);
      return(0);
    }
  }

  void lcd function(){
    insert lcd function here to display things
  }

  void RTC function(){
    insert RTC function here to keep track of time
  }

  void vent function(){
    turns vent

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
    if(resval <= 100){
        *port_e &= ~(0b00001000);
        *port_e &= ~(0b00000100);
        *port_e &= ~(0b00000010);
      return(1);
    }
    else{
      return(0);
    }
}
