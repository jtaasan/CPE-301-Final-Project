//Final Project Template
//Jonathan Taasan, Tara Hartman, Rachel Lykins, Alex Hsueh


//includes (put libraries in here)
#include <Stepper.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#include "RTClib.h"

#define DHTPIN 25          // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT11     // DHT 11

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 10, 2, 3, 4, 5); //NEED TO CHANGE THE PIN OUT !!!!!!!!!!!

volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;

volatile unsigned char* port_d = (unsigned char*) 0x102; 
volatile unsigned char* ddr_d  = (unsigned char*) 0x101; 
volatile unsigned char* pin_d  = (unsigned char*) 0x100;

// pin 28
  volatile unsigned char* port_a = (unsigned char*) 0x22;
  volatile unsigned char* ddr_a = (unsigned char*) 0x21;
  volatile unsigned char* pin_a  = (unsigned char*) 0x20;

// // pin 30
  volatile unsigned char* port_c = (unsigned char*) 0x28  ;
  volatile unsigned char* ddr_c  = (unsigned char*) 0x27 ;
  volatile unsigned char* pin_c = (unsigned char*) 0x26  ;


// // pin 38
  volatile unsigned char* port_b = (unsigned char*)   0x25;
  volatile unsigned char* ddr_b = (unsigned char*)  0x24;
  volatile unsigned char* pin_b = (unsigned char*)   0x23;


// //pin 39
  volatile unsigned char* port_g = (unsigned char*) 0x34;
  volatile unsigned char* ddr_g = (unsigned char*) 0x33;
  volatile unsigned char* pin_g  = (unsigned char*) 0x32;

// pin A10
  volatile unsigned char* port_k = (unsigned char*) 0x108;
  volatile unsigned char* ddr_k = (unsigned char*) 0x107;
  volatile unsigned char* pin_k  = (unsigned char*) 0x106;

//temperature variable
int templevel = 0;

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

  *ddr_a |= 0b01000000;
  *ddr_c |= 0b10000000;
  *ddr_b |= 0b00001000;
  *ddr_g |= 0b00000100;
  
  //vent speed
  myMotor.setSpeed(200);
  
  //fan motor
  *ddr_d |= 0b00100000; //enable pin 5 as output
  *ddr_d |= 0b00010000; //enable pin 4 as output
  
  //DHT sensor
  dht.begin();
  
  //LCD
  lcd.begin(16,2);

  //Real Time Clock Module
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.clear();

  //pk2 to input for pull up resistor button
  *ddr_k &= 0xEF;
  *port_k |= 0b00000100;
}

void loop (){
  delay(5000);
  if(*pin_k & 0b00000100){
    Serial.println("Disabled - ");                          //RTC timestamps disabled
    telltime();
    lcd.clear();
    *port_d &= ~(0b00110000); //turn off fan

    *port_b |= (0b00001000); //yellow LED on

    *port_a &= (0b10111111); //green LED off
    *port_c &= (0b01111111); //red LED off
    *port_g &= (0b11111011); //blue LED off
  }
  else{
    //Do these Anyways
    waterlevel = watercheck();        //Water Level Monitoring 
    templevel = dhtfunction();        //Humidity and Temperature Displayed
    Vent_control();                 //Change Vent Position if Needed

    if(waterlevel == 1){
      LCDerror();                     //display error
      Serial.println("Error State - ");                               //RTC timestamps error state
      telltime();
      *port_d &= ~(0b00110000);       //turn off fan

      *port_c |= (0b10000000); //red LED on

      *port_a &= (0b10111111); //green LED off
      *port_b &= (0b11110111); //yellow LED off
      *port_g &= (0b11111011); //blue LED off

    }
    else if(waterlevel == 0){
      if(templevel == 1){
      Serial.print("Running - ");                                //RTC timestamps running
      telltime();

      *port_g |= (0b00000100); //blue LED on

      *port_a &= (0b10111111);
      *port_c &= (0b01111111);
      *port_b &= (0b11110111);

      }
      else{
      Serial.print("Idle - ");                                //RTC timestamps idle
      telltime();

      *port_a |= (0b01000000); //green LED on

      *port_c &= (0b01111111);
      *port_b &= (0b11110111);
      *port_g &= (0b11111011);
      }
    }
  }
}

  int dhtfunction(){
    lcd.clear();
    float temp_c = dht.readTemperature();
    float humidity = dht.readHumidity();
    LCDdisplay(temp_c,humidity);
    if(temp_c > 24){
      //turn on fan
      *port_d |= (0b00110000);
      return(1);
    }
    else{
      *port_d &= ~(0b00110000);     //turn off fan
      return(0);
    }
  }

  void LCDdisplay(int temp, int hum){
    lcd.clear();
    lcd.setCursor(0,0);

    lcd.print("Temp:");
    lcd.print(temp);
    lcd.print(char(223));
    lcd.print("C");

    lcd.setCursor(0,1);

    lcd.print("Hum:");
    lcd.print(hum);
    lcd.write("%");
  }

  void LCDerror(){
    lcd.setCursor(11,0);
    lcd.print("WL:");
    lcd.setCursor(11,1);
    lcd.print("ERROR:");
  }

void telltime(){
  DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    if(now.hour() < 10){
      Serial.print("0");
      Serial.print(now.hour(), DEC);
    }
    else{
      Serial.print(now.hour(), DEC);
    }
    if(now.minute() < 10){
      Serial.print(":");
      Serial.print("0");
      Serial.print(now.minute(), DEC);
    }
    else{
      Serial.print(":");
      Serial.print(now.minute(), DEC);
    }
    if(now.second() < 10){
      Serial.print(":");
      Serial.print("0");
      Serial.print(now.second(), DEC);
    }
    else{
      Serial.print(":");
      Serial.print(now.second(), DEC);
    }
  Serial.println();
}

//controls vent stepper motor
void Vent_control(){
  potenVal = map(analogRead(A2),0,1023,0,500);
//turns vent based on potentiometer
  if(potenVal>Pval)
      myMotor.step(5);
  if(potenVal<Pval)
      myMotor.step(-5);
  Pval = potenVal;
} 

void U0init(unsigned int U0baud){
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
//NEED TO INCLUDE UART FUNCTIONS THAT REPLACE SERIAL FUNCTIONS
