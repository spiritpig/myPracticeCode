/*
 * =====================================================================================
 *
 *       Filename:  linkedlist.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/12 9:29:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct linkedlist
{
    int data;
    linkedlist *next;
};

linkedlist* createEmptyList()
{
    linkedlist *head = new linkedlist;
    head->data = 0;
    head->next = NULL;

    return head;
}

void addElement( linkedlist *head, int data )
{
    if( head == NULL )
    {
        return;
    }

    while( head->next != NULL )
    {
        head = head->next;
    }

    linkedlist *node = new linkedlist;
    node->data = data;

    node->next = NULL;
    head->next = node;
}

void removeElement( linkedlist *head, int data )
{
    if( head == NULL )
    {
        return;
    }

    linkedlist *cur = head, *prev = head;
    while( cur != NULL )
    {
        if( cur->data == data )
        {
            prev->next = cur->next;

            delete cur;
            cur = NULL;
            return;
        }

        prev = cur;
        cur = cur->next;
    }
}

void outputList( linkedlist *head )
{
    if( head == NULL )
    {
        return;
    }
    else
    {
        head = head->next;
        while( head != NULL )
        {
            printf( "%d ", head->data );
            head = head->next;
        }
        printf( "\n" );
    }
}

void destoryList( linkedlist **head )
{
    if( head == NULL )
    {
        return;
    }

    linkedlist *cur = (*head)->next, *prev = *head;
    while( cur != NULL )
    {
        delete prev;

        prev = cur;
        cur = cur->next;
    }
    *head = NULL;
}

int main(void)
{
    linkedlist *head = createEmptyList();

    addElement( head, 5 );
    addElement( head, 6 );
    addElement( head, 8 );
    outputList( head );

    removeElement( head, 5 );
    removeElement( head, 8 );
    removeElement( head, 6 );
    outputList( head );

    destoryList( &head );
    outputList( head );

    return 0;
}

