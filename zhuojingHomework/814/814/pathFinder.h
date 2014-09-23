/*
	������ pathFinder��·����������
		  �ڲ�ʹ��BFS��ΪѰ·�㷨��

	���ڣ� 2014.08.17

	���ߣ� pinkbeen
 */
#include "stdafx.h"

#ifndef PATHFINDER_AFX
#define PATHFINDER_AFX

class pathFinder
{
private:
	bool isPointOutofRange( const vector2 &v );
	bool isPointCanBeWalked( const vector2 &v, p2DArray maze );
	bool isPointValid( const vector2 &v, p2DArray maze );
	int getOppositeDir( int dir );

	// ���·�����Ա���һ�β��ҳ�����·��
	// ���ᱻ��һ�ε�·��Ӱ��
	void clearPath();

public:
	pathFinder();

	// findpath���������dirMap����Ҫ��ȡ·��ʱ��
	// ����ʹ��readPathFromDirMap���������·��
	void findPath( p2DArray maze, const vector2 &start, const vector2 &end );

	// ��DirMap�ж�ȡ��ʵ�ʵ�·��
	void readPathFromDirMap( const vector2 &end );

	// ����ӿڣ����û���ȡ·�����ҵĽ��
	p2DArray getDirMap();
	MyQueue* getPath();

private:
	char dirMap[ROW][CEL];
	MyQueue path;
};

#endif // PATHFIDNER_AFX END