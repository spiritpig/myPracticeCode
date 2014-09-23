#define DLL_EXPORT

#include <math.h>
#include <cstdio>
#include "vector2d.h"

#define FLOAT_COMPARE_PRECISION 0.00001f
static bool isFloatEqualToZero( float f )
{
	return ( f < FLOAT_COMPARE_PRECISION ) &&
			( f > -FLOAT_COMPARE_PRECISION );
}

vector2d::vector2d(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
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

vector2d vector2d::operator +( const vector2d &other ) const
{
	return vector2d( this->x+other.x, this->y+other.y );
}

vector2d vector2d::operator -( const vector2d &other ) const
{
	return vector2d( this->x-other.x, this->y-other.y );
}

vector2d vector2d::operator *( float k ) const
{
	return vector2d( this->x*k, this->y*k );
}

float vector2d::operator *( const vector2d &other ) const
{
	return this->x*other.x + this->y*other.y;
}

vector2d& vector2d::operator +=( const vector2d &other )
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

vector2d& vector2d::operator -=( const vector2d &other )
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

vector2d& vector2d::operator *=( float k )
{
	this->x *= k;
	this->y *= k;

	return *this;
}

vector2d& vector2d::operator =( const vector2d &other )
{
	this->x = other.x;
	this->y = other.y;

	return *this;
}

float vector2d::length() const
{
	return sqrt( this->x*this->x + this->y*this->y );
}

vector2d vector2d::normalized() const
{
	float l = length();
	if( isFloatEqualToZero( l ) )
	{
		return vector2d( 0.0f, 0.0f );
	}
	else
	{
		return vector2d( this->x/l, this->y/l );
	}
}

vector2d& vector2d::normalizedSelf()
{
	float l = length();
	if( isFloatEqualToZero( l ) )
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

vector2d vector2d::rotation( float angle ) const
{
	return vector2d( this->x*cosf(angle) - this->y*sinf(angle),
					 this->x*sinf(angle) + this->y*cosf(angle) );
}

vector2d& vector2d::rotationSelf( float angle )
{
	float tempX = this->x;
	this->x = this->x*cosf(angle) - this->y*sinf(angle);
	this->y = tempX*sinf(angle)   + this->y*cosf(angle);

	return *this;
}

vector2d operator *( float k, const vector2d &v )
{
	return vector2d( v.x*k, v.y*k );
}

DllOp void outputVector2( const vector2d &v )
{
	printf( "(%.2f,%.2f)", v.x, v.y );
}
