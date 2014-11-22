#include "stdafx.h"
using std::cout;

void food::genRandomFood( const Node *head )
{
	do 
	{
		pos.x = random( 1, MAP_WIDTH-2 );
		pos.y = random( 1, MAP_HEIGHT-2 );
	} 
	while( !isSpace( head, pos ) );
}

bool food::isSpace( const Node *head, const point &pos )
{
	Node *n = head->next;

	while( n != NULL )
	{
		if( pos.x == n->data.x &&
			pos.y == n->data.y )
		{
			return false;
		}

		n = n->next;
	}

	return true;
}

void food::draw()
{
	gotoXY( pos.x, pos.y );
	changeTextColor( FOOD_TEXT_COLOR );
	cout << FOOD_CHAR;

	changeTextColor( DEFAULT_TEXT_COLOR );
}
