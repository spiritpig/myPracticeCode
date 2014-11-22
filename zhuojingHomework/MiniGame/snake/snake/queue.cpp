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

	// 若队列中有元素，那么我们按照链表的删除方式
	// 将其删除
	Node *pCur = front;
	while( pNext != NULL )
	{
		delete pCur;

		pCur = pNext;
		pNext = pNext->next;
	}
}
//---------------------------------------------------------------------------
void MyQueue::push_back( point data )
{
	Node *newNode = new Node;

	// 将新节点作为队列首个元素
	newNode->data = data;
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
void MyQueue::push_front( point data )
{
	Node *newNode = new Node;

	// 将新节点插入到队头
	newNode->data = data;

	newNode->next = front->next;
	front->next = newNode;
}
//---------------------------------------------------------------------------
void MyQueue::push_front( Node *n )
{
	Node *newNode = n;

	// 将新节点插入到队头
	newNode->next = front->next;
	front->next = newNode;
}

void MyQueue::pop( Node **n )
{
	*n = front->next;

	// 将弹出的节点从链中去除
	if( *n != NULL )
	{
		front->next = (*n)->next;
		(*n)->next = NULL;
	}
	else
	{
		front->next = NULL;
	}
}