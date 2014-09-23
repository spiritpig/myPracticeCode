// dfs.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include "dfsPathFinder.h"

int main(int argc, char* argv[])
{
	char tempmapdata[ROW][COL]={
		{ 0,1,0,0,0,0,0,0,0,0 },
		{ 0,1,1,0,1,1,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,1,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,1,1,1,0 },
		{ 0,1,0,0,1,1,1,1,1,0 },
		{ 0,0,0,1,1,0,0,0,1,0 },
		{ 0,1,0,0,0,0,1,0,1,0 },
		{ 0,1,1,1,0,1,1,0,1,1 },
		{ 0,0,0,0,0,0,1,0,0,0 }
	};

	dfsPathFinder dpf;
	StackDArray<dfsNode> path;
	dpf.findPath( tempmapdata, 0, 0, 9, 9, path );

	printf( "\n" );
	for ( int i=0; i<COL; ++i )
	{
		for ( int j=0; j<ROW; ++j )
		{ 
			printf( "%d ", tempmapdata[i][j] );
		}
		printf( "\n" );
	}
	printf( "\n" );

	dfsNode node;
	while ( !path.Empty() )
	{
		path.Pop( node );
		printf( "%d, %d   ", node.pos.x, node.pos.y );
	}

	return 0;
}

