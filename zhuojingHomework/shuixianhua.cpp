/*
 * =====================================================================================
 *
 *       Filename:  shuixianhua.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/31 14:31:52
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

void shuixian()
{
    int ge = 0,shi = 0,bai = 0;
    for( int i = 100; i < 1000; ++i )
    {
        ge = i%10;
        shi = i/10 % 10;
        bai = i/100;

        if( i == ge*ge*ge + shi*shi*shi + bai*bai*bai )
        {
            printf( "%d ", i );
        }
    }
    printf( "\n" );
}

void haveChar( const char *str, char c )
{
    int i = 0;
    while( str[i] != '\0' )
    {
        if( str[i] == c )
        {
            printf( "%s, have %c\n", str, c );
            return;
        }

        ++i;
    }

    printf( "%s, haven't %c\n", str, c );
}



int main(void)
{
    shuixian();
    haveChar( "\"this is a testString we haven't   char!\"", 'X' );

    return 0;
}

