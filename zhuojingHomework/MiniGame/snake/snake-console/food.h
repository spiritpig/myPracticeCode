#ifndef FOOD
#define FOOD

#include "stdafx.h"

class food
{
	point pos;
	bool isSpace( const Node *head, const point &pos );
public:
	food()
	{
	}

	~food() 
	{
	}

	void genRandomFood( const Node *head );
	void draw();

	point &getFoodPos()
	{
		return pos;
	}
};

#endif