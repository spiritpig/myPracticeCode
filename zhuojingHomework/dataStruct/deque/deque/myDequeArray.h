#ifndef MY_DEQUE_ARRAY_AFX
#define MY_DEQUE_ARRAY_AFX

template<typename T, int maxsize>
class myDequeArray
{
public:
	myDequeArray(void);
	~myDequeArray(void);

	bool isFull();
	bool isEmpty();
	bool push( const T &data );
	bool pop( T &data );
	bool pop();

	T &First();
	void setEmpty();

private:
	T m_Data[maxsize];
	int m_Back;
};

template<typename T, int maxsize>
myDequeArray<T, maxsize>::myDequeArray( void )
: m_Back(-1)
{
}

template<typename T, int maxsize>
myDequeArray<T, maxsize>::~myDequeArray( void )
{
	m_Back = -1;
}

template<typename T, int maxsize>
bool myDequeArray<T, maxsize>::isFull()
{
	return (m_Back >= maxsize-1);
}

template<typename T, int maxsize>
bool myDequeArray<T, maxsize>::isEmpty()
{
	return (m_Back <= -1);
}

template<typename T, int maxsize>
bool myDequeArray<T, maxsize>::push( const T &data )
{
	if ( isFull() )
	{
		return false;
	}
	else
	{
		++m_Back;
		for ( int i=m_Back; i>0; --i )
		{
			m_Data[i] = m_Data[i-1];
		}
		m_Data[0] = data;

		return true;
	}
}

template<typename T, int maxsize>
bool myDequeArray<T, maxsize>::pop( T &data )
{
	if ( isEmpty() )
	{
		return false;
	}
	else
	{
		data = m_Data[m_Back--];
		return true;
	}
}

template<typename T, int maxsize>
bool myDequeArray<T, maxsize>::pop()
{
	if ( isEmpty() )
	{
		return false;
	}
	else
	{
		--m_Back;
		return true;
	}	
}

template<typename T, int maxsize>
T & myDequeArray<T, maxsize>::First()
{
	return m_Data[m_Back];
}

template<typename T, int maxsize>
void myDequeArray<T, maxsize>::setEmpty()
{
	m_Back = -1;
}

#endif	// END MY_DEQUE_ARRAY_AFX