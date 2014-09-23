#ifndef TIMER
#define TIMER

#include "commonHeader.h"

class timer
{
	unsigned int maxTime;
	unsigned int prevTime, curTime;

public:
	timer( const unsigned int &mt );
	bool isTimeToDoSomething();
};

#endif // TIMER