#include "stdafx.h"

vector2::vector2()
{
	x = 0;
	y = 0;
}

vector2::vector2( int x,int y )
{
	this->x = x;
	this->y = y;
}

vector2::vector2( vector2 const &other )
{
	this->x = other.x;
	this->y = other.y;
}

vector2& vector2::operator=( vector2 const &other )
{
	this->x = other.x;
	this->y = other.y;

	return *this;
}

vector2 vector2::operator+( vector2 const &other )
{
	vector2 temp;
	temp.x = this->x + other.x;
	temp.y = this->y + other.y;
	return temp;
}

vector2 vector2::operator-( vector2 const &other )
{
	vector2 temp;
	temp.x = this->x - other.x;
	temp.y = this->y - other.y;
	return temp;
}

vector2 vector2::operator*( int n )
{
	vector2 temp;
	temp.x = this->x*n;
	temp.y = this->y*n;
	return temp;
}

int vector2::operator*( vector2 const &other )
{
	return this->x*other.x 
		 + this->y*other.y;
}

vector2& vector2::operator+=( vector2 const &other )
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

vector2& vector2::operator-=( vector2 const &other )
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

vector2& vector2::operator*=( int n )
{
	this->x *= n;
	this->y *= n;

	return *this;
}

float vector2::Length()
{
	return sqrt( (float)this->x*this->x + 
				        this->y*this->y );
}

bool vector2::operator==( const vector2 &other )
{
	return (this->x == other.x) &&
		   (this->y == other.y);
}

std::ostream& operator<<( std::ostream &out, const vector2 &v )
{
	out << "(" << v.x << "," << v.y << ")";
	return out;
}

//////////////////////////////////////////////////////////////////////////

vector2 operator*( int n,vector2 const &right )
{
	vector2 temp;
	temp.x = right.x*n;
	temp.y = right.y*n;

	return temp;
}
