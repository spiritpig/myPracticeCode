#include <Windows.h>

#ifndef TIMER
#define TIMER

class newTimer
{
	unsigned int maxTime;
	unsigned int prevTime, curTime;

public:
	newTimer( const unsigned int &mt );
	void setMT( const unsigned int &mt );
	bool isOutOfTime();
	void moveTimer();
};

#endif // TIMER