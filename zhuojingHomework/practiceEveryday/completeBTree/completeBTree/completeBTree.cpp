// completeBTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BTreeComplete.h"

void outputBTree( BTreeComplete<int> &ciBTree )
{
	for ( int i=0; i<ciBTree.size(); ++i )
	{
		printf( "%d ", ciBTree[i] );
	}
	printf( "\n" );
}

int _tmain(int argc, _TCHAR* argv[])
{
	BTreeComplete<int> ciBTree;

	for ( int i = 0; i < 10; ++i )
	{
		ciBTree.add( i );
	}
	outputBTree( ciBTree );

	ciBTree.remove();
	outputBTree( ciBTree );

	int t;
	if ( ciBTree.child( t, 3 ) )
	{
		printf( "%d ������Ϊ %d\n", 3, t );
	}
	
	if ( ciBTree.parent( t, 8 ) )
	{
		printf( "%d �ĸ���Ϊ %d\n", 8, t );
	}

	if( ciBTree.left_sinling( t, 7 ) )
	{
		printf( "%d �����ֵ�Ϊ %d\n", 7, t );
	}

	if( ciBTree.right_sinling( t, 7 ) )
	{
		printf( "%d �����ֵ�Ϊ %d\n", 7, t );
	}

	return 0;
}

