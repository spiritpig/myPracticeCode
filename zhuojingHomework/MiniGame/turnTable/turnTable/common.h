/*
 * 日常练习 通用函数
 *
 */
#include "stdafx.h"

#ifndef COMMON
#define COMMON

using std::cout;
using std::vector;

#define AS( a ) sizeof( a )/sizeof( a[0] )

template<typename T>
void outputArray( vector<T> &a, char separator )
{
    for( int i = 0; i < a.size(); ++i )
    {
        cout << a[i] << separator;
    }
}

void outputArray( int a[], int n, char seperator );
void outputArray( int a[], int left, int right );
// 输入数组的下标范围，左闭右开区间：[ left, right )
int partition( int a[], int left, int right );
// 输入数组的下标范围，左闭右开区间：[ left, right )
void quickSort( int a[], int left, int right );

// 请注意使用srand播撒种子，再使用random函数
int random( int min, int max );
void outputHeader( char *name );

#endif // COMMON end
