// stack.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	stackList<int> sa;

	for ( int i=0; i<10; i+=3 )
	{
		sa.push( i );
		printf( "����ɹ�, %d\n", i );
	}

	int t = -1;
	sa.getTop( t );
	printf( "top(T): %d\n", t );
	printf( "t top(): %d\n", sa.getTop() );
	
	for ( int i = 0; i<20; ++i )
	{
		
		if( sa.pop( i ) )
		{
			printf( "�����ɹ�, %d\n", i );
		}
		else
		{
			printf( "����ʧ��, %d\n", i );
		}
	}

	for ( int i = 0; i<20; ++i )
	{
		if( sa.pop() )
		{
			printf( "�����ɹ�\n" );
		}
		else
		{
			printf( "����ʧ��\n" );
		}
	}

	sa.setEmpty();
	
	if( sa.isEmpty() )
	{
		printf( "ջΪ��\n" );
	}

	return 0;
}

