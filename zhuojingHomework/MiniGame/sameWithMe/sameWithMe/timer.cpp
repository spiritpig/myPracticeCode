#include "timer.h"

newTimer::newTimer( const unsigned int &mt )
{
	prevTime = GetTickCount();
	curTime = prevTime;
	maxTime = mt;
}


bool newTimer::isOutOfTime()
{
	curTime = GetTickCount();

	if( ( curTime - prevTime ) > maxTime )
	{
		prevTime = curTime;
		return true;
	}
	return false;
}


void newTimer::setMT( const unsigned int &mt )
{
	maxTime = mt;
}