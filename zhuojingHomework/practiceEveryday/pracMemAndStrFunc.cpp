/*
 * =====================================================================================
 *
 *       Filename:  pracMemAndStrFunc.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/10 17:11:34
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
        char * const pDest = ( char * const )dest;
        const char * const pSrc = ( const char * const )src;

        for( size_t i=0; i<count; ++i )
        {
            pDest[i] = pSrc[i];
        }
    }

    return dest;
}

void* myMemmove( void * const dest, const void * const src, size_t count )
{
    if( dest == src )
    {
        return dest;
    }
    else
    {
        char * const pDest = ( char * const )dest;
        const char * const pSrc = ( const char * const )src;

        if( dest > src )
        {
            for( int i=(int)count-1; i>-1; --i )
            {
                pDest[i] = pSrc[i];
            }
        }
        else
        {
            for( size_t i=0; i < count; ++i )
            {
                pDest[i] = pSrc[i];
            }
        }
    }

    return dest;
}

int myMemcmp( const void * const buf1, const void * const buf2, size_t count )
{
    if( buf1 == buf2 )
    {
        return 0;
    }
    else
    {
        char * const pBuf1 = ( char * const )buf1;
        const char * const pBuf2 = ( const char * const )buf2;

        for( size_t i=0; i<count; ++i  )
        {
            if( pBuf1[i] > pBuf2[i] )
            {
                return 1;
            }
            else
            {
                if( pBuf1[i] < pBuf2[i] )
                {
                    return -1;
                }
            }
        }
    }

    return 0;
}

void* myMemset( void * const dest, size_t count, const int c )
{ 
    char * const pDest = ( char * const )dest;
    for( size_t i=0; i<count; ++i )
    {
        pDest[i] = (char)c;   
    }

    return dest;
}

void outputArray( int *a, int n )
{
    for( size_t i=0; i<n; ++i )
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}

char* myStrcpy( char * const dest, const char * const src )
{
    if( dest == src )
    {
        return dest;
    }
    else
    {
        size_t index = 0;
        while( ( dest[index] = src[index] ) != '\0' )
        {
            ++index;
        }
    }

    return dest;
}

int myStrcmp( const char * const dest, const char * const src )
{
    if( dest == src )
    {
        return 0;
    }
    else
    {
        size_t index = 0;
        while( dest[index] != '\0' ||
               src[index]  != '\0' )
        {
            if( dest[index] > src[index] )
            {
                return 1;
            }
            else
            {
                if( dest[index] < src[index] )
                {
                    return -1;
                }
            }

            ++index;
        }
    }

    return 0;
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

char* myStrcat( char * const dest, const char * const src )
{
    size_t destLen = myStrlen( dest );   
    size_t srcLen = myStrlen( src );
    size_t index = 0;
    for( index; index<srcLen; ++index )
    {
        dest[destLen+index] = src[index];
    }
    dest[destLen+index]='\0';

    return dest;
}

int main(void)
{
/*  
    int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int b[10];

    myMemcpy( b, a, sizeof( int )*10 );
    outputArray( a, 10 );
    outputArray( b, 10 );

    printf( "%d\n", myMemcmp( a, b, sizeof( int )*10 ) );

    myMemmove( a, &a[2], sizeof( int )*8 );
    outputArray( a, 10 );

    myMemmove( &a[2], a, sizeof( int )*8 );
    outputArray( a, 10 );

    myMemset( b, sizeof( int )*10, 0 );
    outputArray( b, 10 );
    */
    char a[100] = "123456789";
    char b[100] = "abcdefghijklmn";

    printf( "%d\n", myStrlen( a ) );
    printf( "%d\n", myStrlen( b ) );

    printf( "%s\n", myStrcat( b, a ) );
    printf( "%s\n", myStrcat( a, &a[2] ) );
    printf( "%s\n", myStrcat( &a[2], a ) );
    printf( "%s\n", a );
    printf( "%d\n", myStrcmp( b, a ) );
    printf( "%s\n", myStrcpy( b, a ) );

    return 0;
}

