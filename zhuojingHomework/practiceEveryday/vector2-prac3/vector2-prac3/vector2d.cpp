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

vector2d::vector2d( const vector2d &other )
{
	this->x = other.x;
	this->y = other.y;
}

vector2d::~vector2d(void)
{
}

float vector2d::length()
{
	return sqrt(this->x*this->x + this->y*this->y);
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

vector2d vector2d::operator*( float k )
{
	vector2d temp;
	temp.x = this->x*k;
	temp.y = this->y*k;

	return temp;
}

float vector2d::operator*( const vector2d &other )
{
	return this->x*other.x + this->y*other.y;
}

vector2d vector2d::normalized()
{
	float l = length();

	vector2d temp;
	temp.x = this->x/l;
	temp.y = this->y/l;

	return temp;
}


vector2d vector2d::rotation( float angle )
{
	vector2d temp;
	temp.x = this->x*cosf(angle) - this->y*sinf(angle);
	temp.y = this->x*sinf(angle) + this->y*cosf(angle);

	return temp;
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

vector2d& vector2d::operator*=( float k )
{
	this->x *= k;
	this->y *= k;

	return *this;
}

vector2d& vector2d::normalizedSelf()
{
	float l = length();

	this->x = this->x/l;
	this->y = this->y/l;

	return *this;
}

vector2d& vector2d::rotationSelf( float angle )
{
	float tempX = this->x;

	this->x = this->x*cosf(angle) - this->y*sinf(angle);
	this->y = tempX*sinf(angle) + this->y*cosf(angle);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
std::ostream& operator<<( std::ostream &out, const vector2d &v )
{
	out << "(" << v.x << "," << v.y << ")";
	return out;
}

//////////////////////////////////////////////////////////////////////////
vector2d operator*( float k, const vector2d &v )
{
	vector2d temp;
	temp.x = v.x*k;
	temp.y = v.y*k;

	return temp;
}