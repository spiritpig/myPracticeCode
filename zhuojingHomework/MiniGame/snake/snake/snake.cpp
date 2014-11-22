#include "stdafx.h"
using std::cout;

snake::snake()
{
	// 初始化三节蛇
	point pos = { MAP_WIDTH/2 + 1, MAP_HEIGHT/2 - 1 };
	snakeNodes.push_back( pos );
	pos.x -= 1;
	snakeNodes.push_back( pos );
	pos.x -= 1;
	snakeNodes.push_back( pos );

	prevDir = NONE;
	headPos.x = pos.x;
	headPos.y = pos.y;

	prevHeadPos.x = headPos.x;
	prevHeadPos.y = headPos.y;

	prevTailPos.x = -1;
	prevTailPos.y = -1;

	isEatFood = false;
	curSnakeNodeNum = 3;
}
//---------------------------------------------------------------------------
snake::~snake()
{
}
//---------------------------------------------------------------------------
void snake::firstDraw()
{
	const Node *n = snakeNodes.getHead();
	n = n->next;

	changeTextColor( SNAKE_TAIL_TEXT_COLOR );
	while( n != NULL )
	{
		gotoXY( n->data.x, n->data.y );
		cout << SNAKE_CHAR;

		n = n->next;
	}
	// 我们只画头
	gotoXY( prevHeadPos.x, prevHeadPos.y );
	changeTextColor( SNAKE_HEAD_TEXT_COLOR );
	cout << SNAKE_HEAD_CHAR;

	changeTextColor( DEFAULT_TEXT_COLOR );
}
//---------------------------------------------------------------------------
void snake::draw()
{
	if( prevDir != NONE )
	{
		// 将前面的蛇头画成尾巴
		gotoXY( prevHeadPos.x, prevHeadPos.y );
		changeTextColor( SNAKE_TAIL_TEXT_COLOR );
		cout << SNAKE_CHAR;

		if( isEatFood )
		{
			isEatFood = false;
		}
		else
		{
			gotoXY( prevTailPos.x, prevTailPos.y );
			changeTextColor( DEFAULT_TEXT_COLOR );
			cout << SPACE_CHAR;
		}

		// 我们只画头
		gotoXY( headPos.x, headPos.y );
		changeTextColor( SNAKE_HEAD_TEXT_COLOR );
		cout << SNAKE_HEAD_CHAR;

		prevHeadPos.x = headPos.x;
		prevHeadPos.y = headPos.y;
	}
}
//---------------------------------------------------------------------------
void snake::move( const char dir ) 
{
	int newDir = convertDirCharToDirNum( dir );
	// 检测是否允许移动
	// 不允许向蛇朝向的反方向移动
	// 同时，检测输入是否为方向键,不是则不产生反应
	if( !canWeMove( newDir ) || newDir == NONE )
	{
		// 最开始蛇未动的时候，直接返回
		if( prevDir == NONE )
		{
			return;
		}
		else
		{
			newDir = prevDir;
		}
	}

	Node *n;
	snakeNodes.pop( &n );
	prevTailPos = n->data;

	switch( newDir )
	{
	case UP:
		{
			n->data.y = headPos.y-1;
			n->data.x = headPos.x;
		}
		break;

	case DOWN:
		{
			n->data.y = headPos.y+1;
			n->data.x = headPos.x;
		}
		break;

	case LEFT:
		{
			n->data.y = headPos.y;
			n->data.x = headPos.x-1;
		}
		break;

	case RIGHT:
		{
			n->data.y = headPos.y;
			n->data.x = headPos.x+1;
		}
		break;

	default:
		{
			return;
		}
		break;
	}

	// 储存之前的运动方向。
	prevDir = newDir;
	headPos.x = n->data.x;
	headPos.y = n->data.y;

	snakeNodes.push_back( n );
}
//---------------------------------------------------------------------------
int snake::convertDirCharToDirNum( char dir )
{
	switch( dir )
	{
	case 'W': case 'w':
		{
			return UP;
		}
		break;

	case 'S': case 's':
		{
			return DOWN;
		}
		break;

	case 'A': case 'a':
		{
			return LEFT;
		}
		break;

	case 'D': case 'd':
		{
			return RIGHT;
		}
		break;

	default:
		{
			return NONE;
		}
		break;
	}
}
//---------------------------------------------------------------------------
void snake::onEatFood()
{
	Node *n = new Node;
	n->next = NULL;

	switch( prevDir )
	{
	case UP:
		{
			n->data.x = prevTailPos.x;
			n->data.y = prevTailPos.y;
		}
		break;

	case DOWN:
		{
			n->data.x = prevTailPos.x;
			n->data.y = prevTailPos.y;
		}
		break;

	case LEFT:
		{
			n->data.x = prevTailPos.x;
			n->data.y = prevTailPos.y;
		}
		break;

	case RIGHT:
		{
			n->data.x = prevTailPos.x;
			n->data.y = prevTailPos.y;
		}
		break;
	}

	snakeNodes.push_front( n );
	++curSnakeNodeNum;
}
//---------------------------------------------------------------------------
bool snake::isHitSnake()
{
	Node *n = getHead()->next;

	// 我们遍历到蛇头的后面一节
	while( n->next != NULL )
	{
		if( headPos.x == n->data.x &&
			headPos.y == n->data.y )
		{
			return true;
		}
		n = n->next;
	}
	return false;
}