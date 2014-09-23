#ifndef TIMER
#define TIMER

#include <Windows.h>

class newTimer
{
	unsigned int maxTime;
	unsigned int prevTime, curTime;

public:
	newTimer( const unsigned int &mt );
	void setMT( const unsigned int &mt );
	bool isOutOfTime();
};

#endif // TIMER