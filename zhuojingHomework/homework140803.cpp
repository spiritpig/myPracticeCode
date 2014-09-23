/*
 * =====================================================================================
 *
 *       Filename:  homework140803.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/8/3 14:02:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

bool		fCompare( double a, double b );									// 为了更加准确的判断一个浮点数与零的关系而写
int			myStrlen( const char *str );									// 计算字符串长度
int         getDigitNum( int n, const int radix );							// 获取数字位数的函数
int         getDigitNum( long long n, const int radix );
int         getDigitNum( unsigned int n, const int radix );
int			myAtoi( char *str );											// 数字字符串转换为，整数
char*		myLLtoa( long long num, char *str, int radix );					// 长整形转换为字符串，可调整进制
char*       myItoa( int num, char *str, int radix );						// 整形转换为字符串，可调整进制
char*		myUItoa( unsigned int num, char *str, int radix );				// 无符号整形转换为字符串，可调整进制
char*		myFtoa( double dn, char *str, int precision );					// 浮点数转换为字符串，可调整精度
char        getHexChar( int cD );                                                               // 获取16进制数字的对应的表示16进制的字符
int         getHexVal( const char c );                                                          // 获取表示16进制的字符的16进制数字
long        strtol( const char *str, char **endPtr, int base );                                 // 字符串转换为long
double      getIntegerFromStr( const char *str, char **endPtr );                                   // 获取整数部分，用于配合浮点数



/*-----------------------------------------------------------------------------
 *  
 *  函数定义区
 *
 *-----------------------------------------------------------------------------*/
bool fCompare( double a, double b )
{
    return a - b > 1e-12;
}

int	myStrlen( const char *str )
{
    int size = 0;
    while( *(str++) != '\0' )
    {
        size++;
    }

    return size;
}

int getDigitNum( int n, int radix ) 
{                         
    int count = 1;        
    if( n < 0 )           
    {                     
        n = -n;           
    }                     

    while( n > radix-1 )        
    {                     
        n/=radix;            
        count++;          
    }                     

    return count;         
}                         

int getDigitNum( unsigned int n, const int radix ) 
{                         
	int count = 1;        

	while( n > radix-1 )        
	{                     
		n/=radix;            
		count++;          
	}                     

	return count;         
}                         

int getDigitNum( long long n, int radix ) 
{                         
	int count = 1;        
	if( n < 0 )           
	{                     
		n = -n;           
	}                     

	while( n > radix-1 )        
	{                     
		n/=radix;            
		count++;          
	}                     

	return count;         
}

int	myAtoi( const char *str )
{
    int num = 0;
    int i = 0;
    while( str[i] != '\0' && 
            str[i] >= '0' && 
            str[i] <= '9' 	)
    {
        num = str[i] - '0' + num*10;
        ++i;
    }

    return num;
}

char getHexChar( int cD )
{
    switch( cD )                   
    {                                    
        case 10:                             
            {                            
                return 'a';        
            }                            
            break;                       

        case 11:                             
            {                            
                return 'b';        
            }                            
            break;                       

        case 12:                             
            {                            
                return 'c';        
            }                            
            break;                       

        case 13:                             
            {                            
                return 'd';        
            }                            
            break;                       

        case 14:                             
            {                            
                return 'e';        
            }                            
            break;                       

        case 15:                             
            {                            
                return 'f';        
            }                                
            break;                       
    }

    return -1;
}                                    

char * myItoa( int num, char *str, int radix )
{
    if( !str )
    {
        return NULL;
    }

    // 填充符号位
    int i = 0;
    if( num < 0 )
    {
        num = -num;
        str[i] = '-';
        ++i;
    }

    int digits = getDigitNum( num, radix ); 
    int curDigit = 0;
    // 依次取出位数
    while( digits != 0 )   
    {
        curDigit = num / (int)pow( (double)radix, (double)digits-1 ) % radix;

        if( curDigit < 10 )
        {
            str[i] = curDigit + '0';
        }
        else
        {
            str[i] = getHexChar( curDigit );
        }

        ++i;
        --digits;
    }
    str[i] = '\0';

    return str;
}

char * myLLtoa( long long num, char *str, int radix )
{
    if( !str )
    {
        return NULL;
    }

    // 填充符号位
    int i = 0;
    if( num < 0 )
    {
        num = -num;
        str[i] = '-';
        ++i;
    }

    long long digits = getDigitNum( num, radix ); 
    int curDigit = 0, curBase;
    // 依次取出位数
    while( digits != 0 )   
    {
        curBase = (int)pow( (double)radix, (double)digits-1 );
        curDigit = num / curBase % radix;

        if( curDigit < 10 )
        {
            str[i] = curDigit + '0';
        }
        else
        {
            str[i] = getHexChar( curDigit );
        }

        ++i;
        --digits;
    }
    str[i] = '\0';

    return str;
}

