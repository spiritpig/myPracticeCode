/*
 * =====================================================================================
 *
 *       Filename:  getPathAndName.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/7 13:50:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* getFilenameFromFullPath( const char * const fullPath )
{
    int pSize = strlen( fullPath ) - 1;
    while( pSize > -1 )
    {
        if( fullPath[pSize] == '\\' ||
            fullPath[pSize] == '/' )
        {
            return ( char * )&fullPath[pSize+1];
        }
        --pSize;
    }

    return NULL;
}

char* getPathFromFullPath( char * const path, const char * const fullPath )
{
    int pSize = strlen( fullPath ) - 1;
    while( pSize > -1 )
    {
        if( fullPath[pSize] == '\\' ||
            fullPath[pSize] == '/' )
        {
            break;
        }
        --pSize;
    }

    int index = 0;
    for( index; index < pSize; ++index )
    {
        path[index] = fullPath[index];
    }
    path[index] = '\0';

    return path;
}

int main(void)
{
    char fullPath1[1024] = "C:/Program Files/Acer/Acer Updater/ALU.exe";
    char fullPath2[1024] = "C:\\Program Files\\Acer\\Acer Updater\\ALU.exe";

    printf( "%s\n", fullPath1 );
    printf( "%s\n", fullPath2 );

    printf( "filename: %s\n", getFilenameFromFullPath( fullPath1 ) );
    printf( "filename: %s\n", getFilenameFromFullPath( fullPath2 ) );

    char path[1024]="\0";
    printf( "path: %s\n", getPathFromFullPath( path, fullPath1 ) );
    printf( "path: %s\n", getPathFromFullPath( path, fullPath2 ) );

    return 0;
}

