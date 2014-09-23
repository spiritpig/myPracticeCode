#ifndef QUEUE
#define QUEUE

#include "stdafx.h"

class MyQueue
{
	Node *front;                        // front指针，不存储实际的值
	Node *back;                         // back指针，存储实际值

public:
	MyQueue();
	~MyQueue();

	const Node * getHead()
	{
		return front;
	}
	void push_back( point data );
	void push_back( Node *n );

	void push_front( point data );
	void push_front( Node *n );
	void pop( Node **n );
};

#endif // QUEUE end