char * myFtoa( double dn, char *str, int precision = 12 )
{
    if( !str )
    {
        exit(-1);
    }

    // 处理负数
    if( dn < 0 )
    {
        dn = -dn;
    }

    long long n = ( long long )dn;
    myLLtoa( n, str, 10 );

    int dotStartIndex = myStrlen( str ),
        p = 0;

    // 安插小数点
    str[dotStartIndex] = '.';
    ++dotStartIndex;

    dn -= n;
    while ( fCompare( dn, 0.0f ) && 
            precision > 0 )
    {
        // 将最大的小数位变为整数部分
        dn *= 10;
        p = (int)dn;
        str[dotStartIndex] = p + '0';

        // 减掉计算完成的整数部分
        dn -= (int)dn;
        dotStartIndex++;
        --precision;
    }

    if( str[dotStartIndex-1] == '.')
    {
        str[dotStartIndex] = '0';
        ++dotStartIndex;
    }

    str[dotStartIndex] = '\0';

    return str;
}

int getHexVal( const char c )
{
    switch( c )
    {
    case 'a': case 'A':
        {
            return 10;
        }
        break;

    case 'b': case 'B':
        {
            return 11;
        }
        break;

    case 'c': case 'C':
        {
            return 12;
        }
        break;

    case 'd': case 'D':
        {
            return 13;
        }
        break;

    case 'e': case 'E':
        {
            return 14;
        }
        break;

    case 'f': case 'F':
        {
            return 15;
        }
        break;
    }

    return -1;
}

long myStrtol( const char *str, char **endPtr, int base )
{
    if( !str )                                                                
    {        
        exit( -1 );
    }                                                                         

    long sign = 1;
    int i = 0;
    if( str[i] == '-')
    {
        sign = -1;
        ++i;
    }

    // 根据base计算能够读取的数字字符的最大值
    char upperChar = '9';
    if( base <= 10 )
    {
        upperChar = '9' - 10 + base;
    }

    long num = 0;                     
    while( str[i] != '\0' &&         
           str[i] >= '0' &&         
           str[i] <= upperChar 	)    
    {                                
        if( str[i] >= '0' && str[i] <= upperChar )
        {
            num = str[i] - '0' + num*base; 
        }
        // 判断16进制
        else
        if( base == 16 && 
            str[i] >= 'a' && str[i] <= 'f' &&
            str[i] >= 'A' && str[i] <= 'F' )
        {
            num = getHexVal( str[i] ) + num*base;
        }
        ++i;                         
    }                                
                                     
    *endPtr = ( char * )&str[i];
    return sign*num;                      
}                                                              

double getIntegerFromStr( const char *str, char **endPtr )
{
    if( !str )                                                                 
    {                                                                          
        exit( -1 );
    }                                                                          

    double sign = 1.0;                                                             
    int i = 0;                                                                 
    if( str[i] == '-' )                                                         
    {                                                                          
        sign = -1.0;                                                             
        ++i;                                                                   
    }                                                                          

    double ret = 0.0;   
    while( str[i] != '.' && str[i] != '\0' )
    {
        if( str[i] > '9' || str[i] < '0' )
        {
            break;
        }
        else
        {
            ret = str[i] - '0' + ret*10;
        }

        ++i;
    }

    *endPtr = ( char * )&str[i];
    return sign*ret;
}

double myAtof( const char *str )
{
    if( !str )
    {
        exit(-1);
    }

    double ret = 0.0;
    char *strPos;
    ret = getIntegerFromStr( str, &strPos ); 
    
    // 如果有小数部分处理之
    if( *strPos == '.' )
    {
        ++strPos;

        char *fracEnd;
        double fracPart = getIntegerFromStr( strPos, &fracEnd );

        int fracLen = strPos - fracEnd;

        // 处理一下符号位
        if( str[0] == '-' )
        {
            fracPart = -fracPart;
        }
        printf( "%f %f %d\n\t", ret, fracPart, fracLen );
        ret += fracPart * pow( 10, fracLen );
    }

    return ret;
}

double myStrtod( const char *str, char **endPtr )
{
    if( !str )
    {
        exit(-1);
    }

    double ret = 0.0;
    char *strPos;
    ret = getIntegerFromStr( str, &strPos ); 
    
    // 如果有小数部分处理之
    if( *strPos == '.' )
    {
        ++strPos;

        char *fracEnd;
        double fracPart = getIntegerFromStr( strPos, &fracEnd );

        int fracLen = strPos - fracEnd;

        // 处理一下符号位
        if( str[0] == '-' )
        {
            fracPart = -fracPart;
        }
        printf( "%f %f %d\n\t", ret, fracPart, fracLen );
        ret += fracPart * pow( 10, fracLen );

        // 储存第一个无效字符的位置
        *endPtr = fracEnd;
    }
    else
    {
        *endPtr = strPos;
    }

    return ret;
}

/*-----------------------------------------------------------------------------
 *
 *  程序入口点
 *
 *-----------------------------------------------------------------------------*/
int main(void)
{
    char *ep;
    printf( "%.20f\n", myAtof( "12232.334342323232323" ) );
    printf( "%.20f\n", myStrtod( "13422434.0002323232323fdfcnvmx0", &ep ) );
    printf( "%s\n", ep );

    return 0;
}
