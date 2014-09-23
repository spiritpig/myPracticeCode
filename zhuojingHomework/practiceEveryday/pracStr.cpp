/*
 * =====================================================================================
 *
 *       Filename:  pracStr.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/8 16:01:33
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

char* myStrcpy( char * const dest, const char* const src )
{
    if( dest == src )
    {
        return dest;
    }
    
    int index = 0;
    while( ( dest[index] = src[index] ) != '\0' )
    {
        ++index;
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
        int index = 0;
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
            ++index;
        }
    }

    return 0;
}

char* myStrcat( char * const dest, const char * const src )
{
    int destLen = 0;
    while( dest[destLen] != '\0' )
    {
        ++destLen;
    }   

    int index = 0;
    while( src[index] != '\0' )
    {
        dest[destLen + index] = src[index];

        ++index;
    }

    return dest;
}

void* myMemcpy( void * const dest, const void * const src, size_t count )
{
    if( dest == src )
    {
        return dest;
    }

    char * const pDest = ( char * const )dest;
    const char * const pSrc = ( const char * const )src;

    for( size_t i = 0; i < count; ++i )
    {
        pDest[i] = pSrc[i];
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
            for( int i = count-1; i > -1; --i )
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

int myMemcmp( const void * const buf1, const void * const buf2, size_t count )
{
    if( buf1 == buf2 )
    {
        return 0;
    }
    else
    {
        const char * const pBuf1 = ( const char * const )buf1;
        const char * const pBuf2 = ( const char * const )buf2;

        for( int i = 0; i < count; ++i )
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

void* myMemset( void * const dest, int c, size_t count )
{
    char * const pDest = ( char * const )dest;

    for( size_t i = 0; i < count; ++i )
    {
        pDest[i] = (char)c;
    }

    return dest;
}

void outputIntArray( int *a, int n )
{
    for( int i = 0; i < n; ++i )
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void)
{
    char a[100] = "12345678910";
    char b[100] = "abcdefg";
    
    printf("%d\n",myStrcmp(a,b));
    printf("%s\n",myStrcat(b,a));
    printf("%s\n",myStrcpy(a,b));

    int ia[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int ib[10];

    myMemcpy( ib, ia, sizeof(int)*10 );
    outputIntArray( ib, 10 );

    myMemmove( &ia[2], &ia[0], sizeof(int)*10 );
    outputIntArray( ia, 10 );

    printf("%d\n",myMemcmp( ia, ib, sizeof(int)*10 ));
    myMemset( ia, 0, sizeof(int)*10 );

    outputIntArray( ia, 10 );

    return 0;
}

