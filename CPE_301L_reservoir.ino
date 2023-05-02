// include the library code: 
#include <LiquidCrystal.h>
//initialise the library with the numbers of the interface pins 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

int resval = 0;  // holds the value
int respin = A5; // sensor pin used
int ledPinRed = 13;  // red LED pin
int buttonPin = 2; // button pin
int buttonState = 0; // variable for reading the button status
  
void setup() { 
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  pinMode(resval, INPUT);
  pinMode(ledPinRed, OUTPUT); 
} 
  
void loop() { 
  // set the cursor to column 0, line 2 
  lcd.setCursor(0, 2);   
  resval = analogRead(respin); //Read data from analog pin and store it to resval variable 
  if (resval<=100){ 
    lcd.println("Water level is too low");
    digitalWrite(ledPinRed, HIGH);
    digitalWrite(ledPinBlue, LOW);
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinYellow, LOW);
    *port_e &= ~(0b00001000); //set pin 5 to LOW
    *port_e &= ~(0b00000100); //set pin 4 to LOW
    *port_e &= ~(0b00000010); //set pin 3 to LOW
  }
  //Get the system back to idle. Temperature and humidity detection do not cease
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && resval > 100) {
    digitalWrite(ledPinGreen, HIGH);
  }  
  delay(1000); 
}