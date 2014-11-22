#ifndef SNAKE
#define SNAKE

#include "stdafx.h"

class snake
{
	point headPos, prevHeadPos, prevTailPos;
	int prevDir, curSnakeNodeNum;
	MyQueue snakeNodes;
	bool isEatFood;

	int convertDirCharToDirNum( char dir );
	bool canWeMove( int dir )
	{
		int pDir = convertDirCharToDirNum( prevDir );
		return (pDir + dir) != 0;
	}

public:
	snake();
	~snake();

	void draw();
	void move( const char dir );
	void onEatFood();

	bool isHitSnake();

	bool isHitWall()
	{
		if( headPos.x <= 0 || headPos.x >= MAP_WIDTH-1 ||
			headPos.y <= 0 || headPos.y >= MAP_HEIGHT-1 )
		{
			return true;
		}
		return false;
	}

	bool isHitFood( const point &pos )
	{
		if( headPos.x == pos.x &&
			headPos.y == pos.y )
		{
			isEatFood = true;
			return true;
		}
		return false;
	}

	const Node * getHead()
	{
		return snakeNodes.getHead();
	}

	int getCurSnakeNodeNum()
	{
		return curSnakeNodeNum;
	}

	void firstDraw();
};

#endif // SNAKE end