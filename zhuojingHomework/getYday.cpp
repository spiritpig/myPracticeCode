/*
 * =====================================================================================
 *
 *       Filename:  getYday.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/7 9:02:54
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

int mDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool isRunNian( int year )
{
    return ( year%400 == 0 ) || ( year%4 == 0 && year%100 != 0 );
}

int getYday( int year, int mon, int day )
{
    int wDay = day;
    mon--;

    while( mon > 0 )
    {
        if( mon != 2 )
        {
            wDay += mDays[mon-1];
        }
        else
        {
            if( isRunNian( year ) )
            {
                wDay += 29;
            }
            else
            {
                wDay += mDays[mon-1];
            }
        }

        --mon;
    }

    return wDay;
}

int main(void)
{
    int year, mon, day;
    while( 1 )
    {
        printf( "please enter year, month, day: " );
        scanf( "%d %d %d", &year, &mon, &day );

        printf( "wDay: %d\n",getYday( year, mon, day ) );
    }

    return 0;
}

