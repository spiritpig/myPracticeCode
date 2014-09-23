/*
 * =====================================================================================
 *
 *       Filename:  homework2.cpp
 *
 *    Description:  作业ING
 *
 *        Version:  1.0
 *        Created:  2014/7/18 8:40:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "../common.h"
#include <cstring>
#include <cstdio>
using namespace std;

/*  
一、算法学习，读懂下列排序方法并自己实现一些数的排序。
        利用数组对数字进行排序。
        方法一：选择法（例为大到小）。
        假定当前有10数存放于一个数组内，次序不一。
        首先用第一个数和其它九个进行一一比较，如果
        第一个数小于要比较的数，则交换两个数据。当
        完成9次比较以后，第一个数的位置会存放此数组
        中最大的数。第二次，放弃第一个数，从第二个数
        开始和后八个数进行一一比较，如果第二个数小于
        要比较的数，则交换两个数据。如此循环9次就可以
        排好序了。（第10次不用比较，最后一个一定是最小的数）
        原理：每次选出一个余下的数中的最大值。
*/

void sort_select( int a[], int n )
{
    for( int i = 0; i < n-1; ++i )   
    {
        for( int j = i+1; j < n; ++j )
        {
            if( a[i] < a[j] )
            { 
                swap( a[i], a[j] );
            }
        }
    }
}

/* 方法二：冒泡法（例为大到小）。
 *      假定当前有10数存放于一个数组内，次序不一。
 *      首先用第0个和第1个进行比较，如果第1个小于第0个，
 *      则进行交换。跟着用第1个和第2个进行比较，小于则
 *      交换，再拿第2和第3个进行比较，小于则交换……一直
 *      比到最后一个，完成第一次冒泡，第9个数将会是数组中
 *      最小数。第二次同样的方法比到第8个结束，冒出第二小
 *      的数。依此类推，冒到第1个即可。原理：让小的数(或者是大的数)
 *      像泡泡一样冒到数组的一边。  
 */
void sort_bubble( int a[], int n )
{
    bool isSwaped = false;

    for( int i = 0; i < n - 1; ++i )
    {
        isSwaped = false;

        for( int j = 0; j < n - i - 1; ++j )
        {
            if( a[j] < a[j+1] )
            {
                swap( a[j], a[j+1] );
                isSwaped = true;
            }
        }

        if( !isSwaped )
        {
            return;
        }
    }
}

///////////////////////////////////////////////////////////////////////////
//
//  第二题
//
///////////////////////////////////////////////////////////////////////////

/*
 * 1、将一个数组中的值按逆序重新存放。
 *     例：原来顺序为8,4,5,6,1的数组，
 *     要求改为1,6,5,4,8即可。 
 */
void reverse( int a[], int n )
{
    for( int i = n/2 - 1; i >= 0; --i  )
    {
        swap( a[i], a[n-1-i] );
    }
}

/* 
 * 2、已有一个已排好序的数组，现输入一个数，
 *      要求按原来排序的规律将它插入到这个数组中。 
 */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  checkOrder
 *  Description:  get array order
 *                 true == ascend 
 *                 false == descend
 *
 *                 The input array must be sorted
 *                 and it's length should greater or equal to 2
 * =====================================================================================
 */
