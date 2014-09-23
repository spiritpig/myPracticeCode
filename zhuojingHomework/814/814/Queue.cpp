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
	// ���front��ָ����Ϊ�գ���֤��
	// ������û��Ԫ�أ�ֱ��ɾ��front��������
	if( pNext == NULL )
	{
		delete front;
		return;
	}
	else
	{
		// ����������Ԫ�أ���ô���ǰ��������ɾ����ʽ
		// ����ɾ��
		Node *pCur = front;
		while( pNext != NULL )
		{
			delete pCur;

			pCur = pNext;
			pNext = pNext->next;
		}
		// ��ɾ��һ��back�ڵ�
		delete back;
	}
}
//---------------------------------------------------------------------------
void MyQueue::push_back( vector2 data )
{
	Node *newNode = new Node;

	// ���½ڵ���Ϊ�����׸�Ԫ��
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

	// ���½ڵ���뵽��β
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

	// ���½ڵ���뵽��ͷ
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

	// ���½ڵ���뵽��ͷ
	newNode->next = front->next;
	front->next = newNode;
	//  �ڲ����һ��Ԫ�ص�ʱ����Ҫ��backָ��ָ�����Ԫ��
	// ��ȷ��backָ��һֱָ�����һ��Ԫ��
	if( isEmpty() )
	{
		back = newNode;
	}
}

void MyQueue::pop_front( vector2 &v )
{
	Node *n = front->next;

	// �������Ľڵ������ȥ��
	if( n != NULL )
	{
		v = n->data;
		front->next = n->next;

		// ����ʣ���һ���ڵ��ʱ��������Ҫ��backָ��ָ��front
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

	// ����������Ԫ�أ���ô���ǰ��������ɾ����ʽ
	// ����ͷ�������Ľڵ�ȫ��ɾ��
	Node *pCur = front->next;
	Node *pNext = pCur->next;
	while( pNext != NULL )
	{
		delete pCur;

		pCur = pNext;
		pNext = pNext->next;
	}
	// ��ɾ��һ��back�ڵ�
	delete back;
	back = front;

}