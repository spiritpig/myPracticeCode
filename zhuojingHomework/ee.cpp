/*
 * =====================================================================================
 *
 *       Filename:  ee.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/29 9:02:26
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

/*
 *  输出 1-n之间，能被3整除的数
 */
void func( int n )
{
    if( n > 0 )
    {
        func( n-1 );

        if( n%3 == 0 )
        {
            printf( "%d ", n );
        }
    }
}

int main(void)
{
    func( 100 );
    return 0;
}

