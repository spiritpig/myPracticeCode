#ifndef AFX_STACKARRAY
#define AFX_STACKARRAY

template<class T,int maxsize>
class StackArray
{
public:
	StackArray();
	bool StackFull();
	bool Empty();
	bool Push(T const &data);
	bool Pop_Front();
	bool Pop();
	bool Pop(T &data);
	T& GetTop();
	bool GetTop(T &data);
	void SetEmpty();
	T& operator[](int sit);
	bool Delete(T const &data);
	int Size();
	~StackArray();
private:
	T m_data[maxsize];
	int m_top;
};

template<class T,int maxsize>
bool StackArray<T, maxsize>::Pop_Front()
{
	if(Empty())
	{
		return false;
	}

	for (int i=0;i<m_top;++i)
	{
		m_data[i]=m_data[i+1];
	}
	--m_top;
	return true;
}

template<class T,int maxsize>
bool StackArray<T, maxsize>::Delete( T const &data )
{
	int sit=-1;

	for (int i=0;i<=m_top;++i)
	{
		if(m_data[i]==data)
		{
			sit=i;
			break;
		}
	}

	if(sit>-1)
	{
		for (int i=sit;i<m_top;++i)
		{
			m_data[i]=m_data[i+1];
		}
		--m_top;
		return true;
	}
	else
	{
		return false;
	}
}

template<class T,int maxsize>
int StackArray<T, maxsize>::Size()
{
	return m_top+1;
}

template<class T,int maxsize>
T& StackArray<T, maxsize>::operator[]( int sit )
{
	return m_data[sit];
}

template<class T,int maxsize>
void StackArray<T, maxsize>::SetEmpty()
{
	m_top=-1;
}

template<class T,int maxsize>
bool StackArray<T, maxsize>::GetTop( T &data )
{
	if(Empty())
	{
		return false;
	}
	else
	{
		data=m_data[m_top];
		return true;
	}
}

template<class T,int maxsize>
T& StackArray<T, maxsize>::GetTop()
{
	return m_data[m_top];
}

template<class T,int maxsize>
bool StackArray<T, maxsize>::Pop( T &data )
{
	if(Empty())
	{
		return false;
	}
	else
	{
		data=m_data[m_top];
		--m_top;
		return true;
	}
}

template<class T,int maxsize>
bool StackArray<T, maxsize>::Pop()
{
	if(Empty())
	{
		return false;
	}
	else
	{
		--m_top;
		return true;
	}
}

template<class T,int maxsize>
bool StackArray<T, maxsize>::Push( T const &data )
{
	if(StackFull())
	{
		return false;
	}
	else
	{
		++m_top;
		m_data[m_top]=data;
		return true;
	}
}

template<class T,int maxsize>
bool StackArray<T, maxsize>::Empty()
{
	return m_top<=-1;
}

template<class T,int maxsize>
bool StackArray<T, maxsize>::StackFull()
{
	return m_top>=maxsize-1;
}

template<class T,int maxsize>
StackArray<T, maxsize>::~StackArray()
{
	m_top=-1;
}

template<class T,int maxsize>
StackArray<T, maxsize>::StackArray()
{
	m_top=-1;
}

#endif