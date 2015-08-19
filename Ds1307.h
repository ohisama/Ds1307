#ifndef Ds1307_h
#define Ds1307_h
#include "Time.h"

class Ds1307
{
public:
	Ds1307();
	static time_t get();
	static void set(time_t t);
	static void read(tmElements_t &tm);
	static void write(tmElements_t &tm);
private:
	static uint8_t dec2bcd(uint8_t num);
	static uint8_t bcd2dec(uint8_t num);
};
//extern Ds1307 RTC;
#endif

