/*
 * =====================================================================================
 *
 *       Filename:  728.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/28 10:40:39
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

void func( int n, int s = 7 )
{
    if( s%7 == 0 )
    {
        printf( "%d\n", s );
    }

    ++s;
    if( s <= n )
    {
        func( n, s );
    }
}

void func_v2( int n, int times = 1 )
{
    printf( "%d\n", times*7 );

    ++times;
    if( times*7 < n )
    {
        func_v2( n, times );
    }
}

void decToBin( int n )
{
    if( n > 0 )
    {
        decToBin( n/2 );
        printf( "%d", n%2 );
    }
}

int main(void)
{
    func_v2( 100 );
    decToBin( 100 );

    return 0;
}

