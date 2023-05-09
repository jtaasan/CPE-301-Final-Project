#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#define DHTPIN 7          // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 10, 2, 3, 4, 5);

 volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
 volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
 volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
 volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;

void setup() {
  U0init(9600);
  // Initialize device.
  dht.begin();
  lcd.begin(16,2);
}

void loop() {
  // Delay between measurements.
  delay(5000);
  // Get temperature event and print its value.
  float temp_c = dht.readTemperature();
  float humidity = dht.readHumidity();

  LCDdisplay(temp_c,humidity);
}

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


void LCDdisplay(int temp, int hum)
{
  lcd.clear();
  lcd.setCursor(0,0);

  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(char(223));
  lcd.print("C");

  lcd.setCursor(0,1);

  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.write("% ");
}
