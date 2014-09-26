/*
 * =====================================================================================
 *
 *       Filename:  strcpy_gpp.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/9/26 9:14:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>

char* myStrcpy( char *strDest, const char *strSrc )
{
    size_t index = 0;
    while( (strDest[index] = strSrc[index]) != '\0' )
    {
        ++index;
    }
    return strDest;
}

int main(void)
{
    char strA[] = "243984932849";
    char strB[100] = "2083t9rogihldknvc,";

    printf( "strB : %s\n", strB );
    myStrcpy( strB, strA );
    printf( "strB : %s\n", strB );

    return 0;
}

