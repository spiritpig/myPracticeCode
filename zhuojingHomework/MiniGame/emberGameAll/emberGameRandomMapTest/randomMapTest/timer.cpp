/*
 *  说明： timer类的实现文件
 *
 *  日期： 2014.7.21
 *  作者： pinkbeen
 */
#include "commonHeader.h"

//---------------------------------------------------------------------------
timer::timer( const unsigned int &mt )
{
	prevTime = GetTickCount();
	curTime = prevTime;
	maxTime = mt;
}
//---------------------------------------------------------------------------
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
