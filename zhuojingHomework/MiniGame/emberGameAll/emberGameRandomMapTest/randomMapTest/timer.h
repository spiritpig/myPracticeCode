/*
 *  说明： timer类， 一个计时器
 *
 *  日期： 2014.7.21
 *  作者： pinkbeen
 */
#ifndef TIMER
#define TIMER

#include "commonHeader.h"

class timer
{
	unsigned int maxTime;
	unsigned int prevTime, curTime;

public:

	/**
	 *	  构造函数
     *
     *	  参数
     *          mt  时间最大值 
	 */
	timer( const unsigned int &mt );

	/**
	 *	  检测是否逝去时间达到了maxTime
     *
     *	  返回值
     *	    达到了maxTime，返回true
     *	    否则返回 false
     *
	 */
	bool isTimeToDoSomething();
};

#endif // TIMER
