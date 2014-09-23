/*
 * =====================================================================================
 *
 *       Filename:  homework3.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/18 21:28:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "../common.h"
using namespace std;

const int SIZE = 5;

/* 
 * 使用1维数组表示2维数组
 *
 * 分析： 用1维数组表示2维数组， 困难的地方在下标的处理
 *        公式为:  pos(i,j) = pos(i*size + j)
 */
void gen1DArrayFrom2DArray( int (*src)[SIZE], int *dest )
{
    for( int i = 0; i < SIZE; ++i )
    {
        for( int j = 0; j < SIZE; ++j )
        {
            dest[ i*SIZE + j ] = src[i][j];
        }
    }
}

/* 
 *  用递归函数完成对此数组的分割，即先试从大的方面来看，
 *  此二维（实际是一维）数组，可以有上左，上右，下左，
 *  下右，正中，五个点。找出这五个点并输出，即可将此数
 *  组分成四个小块。分小块时顺注意，要判断还能不能分。
 *  如果能分就递归调用上面方法。
 *  如不能则直接将各点输出。 
 *
 *  分析： 平方型的二维数组分出来的四个小块依旧是平方型的
 */

// 此处传递的是，小块左上角的坐标和其宽度
void divide2DArray( int (*src)[SIZE],
            int left, int upper, int len )
{
    int offset = len - 1;
    cout << "block,  left: " << left << "  upper: " << upper << "   len: " << len << endl;
    // 输出上左，上右，下左，下右，正中
    cout << "\tupper left: " << src[upper][left] << endl;
    cout << "\tupper right: " << src[upper][left + offset] << endl;
    cout << "\tlower left: " << src[upper + offset][left] << endl;
    cout << "\tlower right: " << src[upper + offset][left + offset] << endl;

    int mid = offset/2;
    cout << "\tmid point: " << src[upper+mid][left+mid] << endl;

    if( mid >= 2 )
    {
        mid += 1;
        // 左上角的小块
        divide2DArray( src, upper, left, mid );
        // 右上角的小块
        divide2DArray( src, upper, left+mid, mid );
        // 左下角的小块
        divide2DArray( src, upper+mid, left, mid );
        // 右下角的小块
        divide2DArray( src, upper+mid, left+mid, mid );
    }
}


int main(void)
{
    int a[SIZE][SIZE] = {
        { 0, 1, 2, 3, 4 },
        { 5, 6, 7, 8, 9 },
        { 10, 11, 12, 13, 14 },
        { 15, 16, 17, 18, 19 },
        { 20, 21, 22, 23, 24 }
    };

    int dest[SIZE*SIZE];
    gen1DArrayFrom2DArray( a, dest );
    outputArray( dest, SIZE*SIZE, ' ' );

    divide2DArray( a, 0, 0, 5 );

    return 0;
}
