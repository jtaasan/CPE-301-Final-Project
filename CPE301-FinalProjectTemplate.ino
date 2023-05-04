//Final Project Template
//Jonathan Taasan, Tara Hartman, Rachel Lykins, Alex Hsueh

//barebones/structure

int waterlevel;

void setup (){
  U0init(9600);
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
      turn on fan
      return(1);
    }
    else{
      turn off fan
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
