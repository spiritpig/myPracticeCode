#include "AllDefine.h"

bool isPointOutOfRange( const POINT &pos )
{
	return (pos.x < 0) || (pos.x > COL-1) ||
		(pos.y < 0) || (pos.y > ROW-1);
}

bool isPointValid( char (*mapdata)[COL], const POINT &pos )
{
	return !isPointOutOfRange( pos ) &&
		(mapdata[pos.y][pos.x] == SPACE);
}

bool isPointEqual( int paX, int paY,
				   int pbX, int pbY )
{
	return (paX == pbX) && (paY == pbY);
}

bool isPointEqual( POINT pa, POINT pb )
{
	return (pa.x == pb.x) && (pa.y == pb.y);
}