#include "timer.h"

timer::timer( const unsigned int &mt )
{
	prevTime = GetTickCount();
	curTime = prevTime;
	maxTime = mt;
}


bool timer::isTimeToDoSomething()
{
	curTime = GetTickCount();

	if( ( curTime - prevTime ) > maxTime )
	{
		prevTime = curTime;
		return true;
	}
	return false;
}
