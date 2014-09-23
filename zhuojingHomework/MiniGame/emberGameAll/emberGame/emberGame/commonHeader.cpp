/*
 * =====================================================================================
 *
 *       Filename:  commmmonHeader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/17 10:08:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "commonHeader.h"

void output2DArray( char **a, int h, int w )
{
    for( int i = 0; i < h; ++i )
    {
        for( int j = 0; j < w; ++j )
        {
            cout << a[i][j];
        }
        cout << endl;
    }
}