bool checkOrder( int a[], int n )
{
    return a[0] < a[1];
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  insertByOrder
 *  Description:  将输入的val按排序顺序插入到对应位置中
 *                  由于插入操作可能需要对输入数组进行扩容
 *                  请传递动态分配的数组
 * =====================================================================================
 */
void insertByOrder( int **a, int n, int val )
{
    bool isAscend = checkOrder( *a, n );

    int *b = new int[n+1];

    int i = 0;
    for( i = 0; i < n; ++i )
    {
        b[i] = (*a)[i];

        if( ( isAscend && val < (*a)[i] ) ||
            ( !isAscend && val > (*a)[i] ) )        
        {
            // 若发现符合情况的位置，将val插入到该位置
            // 同时将后面的数据后移
            b[i] = val;   
            b[i+1] = (*a)[i];
            ++i;

            break; 
        }
    }
    
    for( i; i < n+1; ++i )
    {
        b[i+1] = (*a)[i];
    }

    delete [] *a;
    *a = b;
}

/* 
 * 3、有一行电文，已按下面规律译成密码：
 *      A->Z  a->z  B->Y  b->y  C->X  c->x  ……  M->N  m->n
 *      即第1个字母变成第26个字母，第i个字母变成第(26-i+1)个字母。
 *      非字母字符不变。要求编写程序完成以下密码的破译工作。
 *      要求破译字符串：X Kiltizn! 
 */
char getNewCode( char c )
{
    char baseC = ' ';

    if( ( c >= 'A' && c <= 'Z' ) ||
        ( c >= 'a' && c <= 'z' ) )
    {
        if( c <= 'Z' )
        {
            baseC = 'A';
        }
        else
        {
            baseC = 'a';
        }
        
        // 根据,公式 第i个字母变成，26-i+1
        // 但是由于我们的标号是从0开始的，所以需要-1
        int offset = 26 - ( c - baseC ) - 1;
        return baseC + offset;
    }

    return c;
}

void translate( char *code )
{
    int strLen = strlen( code );
    for( int i = 0; i < strLen; ++i )
    {
        code[i] = getNewCode( code[i] );
    }

}


/*
 *  4、编写程序完成一系列有规则文件名的输出。
 *  例：“Water01.TGA”, “Water02.TGA”,
 *      “Water03.TGA”……“Water44.TGA”。
 *      完成此程序需用到sprintf函数，sprintf函数原形为：
 *      sprintf(字符串数组名，“字符集[%d][%c][%f][%s]字
 *      符集”，表达式1，表达式2……表达式n);功能为：将表
 *      达式1……表达式n按字符的的输出方式输出到字符串数组名所在的数组中。  
 *
 */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  outputSomeFile
 *  Description:  输出一系列有规则的文件名
 * =====================================================================================
 */
int getNumLen( int num )
{
    int len = 0;
    while( num > 0 )
    {
        num/=10;
        len++;
    }

    return len;
}

void getFileIdStr( int number, int len, char *dest )
{
    int destLen = getNumLen( number );

    char tempStr[20];

    // 计算前置零的数量
    int i;
    for( i = 0; i < len - destLen; ++i )
    {
        tempStr[i] = '0';
    }
    tempStr[i] = '\0';

    sprintf( dest, "%s%d", tempStr, number );
}

void outputSomeFile( const char *fileNameBase, const char *extension, 
                     int IdStart, int IdEnd,   const char *separtor )
{
    int numLen = getNumLen( IdEnd );

    char dest[1024];
    for( int i = IdStart; i <= IdEnd; ++i )
    {
        char tempIdStr[20] = " "; 
        getFileIdStr( i, numLen, tempIdStr );

        sprintf( dest, "%s%s.%s%s", fileNameBase, tempIdStr, 
                                    extension, separtor );
        cout << dest;
    }
}


int main(void)
{
    int *a = new int[6];
    
    // 对数组进行赋值，比较坑爹的赋值方法
    a[0] = 1;
    a[1] = 2323232;
    a[2] = 45;
    a[3] = 0x2341;
    a[4] = 9090;
    a[5] = 389946;

    int aLen = 6;
    outputArray( a, aLen, ' ' );
    cout << endl;

    cout << "bubble sort: " << endl;
    sort_bubble( a, aLen );
    outputArray( a, aLen, ' ' );
    cout << endl;

    cout << "reverse: " << endl;
    reverse( a, aLen );
    outputArray( a, aLen, ' ' );
    cout << endl;

    cout << "insertByOrder: " << endl;
    insertByOrder( &a, aLen, 50 );
    outputArray( a, aLen+1, ' ' );
    cout << endl;

    cout << "code translate: " << endl;
    char str[] = "X Kiltizn!";
    translate( str );
    cout << str << endl;
    cout << endl;

    cout << "output some file:" << endl;
    outputSomeFile( "water", "TGA", 1, 200, "\n" );

    delete [] a;

    return 0;
}
