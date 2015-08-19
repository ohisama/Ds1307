#include <Wire.h>
#include <Time.h>
#include "Ds1307.h"

Ds1307 rtc;
void printDigits(int digits)
{
	Serial.print(":");
	if (digits < 10) Serial.print('0');
	Serial.print(digits);
}
void digitalClockDisplay()
{
  Serial.print(year());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(day());
  Serial.print(" ");
	Serial.print(hour());
	printDigits(minute());
	printDigits(second());
	Serial.println();
}
void setup()
{
	pinMode(13, OUTPUT);
	rtc = Ds1307();
	Serial.begin(9600);
	Serial.println("\r\nread rtc ->");
	setSyncProvider(rtc.get);
	if (timeStatus() != timeSet) Serial.println("Unable to sync with the RTC");
	else  Serial.println("RTC has set the system time");
}
void loop()
{
	digitalClockDisplay();
	digitalWrite(13, HIGH);
	delay(3000);
	digitalWrite(13, LOW);
	delay(3000);
}
