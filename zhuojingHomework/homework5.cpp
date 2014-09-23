/*
 * =====================================================================================
 *
 *       Filename:  homework5.cpp
 *
 *    Description:  第五次作业
 *
 *        Version:  1.0
 *        Created:  2014/7/19 8:52:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include "../common.h"
using namespace std;

/*
 *  1、写一个函数，求字符串长度。
 *      在main里面输入一个字符串，求其长度。 
 */

int myStrLen( char *str )
{
    int len = 0;
    while( *str != '\0' )
    {
        str++;
        len++;
    }

    return len;
}


/*
 *  2、有一字符串，包含n个字符，要求写一个函数，
 *      将此字符串中从m(m为输入值)个字符开始的全部字符拷贝到另一字符串。
 */
void copyFromStr( char *src, char *dest, int pos )
{
    int len = myStrLen( src );

    // 检测错误
    if( len <= 0 && pos <= 0 )
    {
        return;
    }

    int i = 0;
    for( i = pos - 1; i < len; ++i )
    {
        dest[i-(pos-1)] = src[i];
    }
    dest[i-(pos-1)] = '\0';
}


/*
 *  3、输入一个字符串，分别统计出其中大写字母，
 *      小写字母，空格，数字的个数。
 *
 */


/* 
 * ===  BLOCK  ======================================================================
 *        name :  检测字符函数组
 * =====================================================================================
 */
bool isUpper( char c )
{
    return c >= 'A' && c <= 'Z';
}
bool isLower( char c )
{
    return c >= 'a' && c <= 'z';
}
bool isSpace( char c )
{
    return c == ' ';
}
bool isDigit( char c )
{
    return c >= '0' && c <= '9';
}


void countElement( char *src )
{
    int countUpper = 0, 
        countLower = 0,
        countSpace = 0,
        countDigit = 0;   

    int len = myStrLen( src );
    for( int i = 0; i < len; ++i )
    {

        //  分别检测四种情况
        if( isUpper( src[i] ) )
        {
            countUpper++;
        }
        else
        if( isLower( src[i] ) )
        {
            countLower++;
        }
        else
        if( isSpace( src[i] ) )
        {
            countSpace++;
        }
        else
        if( isDigit( src[i] ) )
        {
            countDigit++;
        }
    }

    cout << "the number of uppercase, lowercase, space, digit in " << src << " : \n\t\t"  
         << countUpper << "\t\t" 
         << countLower << "\t" 
         << countSpace << '\t'
         << countDigit << endl;
}


/*
 *  4、在主函数中输入5个等长的字符串，用另一函数对它们进行排序。
 *      然后在主函数里输出这5个排好序的字符串。  
 *
 */
void sortFiveStr( char **strs )
{
    for( int i = 0; i < 4; ++i )
    {
        for( int j = 0; j < 4 - i; ++j )
        {
            if( strcmp( strs[j], strs[j+1] ) < 0 )
            {
                swap( strs[j], strs[j+1] );
            }
        }
    }
}


/* 
 *  5、将n个数按输入时顺序的逆序排列，用函数实现，并输出。 
 *
 */
void reverse( int a[], int n )
{
    for( int i = n/2 - 1; i >= 0; --i  )
    {
        swap( a[i], a[n-1-i] );
    }
}


int main(void)
{ 
    char str[1024];
    cout << "enter a string: ";
    cin.getline( str, 1024 ); 

    cout << "the length of " << str << " is: " << myStrLen( str ) << endl;

    char dest[100];

    int offset = 0;
    cout << "enter  offset of string: ";
    cin >> offset;
    copyFromStr( str, dest, offset );
    cout << dest << endl;
    
    countElement( str );


    // 为了交换字符串的行指针，采用动态内存分配的方式
    char **fiveStr = new char*[5];
    for (int i = 0; i < 5; i++)
    {
        fiveStr[i] = new char[100];
    }

    cout << "enter five string, the length should equal: \n";
    // 此处需要吃掉多余的字符
    while( getchar() != '\n' );

    // 分别输入5个字符串
    for( int i = 0; i < 5; ++i )
    {
        cin.getline( fiveStr[i], 100 );
    }

    // 排序并输出5个字符串
    sortFiveStr( fiveStr );
    for( int i = 0; i < 5; ++i )
    {
        cout << i << ": " << fiveStr[i] << endl;
    }


    // 输入数字数
    int n = 0;
    cout << "size of number :";
    cin >> n;

    int *a = new int[n];
    for( int i = 0; i < n; ++i )
    {
        cin >> a[i];
    }

    // 逆序并输出
    outputArray( a, n, ' ' );
    reverse( a, n );
    outputArray( a, n, ' ' );
    

    // delete all
    for( int i = 0; i < 5; ++i )   
    {
        delete[] fiveStr[i];
    }
    delete[] fiveStr;
    delete[] a;

    return 0;
}
