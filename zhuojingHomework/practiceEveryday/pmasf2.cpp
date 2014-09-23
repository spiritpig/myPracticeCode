/*
 * =====================================================================================
 *
 *       Filename:  pmasf2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/11 12:18:54
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

void* myMemcpy( void * const dest, const void * const src, size_t count )
{
    if( dest == src )
    {
        return dest;
    }
    else
    {
        char  * const pDest = (char * const)dest;
        const char * const pSrc = (const char * const)src;

        for( size_t index = 0; index < count; ++index )
        {
            pDest[index] = pSrc[index];
        }
    }

    return dest;
}

int myMemcmp( const void * const dest,  const void * const src, size_t count )
{
    if( dest == src )
    {
        return 0;
    }
    else
    {
        char  * const pDest = (char * const)dest;
        const char * const pSrc = (const char * const)src;

        for( size_t index = 0; index < count; ++index )
        {
            if( pDest[index] > pSrc[index] )
            {
                return 1;
            }
            else
            {
                if( pDest[index] < pSrc[index] )
                {
                    return -1;
                }
            }
        }
    }

    return 0;
}

void* myMemmove( void * const dest, const void * const src, size_t count )
{
    if( dest == src )
    {
        return dest;
    }
    else
    {
        char  * const pDest = (char * const)dest;
        const char * const pSrc = (const char * const)src;

        if( dest > src )
        {
            for( int i = (int)count-1; i > -1; --i )
            {
                pDest[i] = pSrc[i];
            }
        }
        else
        {
            for( size_t i = 0; i < count; ++i )
            {
                pDest[i] = pSrc[i];
            }
        }
    }

    return dest;
}

void* myMemset( void * const dest, int c, size_t count )
{
    char  * const pDest = (char * const)dest;

    for( size_t i = 0; i < count; ++i )
    {
        pDest[i] = (char)c;
    }

    return dest;
}

void outputArray( int *a, size_t n )
{
    for( size_t i = 0; i < n; ++i )
    {
        printf("%d ", a[i]);
    }
    printf( "\n" );
}

size_t myStrlen( const char * const str )
{
    size_t index = 0;
    while( str[index] != '\0' )
    {
        ++index;
    }

    return index;
}

char* myStrcpy( char * const dest, const char * const src )
{
    if( dest == src )
    {
        return dest;
    }
    else
    {
        if( dest > src )
        {
            size_t srcLen = myStrlen( src );
            for( int i = (int)srcLen; i > -1; --i )
            {
                dest[i] = src[i];
            }
        }
        else
        {
            size_t i = 0;
            while( src[i] != '\0' )
            {
                dest[i] = src[i];

                ++i;
            }
        }
    }

    return dest;
}

char* myStrcat( char * const dest, const char * const src )
{
    size_t destLen = myStrlen( dest );
    size_t i = 0;
    while( ( dest[destLen+i] = src[i] ) != '\0' )
    {
        ++i;
    }

    return dest;
}

int myStrcmp( const char * const str1, const char * const str2 )
{
    if( str1 == str2 )
    {
        return 0;
    }
    else
    {
        size_t index = 0;
        while( str1[index] != '\0' ||
               str2[index] != '\0' )
        {
            if( str1[index] > str2[index] )
            {
                return 1;
            }
            else
            {
                if( str1[index] < str2[index] )
                {
                    return -1;
                }
            }
        }
    }
}

int main(void)
{
    int c[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int d[10];

    myMemcpy( d, c, sizeof( int )*10 );
    outputArray( c, 10 );
    outputArray( d, 10 );

    printf( "%d\n", myMemcmp( c, d, sizeof( int )*10 ) );

    myMemmove( c, &c[2], sizeof( int )*8 );
    outputArray( c, 10 );

    myMemmove( &c[2], c, sizeof( int )*8 );
    outputArray( c, 10 );

    myMemset( d, 0, sizeof( int )*10 );
    outputArray( d, 10 );
  
    char a[100] = "123456789";
    char b[100] = "abcdefghijklmn";

    printf( "%d\n", myStrlen( a ) );
    printf( "%d\n", myStrlen( b ) );

    printf( "%s\n", myStrcat( b, a ) );
    //printf( "%s\n", myStrcat( a, &a[2] ) );
    //printf( "%s\n", myStrcat( &a[2], a ) );
    printf( "%s\n", a );
    printf( "%d\n", myStrcmp( b, a ) );
    printf( "%s\n", myStrcpy( b, a ) );
    printf( "%s\n", myStrmove( a, &a[3] ) );
    printf( "%s\n", myStrmove( &a[4], a ) );
    printf( "%s\n", a );


    return 0;
}
