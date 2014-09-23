#include "newTimer.h"
#include <cstdio>

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
		moveTimer();
		return true;
	}
	return false;
}

void newTimer::moveTimer()
{
//	printf( "prevTime = %d, curTime = %d\n",prevTime, curTime );
	prevTime = GetTickCount();
}

void newTimer::setMT( const unsigned int &mt )
{
	maxTime = mt;
}