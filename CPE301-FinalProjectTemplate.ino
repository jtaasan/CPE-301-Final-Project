//Final Project Template
//Jonathan Taasan, Tara Hartman, Rachel Lykins, Alex Hsueh

//includes (put libraries in here)
#include <Stepper.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#include "RTClib.h"

#define DHTPIN 7          // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT11     // DHT 11

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 10, 2, 3, 4, 5); //NEED TO CHANGE THE PIN OUT !!!!!!!!!!!

volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;

volatile unsigned char* port_e = (unsigned char*) 0x2E; 
volatile unsigned char* ddr_e  = (unsigned char*) 0x2D; 
volatile unsigned char* pin_e  = (unsigned char*) 0x2C;

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
  
  //vent speed
    myMotor.setSpeed(200);
  
  //fan motor
  *ddr_e |= 0b00001000; //FAN MOTOR PIN 5
  *ddr_e |= 0b00000100; //FAN MOTOR PIN 4
  *ddr_e |= 0b00000010; //FAN MOTOR PIN 3
  
  //DHT sensor
  dht.begin();
  
  //LCD
  lcd.begin(16,2);
  
  //Real Time Clock Module
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop (){
  if button pressed, then disable system{
    Serial.println("Disabled - ");                          //RTC timestamps disabled
                                      Yellow LED on
  }
  //else, do either idle, error, or running{
    //Do these Anyways
    waterlevel = watercheck();        //Water Level Monitoring 
    templevel = dhtfunction();        //Humidity and Temperature Displayed
    Vent_control();                   //Change Vent Position if Needed

    if(waterlevel == 1){
      LCDerror();                     //display error
                                      RED LED on
      Serial.println("Error State - ");                               //RTC timestamps error state
      telltime();
      *port_e &= ~(0b00001000);       //turn off fan
    }
    else if(water level == 0){
      if(templevel == 1){
                                      Blue LED on
      Serial.println("Running - ");                                //RTC timestamps running
      telltime();
      }
      else{
                                      Green LED on
      Serial.println("Idle - ");                                //RTC timestamps idle
      telltime();
      }
    }
  }

}

  int dhtfunction(){
    float temp_c = dht.readTemperature();
    float humidity = dht.readHumidity();
    if(temp_c > 24){
      //turn on fan
      *port_e |= ~(0b00000000);
      return(1);
    }
    else{
      //turn off fan
      *port_e &= ~(0b00001000);
      return(0);
    }
    LCDdisplay(temp_c,humidity);
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
    lcd.setCursor(12,1);
    lcd.print("WL:");
    lcd.setCursor(12,2);
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
  potenVal = map(analogRead(A0),0,1023,0,500);
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
