#include "RTClib.h"

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  Serial.begin(9600);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () {
    telltime();
    delay(1000);
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