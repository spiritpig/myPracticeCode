#include "stdafx.h"

MyQueue::MyQueue()
{
	front = new Node;
	front->next = NULL;
	back = front;
}
//---------------------------------------------------------------------------
MyQueue::~MyQueue()
{
	Node *pNext = front->next;
	// 如果front的指针域为空，则证明
	// 队列中没有元素，直接删除front，并返回
	if( pNext == NULL )
	{
		delete front;
		return;
	}
	else
	{
		// 若队列中有元素，那么我们按照链表的删除方式
		// 将其删除
		Node *pCur = front;
		while( pNext != NULL )
		{
			delete pCur;

			pCur = pNext;
			pNext = pNext->next;
		}
		// 少删除一个back节点
		delete back;
	}
}
//---------------------------------------------------------------------------
void MyQueue::push_back( vector2 data )
{
	Node *newNode = new Node;

	// 将新节点作为队列首个元素
	newNode->data.x = data.x;
	newNode->data.y = data.y;
	newNode->next = NULL;

	back->next = newNode;
	back = newNode;
}
//---------------------------------------------------------------------------
void MyQueue::push_back( Node *n )
{
	Node *newNode = n;

	// 将新节点插入到队尾
	newNode->next = NULL;

	back->next = newNode;
	back = newNode;
}
//---------------------------------------------------------------------------
void MyQueue::push_front( vector2 data )
{
	Node *newNode = new Node;
	newNode->data.x = data.x;
	newNode->data.y = data.y;

	// 将新节点插入到队头
	newNode->next = front->next;
	front->next = newNode;
	if( isEmpty() )
	{
		back = newNode;
	}
}
//---------------------------------------------------------------------------
void MyQueue::push_front( Node *n )
{
	Node *newNode = n;

	// 将新节点插入到队头
	newNode->next = front->next;
	front->next = newNode;
	//  在插入第一个元素的时候，需要将back指针指向这个元素
	// 以确保back指针一直指向最后一个元素
	if( isEmpty() )
	{
		back = newNode;
	}
}

void MyQueue::pop_front( vector2 &v )
{
	Node *n = front->next;

	// 将弹出的节点从链中去除
	if( n != NULL )
	{
		v = n->data;
		front->next = n->next;

		// 当仅剩最后一个节点的时候，我们需要将back指针指向front
		if( n->next == NULL )
		{
			back = front;
		}
		n->next = NULL;
	}
	else
	{
		front->next = NULL;
	}
}

bool MyQueue::isEmpty()
{
	return (front == back);
}

void MyQueue::clearQueue()
{
	if( isEmpty() )
	{
		return;
	}

	// 若队列中有元素，那么我们按照链表的删除方式
	// 将出头结点以外的节点全部删除
	Node *pCur = front->next;
	Node *pNext = pCur->next;
	while( pNext != NULL )
	{
		delete pCur;

		pCur = pNext;
		pNext = pNext->next;
	}
	// 少删除一个back节点
	delete back;
	back = front;

}