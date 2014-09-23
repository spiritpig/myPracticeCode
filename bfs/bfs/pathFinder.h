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

	void readPathFromDirMap( const vector2 &end );
	void clearPath();

public:
	pathFinder();
	bool findPathOneStep( char (*maze)[CEL], const vector2 &start, const vector2 &end );
	void findPath( char (*maze)[CEL], const vector2 &start, const vector2 &end );
	MyQueue* getPath();

private:
	char dirMap[ROW][CEL];
	MyQueue path;
};

#endif // PATHFIDNER_AFX END