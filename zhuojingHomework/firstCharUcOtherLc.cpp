/*
 * =====================================================================================
 *
 *       Filename:  firstCharUcOtherLc.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/24 22:43:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <cstring>
using namespace std;

bool isLowercase( char c )
{
    return ( c >= 'a' && c <= 'z' );
}

bool isUppercase( char c )
{
    return ( c >= 'A' && c <= 'Z' );
}

int checkForChar( char c )
{
    if( isLowercase( c ) )
    {
        return 1;
    }
    if( isUppercase( c ) )
    {
        return 2;
    }

    return 0;
}

void firstCharUcOtherLc_v2( char * str )
{
   int sLen = strlen( str ); 
   bool isFirstChar = true;

   int i = 0;
   // 检测第一个字符是否为小写
   // 小写则转换为大写 
   int res = checkForChar( str[i] );
   while( res <= 0 )
   {
       ++i;
       res = checkForChar( str[i] );
   }

   if( res == 1 )
   {
       str[i] -= 32;
   }

   for( ++i; i < sLen; ++i )
   {
       if( isUppercase( str[i] ) )
       {
           str[i] += 32;
       }
   }
}

void firstCharUcOtherLc( char *str )
{
    int sLen = strlen( str );
    bool isFirstChar = true;
    
    for( int i = 0; i < sLen; ++i )
    {
        if( isUppercase( str[i] ) && 
            !isFirstChar )
        {
            str[i] = str[i] + 32;
            isFirstChar = false;
        }
        else
        if( isLowercase( str[i] ) &&
            isFirstChar  )
        {
            isFirstChar = false;
        }

    }
}

int main(void)
{
    char str[] = "223AsdsdDSDsdsDshHdsd";
    firstCharUcOtherLc_v2( str );

    cout << str << endl;
    return 0;
}
