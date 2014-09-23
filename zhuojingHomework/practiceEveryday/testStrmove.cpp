/*
 * =====================================================================================
 *
 *       Filename:  testCPY.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/8 9:04:44
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
 * 这种处理内存重叠的strcpy，在src<dest时，
 * 只能应付src与dest相隔了1个字符的情况。
 */
char* myStrcpy( char * const dest, const char * const src )
{
    if( dest == NULL || src == NULL )
    {
        return dest;
    }

    if( dest == src )
    {
        return dest;
    }
    else
    {
        if( dest < src )
        {
            int i = 0;
            while( dest[i]=src[i] )
            {
                ++i;
            }
        }
        else
        {
            char curChar, prevChar;
            int i = 0;
            do
            {
                if( i )
                {
                    prevChar = curChar;
                    curChar = src[i];
                    dest[i-1]=prevChar;
                }
                else
                {
                    curChar = src[i];
                }

                ++i;
            }while( curChar != '\0' );

            dest[i-1]=curChar;
        }
    }

    return dest;
}


int main(void)
{
    char a[100] = "abcdefg123456789";
    char b[100] = "a23456789";

    myStrcpy( &a[3], a );
    printf("%s\n", a);

    return 0;
}

