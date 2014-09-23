#include "stdafx.h"

#ifndef QUEUE
#define QUEUE

struct Node
{
	vector2 data;
	Node *next;
};

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
	void push_back( vector2 data );
	void push_back( Node *n );

	void push_front( vector2 data );
	void push_front( Node *n );
	void pop_front( vector2 &v );

	void clearQueue();

	bool isEmpty();
};

#endif // QUEUE end