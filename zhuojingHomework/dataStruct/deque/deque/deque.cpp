// deque.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	myDequeList<int> mda;

	for ( int i=0; i<30; i+=2 )
	{
		mda.push( i );
		printf( "����ɹ�,%d\n", i );
	}

	printf( "%d\n", mda.First() );

	int t=0;
	for ( int i=0; i<40; i+=2 )
	{
		if( mda.pop( t ) )
		{
			printf( "�����ɹ�,%d\n", t );
		}
		else
		{
			printf( "����ʧ��,%d\n", i );
		}
	}

	if( mda.pop() )
	{
		printf( "�����ɹ�\n" );
	}
	else
	{
		printf( "����ʧ��\n" );
	}

	mda.setEmpty();
	if( mda.isEmpty() )
	{
		printf( "ջΪ��\n" );
	}
	return 0;
}

