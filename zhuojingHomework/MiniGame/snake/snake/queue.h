#ifndef QUEUE
#define QUEUE

#include "stdafx.h"

class MyQueue
{
	Node *front;                        // frontָ�룬���洢ʵ�ʵ�ֵ
	Node *back;                         // backָ�룬�洢ʵ��ֵ

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