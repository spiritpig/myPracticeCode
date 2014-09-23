/*
 * =====================================================================================
 *
 *       Filename:  strtok.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/7 19:14:48
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

bool isCharinStr( const char c, const char * const seperators )
{
    int index = 0;
    while( seperators[index] != '\0' )
    {
        if( seperators[index] == c )
        {
            return true;
        }
        ++index;
    }

    return false;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  mystrtok
 *  Description:  字符串切分函数
 *                  将字符串按照seperators字符串中的字符切分成若干块
 *                  第一次调用时，第一个参数传str字符串的首地址
 *                  随后的调用， 第一个参数则传NULL
 * =====================================================================================
 */
char* mystrtok( char * str, const char * const seperators )
{
    static char *lastPos = str;
    char *curTok = NULL;

    if( lastPos == NULL )
    {
        return NULL;
    }

    // 根据情况，选择变量的赋值方式，
    // 第一次进入的时候，我们将str字符串的首地址
    // 赋给curTok，而第二次以后，由于我们规定str
    // 需要传NULL，所以str的值，由lastPos这个变量
    // 定义，同时当前切分块的首部，就是lastPos变量
    // 指向的地址
    if( str == NULL )
    {
        str = lastPos;
        curTok = lastPos;
    }
    else
    {
        curTok = str;
    }

    // 虽然第一次调用和后面的调用对于str的处理方式有些不同
    // 但是，判断是否为分隔符的方法是一样的
    while( *str != '\0' )
    {
        if( isCharinStr( *str, seperators ) )
        {
            break;
        }
        ++str;
    }

    // 当运行到了字符串的末尾时，lastPos需要值为NUll
    // 这样下一次进入函数的时候，就可以终止这一轮切分的过程了。
    // 未运行到字符串的末尾时，我们将分隔符变为‘\0’
    // 同时lastPos变量移动到下一个切分块的首部
    if( *str == '\0' )
    {
        lastPos = NULL;
    }
    else
    {
        *str = '\0';

        ++str;
        lastPos = str;
    }

    return curTok;
}

// 低效版本
//char* mystrtok( char * str, const char * const seperators )
//{
//    static char *lastPos = str;
//    char *curTok = NULL;
//
//    if( str != NULL )
//    {
//        int index = 0;
//        while( str[index] != '\0' )
//        {
//            if( isCharinStr( str[index], seperators ) ) 
//            {
//                str[index] = '\0';
//
//                // 储存一下这一次运行到的位置
//                lastPos = ( char * )&str[index+1];
//                curTok = str;
//
//                break;
//            }
//            ++index;
//        }
//    }
//    else
//    {
//        if( !lastPos )
//        {
//            return NULL;
//        }
//
//        curTok = lastPos;
//        char *curStr = lastPos;
//        while( *curStr != '\0' )
//        {
//            if( isCharinStr( *curStr, seperators ) ) 
//            {
//                break;
//            }
//            ++curStr;
//        }
//        
//        if( *curStr != '\0' )
//        {
//            *curStr = '\0';
//
//            ++curStr;
//            lastPos = curStr;
//        }
//        else
//        {
//            lastPos = NULL;
//        }
//    }
//
//    return curTok;
//}

int main(void)
{
    char str[20] = "dir \\s \\w \\d \\?";
    char * p = mystrtok( str, " " );
    while( p != NULL )
    {
        printf( "%s\n", p );

        p = mystrtok( NULL, " " );
    }
    return 0;
}

