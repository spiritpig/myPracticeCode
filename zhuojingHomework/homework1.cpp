/*
 * =====================================================================================
 *
 *       Filename:  diamond.cpp
 *
 *    Description:  第一次作业
 *
 *
 *        Version:  1.0
 *        Created:  2014/7/17 22:37:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <cmath>
using namespace std;

/*  
 *   1、打印出以下图形：
 *         *
 *        ***
 *       *****
 *        ***
 *         **
 */
void outputDiamond( int height )
{
    int halfHeight = height/2;

    for( int i = -halfHeight; i <= halfHeight; ++i )
    {
        // 输出前置空格部分
        for( int s = 0; s < abs( i ); ++s )
        {
            cout << ' ';
        }

        // 输出菱形部分
        for( int j = 0; j < 2*( halfHeight - abs( i ) ) + 1; ++j )
        {
            cout << '*';
        }

        cout << endl;
    }
}

/*
 * 
 * 2、  打印出所有水仙花数，所谓“水仙花数”是指一个3位数，
 *      其百位数的立方加十位数的立方加个位数的立方等于该数本身。
 *
 *      例：153是一个水仙花数，因为153=1*1*1+5*5*5+3*3*3。
 *
 */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isDaffodilNum
 *  Description:  check the input number is daffodilNum
 * =====================================================================================
 */
bool isDaffodilNum( int num )
{
    int orignNum = num;
    int temp = 0, sum = 0;
    for( int i = 0; i < 3; ++i )
    {
        temp = num%10;
        num /= 10;

        sum += temp*temp*temp;
    }

    return sum == orignNum;
}

void outputDaffodilNum()
{
    for( int i = 101; i <= 999; ++i )
    {
        if( isDaffodilNum( i ) )
        {
            cout << i << " ";
        }
    }
}

/*
 *  3、一个数如果恰好等于它的因子之和，这个数就是“完数”。
 *      例如6的因子为，1，2，3（即小于6的所有能整除6的数),
 *      而6=1+2+3，因此6是个“完数”。编写程序找出1000以内的所有完数。
 *
 */
bool isCompletedNum( int num )
{
    int sum = 1;
    int sqrtNum = ( float )sqrt( num );

    for( int i = 2; i <= sqrtNum; ++i )
    {
        if( num%i == 0 )
        {
            sum += i + num/i;
        }
    }

    return sum == num;
}


void findCompletedNum( int range )
{
    for( int i = 0; i <= range; ++i )
    {
        if( isCompletedNum( i ) )
        {
            cout << i << " ";
        }
    }
}

/* 
 * 4、编写程序完成（1）+（1+2）+（1+2+3）+……+（1+2+3……+19+20）之和。
 * 
 */
int calcSum( int max )
{
    int sum = 0;
    for( int i = 1; i <= max; ++i )
    {
        for( int j = 1; j <= i; ++j )
        {
            sum += j;
        }
    }

    return sum;
}

int main(void)
{
    cout << "输出菱形：" << endl;
    outputDiamond( 5 );

    cout << "输出所有水仙花数： " << endl;
    outputDaffodilNum();
    cout << endl;

    cout << "输出1000以内的完数： " << endl;
    findCompletedNum( 1000 );
    cout << endl;

    cout << "输出1 + 1+2 + 1+2+3 + ... + 1+2+..。+19+20的值： " << endl;
    cout << calcSum( 20 );
    cout << endl;

    return 0;
}

