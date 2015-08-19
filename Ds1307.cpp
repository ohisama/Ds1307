#include <Wire.h>
#include "Ds1307.h"

#define _addr 				0x68
Ds1307::Ds1307()
{
	Wire.begin();
}
time_t Ds1307::get()
{
	tmElements_t tm;
	read(tm);
	return(makeTime(tm));
}
void Ds1307::set(time_t t)
{
	tmElements_t tm;
	breakTime(t, tm);
	tm.Second |= 0x80;
	write(tm);
	tm.Second &= 0x7f;
	write(tm);
}
void Ds1307::read(tmElements_t &tm)
{
	Wire.beginTransmission(_addr);
	Wire.write(0x00);
	Wire.endTransmission();
	Wire.requestFrom(_addr, tmNbrFields);
	tm.Second = bcd2dec(Wire.read() & 0x7f);
	tm.Minute = bcd2dec(Wire.read());
	tm.Hour = bcd2dec(Wire.read() & 0x3f);
	tm.Wday = bcd2dec(Wire.read());
	tm.Day = bcd2dec(Wire.read());
	tm.Month = bcd2dec(Wire.read());
	tm.Year = y2kYearToTm((bcd2dec(Wire.read())));
}
void Ds1307::write(tmElements_t &tm)
{
	Wire.beginTransmission(_addr);
	Wire.write(0x00);
	Wire.write(dec2bcd(tm.Second));
	Wire.write(dec2bcd(tm.Minute));
	Wire.write(dec2bcd(tm.Hour));
	Wire.write(dec2bcd(tm.Wday));
	Wire.write(dec2bcd(tm.Day));
	Wire.write(dec2bcd(tm.Month));
	Wire.write(dec2bcd(tmYearToY2k(tm.Year)));
	Wire.endTransmission();
}
uint8_t Ds1307::dec2bcd(uint8_t num)
{
	return ((num / 10 * 16) + (num % 10));
}
uint8_t Ds1307::bcd2dec(uint8_t num)
{
	return ((num / 16 * 10) + (num % 16));
}
//Ds1307 RTC = Ds1307();
