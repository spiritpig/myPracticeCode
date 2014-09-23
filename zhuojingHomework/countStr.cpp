/*
 * =====================================================================================
 *
 *       Filename:  countStr.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/31 10:19:55
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

#define SIZE 1024

int countCharNum( const char *str, char c )
{
    int i = 0, count = 0;
    while( str[i] != '\0' )
    {
        if( str[i] == c )
        {
            ++count;
        }

        ++i;
    }

    return count;
}

int main(void)
{
    char str[ SIZE ] = "sajdklasjfklvcxnlkuetiuwyhgkdns,djfwikywredjhf"
                       "szxnm,asheu2jwfgb xcqowjkbnm,qnsafkjbvnkjashfc";

    char c = ' ';
    printf( "请输入一个字符:" );
    scanf( "%c", &c );

    printf( "%c in %s is \n\t%d\n", c, str, countCharNum( str, c ) );

    return 0;
}

