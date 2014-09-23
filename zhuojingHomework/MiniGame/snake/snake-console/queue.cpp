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

	// ����������Ԫ�أ���ô���ǰ��������ɾ����ʽ
	// ����ɾ��
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

	// ���½ڵ���Ϊ�����׸�Ԫ��
	newNode->data = data;
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
void MyQueue::push_front( point data )
{
	Node *newNode = new Node;

	// ���½ڵ���뵽��ͷ
	newNode->data = data;

	newNode->next = front->next;
	front->next = newNode;
}
//---------------------------------------------------------------------------
void MyQueue::push_front( Node *n )
{
	Node *newNode = n;

	// ���½ڵ���뵽��ͷ
	newNode->next = front->next;
	front->next = newNode;
}

void MyQueue::pop( Node **n )
{
	*n = front->next;

	// �������Ľڵ������ȥ��
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