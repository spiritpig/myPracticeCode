#include "stdafx.h"

vector2::vector2()
{
	x = 0.0f;
	y = 0.0f;
}

vector2::vector2( float x,float y )
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

vector2 vector2::operator*( float n )
{
	vector2 temp;
	temp.x = this->x*n;
	temp.y = this->y*n;
	return temp;
}

float vector2::operator*( vector2 const &other )
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

vector2& vector2::operator*=( float n )
{
	this->x *= n;
	this->y *= n;

	return *this;
}

float vector2::Length()
{
	return sqrt( this->x*this->x + 
				 this->y*this->y );
}

vector2 vector2::normal()
{
	float l = this->Length();
	vector2 temp;
	if( isFloatEqualToZero( l ) )
	{
		temp.x = 0.0f;
		temp.y = 0.0f;
	}
	else
	{
		temp.x = this->x/l;
		temp.y = this->y/l;
	}

	return temp;
}

vector2& vector2::normalself()
{
	float l = this->Length();
	if( isFloatEqualToZero( l ) )
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x = this->x/l;
		this->y = this->y/l;
	}

	return *this;
}

vector2 vector2::rotation( float angle )
{
	vector2 temp;
	temp.x = this->x*cosf(angle) - this->y*sinf(angle);
	temp.y = this->x*sinf(angle) + this->y*cosf(angle);

	return temp;
}

vector2& vector2::rotationself( float angle )
{
	float tempX = this->x;

	this->x = this->x*cosf(angle) - this->y*sinf(angle);
	this->y = tempX*sinf(angle) + this->y*cosf(angle);

	return *this;
}

vector2::~vector2()
{

}

std::ostream& operator<<( std::ostream &out, const vector2 &v )
{
	out << "(" << v.x << "," << v.y << ")";
	return out;
}

//////////////////////////////////////////////////////////////////////////

vector2 operator*( float n,vector2 const &right )
{
	vector2 temp;
	temp.x = right.x*n;
	temp.y = right.y*n;

	return temp;
}
