#include "stdafx.h"

vector2::vector2(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
}

vector2::vector2( float x, float y )
{
	this->x = x;
	this->y = y;
}

vector2::vector2( const vector2 &other )
{
	this->x = other.x;
	this->y = other.y;
}

vector2 vector2::operator+( const vector2 &other )
{
	vector2 temp;
	temp.x = this->x + other.x;
	temp.y = this->y + other.y;

	return temp;
}

vector2 vector2::operator-( const vector2 &other )
{
	vector2 temp;
	temp.x = this->x - other.x;
	temp.y = this->y - other.y;

	return temp;
}

vector2 vector2::operator*( float k )
{
	vector2 temp;
	temp.x = this->x*k;
	temp.y = this->y*k;

	return temp;
}

float vector2::operator*( const vector2 &other )
{
	return this->x*other.x + this->y*other.y;
}

vector2& vector2::operator=( const vector2 &other )
{
	this->x = other.x;
	this->y = other.y;

	return *this;
}

vector2& vector2::operator+=( const vector2 &other )
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

vector2& vector2::operator-=( const vector2 &other )
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}
vector2& vector2::operator*=( float k )
{
	this->x *= k;
	this->y *= k;

	return *this;
}

float vector2::length()
{
	return sqrt( this->x*this->x + this->y*this->y );
}

vector2 vector2::normalized()
{
	float l = length();

	vector2 temp;
	if( (l < 0.00001f) &&
		(l > -0.00001f) )
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
vector2& vector2::normalizedSelf()
{
	float l = length();
	if( (l < 0.00001f) &&
		(l > -0.00001f) )
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= l;
		this->y /= l;
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

vector2& vector2::rotationSelf( float angle )
{
	float tempX = this->x;

	this->x = this->x*cosf(angle) - this->y*sinf(angle);
	this->y = tempX*sinf(angle) + this->y*cosf(angle);

	return *this;
}

std::ostream& operator<<( std::ostream &out, const vector2 &v )
{
	out << "(" << v.x << "," << v.y << ")";
	return out;
}

vector2 operator*( float k, const vector2 &v )
{
	vector2 temp;
	temp.x = v.x*k;
	temp.y = v.y*k;

	return temp;
}