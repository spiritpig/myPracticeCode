/*
 * =====================================================================================
 *
 *       Filename:  801.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/1 14:19:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int han( int n, int curN = 0 )
{
    if( n == 0 )
    {
        return 0;
    }

    if( curN == 0 )
    {
        curN = n-1;
    }

    if( n%curN == 0 )
    {
        return curN;
    }
    else
    {
        return han( n, curN-1 );
    }
}

bool isPrime( int n )
{
    int sqrtN = (int)sqrt( n ) + 1;
    for( int i = 2; i <= sqrtN; ++i )
    {
        if( n%i == 0 )
        {
            return false;
        }
    }

    return true;
}

int primeSum( int n )
{
    int sum = 2;
    for( int i = 3; i <= n; ++i )
    {
        if( isPrime( i ) )
        {
            sum += i;
        }
    }

    return sum;
}

int primeSum_recu( int n )
{
    if( isPrime( n ) )
    {
        return n + primeSum_recu( n-1 ) ;
    }

    if( n > 2 )
    {
        return primeSum_recu( n-1 );
    }

    if( n == 2 )
    {
        return 2;
    }
}

// a 对 b取余
float fmodf( float a, float b )
{
    // 异常
    if( b == 0 )
    {
        return -1.0f;
    }

    // 取符号
    int sign = 1;
    if( a < 0.0f )
    {
        sign = -sign; 
        a = -a;
    }
    if( b < 0.0f )
    {
        b = -b;
    }

    // 累减的过程
    while( a > b )
    {
        a -= b;
    }

    return sign * a;
}


// 获取1/10^digit的小数
float getBaseNum( int digit )
{
    if( digit == 0 )
    {
        return 1.0f;
    }

    int num = 10;
    for( int i = 1; i < digit; ++i )
    {
        num *= 10;
    }

    return 1.0f/num;
}

float mySqrt( float n, int digit )
{
    if( n < 0.0f )
    {
        return -1.0f;
    }

    if( n == 1.0f || n == 0.0f )
    {
        return n;
    }
    float halfN = n/2;
    float curNum = 0.0f;
    for( int i = 0; i <= digit; ++i )
    {
        float curBaseNum = getBaseNum( i );
        for( curNum; curNum < halfN; curNum += curBaseNum )
        {
            if( curNum*curNum > n )
            {
                break;
            }
        }

        curNum = curNum - curBaseNum;
    }

    return curNum;
}

int main(void)
{
    float a = 3.3f, b = -1.2f;
//  printf( "%d\n", han( 100 ) );
//  printf( "%d\n", han( 131 ) ); 
//  printf( "%d\n", primeSum( 7 ) );
//  printf( "%d\n", primeSum_recu( 10 ) );
//  printf( "%f / %f = %f \n", a, b, fmodf( a, b ) );
    printf( "%f\n", mySqrt( 101.0f, 5 ) );

    return 0;
}
