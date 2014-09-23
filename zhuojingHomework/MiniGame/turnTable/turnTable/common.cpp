/*
 * =====================================================================================
 *
 *       Filename:  common.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/8 23:06:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "stdafx.h"
using std::endl;

void outputArray( int a[], int n, char seperator )
{
    for( int i = 0; i < n; ++i )
    {
        cout << a[i] << seperator;
    }
    cout << endl;
}

void outputArray( int a[], int left, int right )
{
    for( int i = left; i < right; ++i )
        cout << a[i] << " ";

    cout << endl;
}


/* 
 * ===  Algorithm  ======================================================================
 *         Name:  quickSort
 * =====================================================================================
 */
// [ left, right )
int partition( int a[], int left, int right )
{
    int key = right - 1;
    int i = -1;
    for( int j = left; j < key; ++j )
    {
        if( a[j] > a[key]  )
        {
            ++i;
            std::swap( a[j], a[i] );
        }
    }
    std::swap( a[++i], a[key] );

    return i;
}

// [ left, right )
void quickSort( int a[], int left, int right )
{
    if( left < right - 1 )
    {
        int q = partition( a, left, right );
        quickSort( a, left, q );
        quickSort( a, q+1, right );
    }
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  random
 *  Description:  generate random number
 * =====================================================================================
 */
int random( int min, int max )
{
    if( max < min )
        return min;
    return rand()%( max - min + 1 ) + min;
}

void outputHeader( char *name )
{
	printf( " -----------------------------------------------------------------------------\n" );
	printf( "!                                                                   \n" );
	printf( "!                           %s                        \n",name );
	printf( "!                                                                   \n" );
	printf( " -----------------------------------------------------------------------------\n" );
}
