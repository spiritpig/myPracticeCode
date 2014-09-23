#include "stdafx.h"

vector2d::vector2d()
{
	x = 0.0f;
	y = 0.0f;
}

vector2d::vector2d( float x, float y )
{
	this->x = x;
	this->y = y;
}

vector2d vector2d::operator+( const vector2d &other )
{
	vector2d temp;
	temp.x = this->x + other.x;
	temp.y = this->y + other.y;

	return temp;
}

vector2d vector2d::operator-( const vector2d &other )
{
	vector2d temp;
	temp.x = this->x - other.x;
	temp.y = this->y - other.y;

	return temp;
}

vector2d vector2d::operator*( float n )
{
	vector2d temp;
	temp.x = this->x*n;
	temp.y = this->y*n;

	return temp;
}

float vector2d::operator*( const vector2d &other )
{
	return this->x*other.x 
		 + this->y*other.y;
}

vector2d& vector2d::operator=( const vector2d &other )
{
	this->x = other.x;
	this->y = other.y;

	return *this;
}

vector2d& vector2d::operator+=( const vector2d &other )
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

vector2d& vector2d::operator-=( const vector2d &other )
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

vector2d& vector2d::operator*=( float n )
{
	this->x = this->x*n;
	this->y = this->y*n;

	return *this;
}


float vector2d::length()
{
	return sqrt( this->x*this->x + this->y*this->y );
}

vector2d vector2d::normalized()
{
	float len = this->length();

	vector2d temp;
	temp.x = this->x/len;
	temp.y = this->y/len;

	return temp;
}

vector2d& vector2d::normalizedSelf()
{
	float len = this->length();

	this->x = this->x/len;
	this->y = this->y/len;

	return *this;
}

vector2d vector2d::rotation( float angle )
{
	vector2d temp;
	temp.x = this->x*cosf(angle) - this->y*sinf(angle);
	temp.y = this->x*sinf(angle) + this->y*cosf(angle);

	return temp;
}

vector2d& vector2d::rotationSelf( float angle )
{
	float tempX = this->x;

	this->x = this->x*cosf(angle) - this->y*sinf(angle);
	this->y = tempX*sinf(angle) + this->y*cosf(angle);

	return *this;
}

std::ostream& operator<<( std::ostream &out, const vector2d &v )
{
	out << "(" << v.x << "," << v.y << ")";
	return out;
}

//////////////////////////////////////////////////////////////////////////
vector2d operator*( float n, const vector2d &v )
{
	vector2d temp;
	temp.x = v.x*n;
	temp.y = v.y*n;

	return temp;
}
