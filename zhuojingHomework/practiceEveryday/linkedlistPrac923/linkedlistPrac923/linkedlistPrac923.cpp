// linkedlistPrac923.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "myList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	linkedList<int> ll;

	ll.Insert( 0, 123231 );
	ll.Insert( 0, 0 );
	for ( int i=0; i<10; ++i )
	{
		ll.Insert( ll.Length()-1, i%5 );
	}
	ll.Insert( ll.Length(), 999 );

	if( ll.Find( 123231, 1 ) )
	{
		printf( "�ҵ�4Ԫ��\n" );
	}

	int t = -1;
	while ( ll.Delete( 0, t ) )
	{
		printf( "%d ", t );
	}
	printf( "\n" );

	return 0;
}

