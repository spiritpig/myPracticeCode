/*
 * =====================================================================================
 *
 *       Filename:  bubbleSort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/4 15:53:16
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
#include <Windows.h>

void bubbleSort( int *a, int n )
{
    bool isSwaped = true;
    for( int i = 0; i < n - 1 && isSwaped; ++i )
    {
        isSwaped = false;
        for( int j = 0; j < n - 1 - i; ++j )
        {
            if( a[j] > a[j+1] )
            {
                int t = a[j];
                a[j]  = a[j+1];
                a[j+1] = t;

                isSwaped = true;
            }
        }
    }
}

int main(void)
{
    int a[65536];

    for( int i = 0; i < 65536; ++i )
    {
        a[i] = rand();
    }

    float t = GetTickCount()/1000.0f;
    bubbleSort( a, 65536 );
    printf( "%f\n", GetTickCount()/1000.0f - t );

    return 0;
}

