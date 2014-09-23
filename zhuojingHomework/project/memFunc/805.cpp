/*
 * =====================================================================================
 *
 *       Filename:  805.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/5 19:27:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "stdafx.h"

// 时钟小时位的位置
pos clockPos[12] = {
	{ 4, 1 },
	{ 5, 2 },
	{ 6, 3 },
	{ 5, 4 },
	{ 4, 5 },
	{ 3, 6 },
	{ 2, 5 },
	{ 1, 4 },
	{ 0, 3 },
	{ 1, 2 },
	{ 2, 1 },
	{ 3, 0 },
};


void gotoXY( int x, int y )
{
	COORD pos = { 2*x, y };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
}

void outputClock( int second )
{
	int CLOCK_wIDTH_TIMES = 5;
	for( int i = 0; i < 12; ++i )
	{
		gotoXY( CLOCK_wIDTH_TIMES*clockPos[i].x, 
			CLOCK_wIDTH_TIMES*clockPos[i].y );

		printf( "%d", i+1 );
	}

	// 55-60的情况需要特殊处理一下
	pos sOffset;
	int curClockPos = second/5;
	int preClockPos = second/5-1;
	if( preClockPos < 0 )
	{
		preClockPos = 11;
	}

	// 时钟位直接读取clockPos中的值
	// 否则，计算其坐标
	if( second%5 != 0 )
	{
		sOffset.x = clockPos[curClockPos].x - clockPos[preClockPos].x;
		sOffset.y = clockPos[curClockPos].y - clockPos[preClockPos].y;
		int x = sOffset.x * (second%5) + CLOCK_wIDTH_TIMES*clockPos[preClockPos].x;
		int y = sOffset.y * (second%5) + CLOCK_wIDTH_TIMES*clockPos[preClockPos].y;
		gotoXY( x, y );
	}
	else
	{
		gotoXY( CLOCK_wIDTH_TIMES*clockPos[preClockPos].x,
			CLOCK_wIDTH_TIMES*clockPos[preClockPos].y );
	}

	// 一位数在前面补零
	if( second != 0 )
	{
		printf( "%d",second );
	}
	else
	{
		printf( "00" );
	}
}

void runClock()
{
	time_t t; 
	tm *p; 

	while( 1 )
	{
		time( &t );
		p = localtime( &t );

		Sleep( 200 );
		system( "cls" );

		outputClock( p->tm_sec );
	}
}

size_t myStrlen( const char * const str )
{
    size_t i = 0;
    while( str[i] != '\0' )
    {
        ++i;
    }

    return i;
}

char* myStrcat( char * const dest, const char * const src )
{
    if( dest == NULL || src == NULL )
    {
        return dest;
    }

    if( dest == src )
    {
        return dest;
    }

    size_t destSize = myStrlen( dest );
    size_t i = 0;
    while( src[i] != '\0' )
    {
        dest[i+destSize] = src[i];

        ++i;
    }

    dest[i+destSize] = '\0';

    return dest;
}

char* myStrncat( char * const dest, const char * const src,
                 size_t count )
{
    if( dest == NULL || src == NULL )
    {
        return dest;
    }

    if( dest == src )
    {
        return dest;
    }

    size_t destSize = myStrlen( dest );
    size_t i = 0;
    for( i; i < count; ++i )
    {
        dest[i+destSize] = src[i];
    }
    dest[i+destSize] = '\0';

    return dest;
}

char* myStrchr( const char * const s, int c )
{
    if( s == NULL )
    {
        return (char *)s;
    }

    int i = 0;
    while( s[i] != '\0' )
    {
        if( s[i] == c )
        {
            return ( char * )&s[i];
        }

        ++i;
    }

    return NULL;
}

int myStrcmp( const char *s1, const char *s2 )
{
    // 指针相同，证明这两个字符串相等，
    // 返回0
    if( s1 == s2 )
    {
        return 0;
    }

    int i = 0;
    while( ( s1[i] != '\0') ||
           ( s2[i] != '\0' ) )
    {
        if( s1[i] > s2[i] )
        {
            return 1;
        }
        else
        {
            if( s1[i] < s2[i] )
            {
                return -1;
            }
        }

        ++i;
    }

    return 0;
}

int myStrcmp( const char *s1, const char *s2,
              size_t count )
{
    // 指针相同，证明这两个字符串相等，
    // 返回0
    if( s1 == s2 )
    {
        return 0;
    }

    size_t i = 0;
    for( i; i < count; ++i )
    {
        if( s1[i] > s2[i] )
        {
            return 1;
        }
        else
        {
            if( s1[i] < s2[i] )
            {
                return -1;
            }
        }

        ++i;
    }

    return 0;
}

/*  
char* myStrcpy( char * const dest, const char * const src )
{
    // 若两个指针相同我们何须复制呢
    if( dest == src )
    {
        return dest;
    }

    int i = 0;
    while( src[i] != '\0' )
    {
        dest[i] = src[i];

        ++i;
    }
    dest[i] = '\0';

    return dest;
}
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

    int i = 0;
    while( dest[i]=src[i] )
    {
        ++i;
    }

    return dest;
}

char* myStrncpy( char * const dest, const char * const src,
                 size_t count )
{
    if( dest == NULL || src == NULL )
    {
        return dest;
    }

    if( dest == src )
    {
        return dest;
    }

    size_t i = 0;
    for( i; i < count; ++i )
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return dest;
}

bool isCharinStr( const char * str, const char c )
{
    while( *str != '\0' )
    {
        if( c == *str )
        {
            return true;
        }
        
        ++str;
    }

    return false;
}

size_t myStrcspn( const char * const s, const char * const reject )
{
    int i = 0;
    for( i; s[i] != '\0'; ++i )
    {
        if( isCharinStr( reject, s[i] ) )
        {
            break;
        }
    }

    return i;
}

char* myStrrchr( const char * const s, int c )
{
    int sSize = ( int )myStrlen( s );
    
    int i = sSize - 1;
    for( i; i > -1; --i )
    {
        if( s[i] == c )
        {
            return ( char* )&s[i];
        }
    }

    return NULL;
}

double ceil( const double d )
{
    return (int)d;
}

double floor( const double d )
{
    return (int)d + 1;
}

int main(void)
{
    char d[100] = " jsslkb1rg roeuirjfkwj1k40rklsdjlk2jgfk";
    char s[50] =  "12305678910111";

    myStrcat( d, s );
    printf( "%s\n", d );
    printf( "%s\n", s );

    printf( "%s\n", myStrchr( d, '0' ) );
    printf( "%s\n", myStrchr( d, '0' ) );
    printf( "%s\n", myStrcpy( d, s ) );
    printf( "%u\n", myStrcspn( d, s ) );
    printf( "%s\n", myStrrchr( d, 's' ) );

    printf("%f\n", ceil( 100.53 ));
    printf("%f\n", floor( 100.53 ));

	printf( "\ndispaly clock!" );
	system( "pause" );

	runClock();

    return 0;
}

