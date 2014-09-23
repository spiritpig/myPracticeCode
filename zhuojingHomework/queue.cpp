/*
 * =====================================================================================
 *
 *       Filename:  queue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/24 11:48:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

struct MyQueue
{
    Node *front;                        // front指针，不存储实际的值
    Node *back;                         // back指针，存储实际值

    MyQueue()
    {
        front = new Node;
        front->next = NULL;
        back = front;
    }

    void push( int data )
    {
        Node *newNode = new Node;

        // 将新节点作为队列首个元素
        newNode->data = data;
        newNode->next = NULL;
        cout << "push: " << newNode->data << endl;

        back->next = newNode;
        back = newNode;
    }

    void pop( Node **n )
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

    ~MyQueue()
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
        while( pCur != NULL )
        {
            delete pCur;

            pCur = pNext;
            pNext = pNext->next;
        }
    }
};

int main( void )
{
    MyQueue myQueue;

    myQueue.push( 1 );
    myQueue.push( 2 );
    myQueue.push( 3 );
    myQueue.push( 4 );
    myQueue.push( 5 );
    myQueue.push( 6 );
    myQueue.push( 7 );
    myQueue.push( 8 );
    myQueue.push( 9 );
    myQueue.push( 10 );
    myQueue.push( 11 );
    myQueue.push( 12 );

    Node *n;
    myQueue.pop( &n );
    while( n != NULL )
    {
        cout << n->data << " ";

        delete n;
        myQueue.pop( &n );
    }

    return 0;
}
