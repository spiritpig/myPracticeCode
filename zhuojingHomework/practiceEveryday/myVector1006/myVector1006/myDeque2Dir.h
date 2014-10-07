#ifndef MYDEQUE2DIR
#define MYDEQUE2DIR

template<class T>
class myDeque2Dir
{
	myDeque2Dir();
private:
	T *m_pLeftData;
	T *m_pRightData;
	size_t m_LeftSize;
	size_t m_RightSize;
	size_t m_LeftCapacity;
	size_t m_RightCapacity;
};

#endif	// END MYDEQUE2DIR