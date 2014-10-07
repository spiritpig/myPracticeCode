#include "commonHeader.h"

#define FLOAT_COMPARE_PRECISION 0.00001f

static bool isFloatEqualToZero( float f )
{
	return ( f < FLOAT_COMPARE_PRECISION ) &&
		   ( f > -FLOAT_COMPARE_PRECISION );
}

vector2::vector2()
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

vector2 vector2::operator +( const vector2 &other ) const
{
	return vector2( this->x+other.x, this->y+other.y );
}

vector2 vector2::operator -( const vector2 &other ) const
{
	return vector2( this->x-other.x, this->y-other.y );;
}

float vector2::operator *( const vector2 &other ) const
{
	return (this->x*other.x + this->y*other.y);
}

vector2 vector2::operator *( float k ) const
{
	return vector2( this->x*k, this->y*k );;
}

vector2& vector2::operator +=( const vector2 &other )
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

vector2& vector2::operator -=( const vector2 &other )
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

vector2& vector2::operator *=( float k )
{
	this->x *= k;
	this->y *= k;

	return *this;
}

vector2& vector2::operator=( const vector2 &other )
{
	this->x = other.x;
	this->y = other.y;

	return *this;
}

float vector2::length() const
{
	return sqrt( this->x*this->x + this->y*this->y );
}

vector2 vector2::normalized() const
{
	float l = length();
	if( isFloatEqualToZero( l ) )
	{
		return vector2( 0.0f, 0.0f );
	}
	else
	{
		return vector2( this->x/l, this->y/l );
	}
}

vector2& vector2::normalizedSelf()
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

vector2 vector2::rotation( float angle ) const
{
	return vector2( this->x*cosf(angle) - this->y*sinf(angle),
					this->x*sinf(angle) + this->y*cosf(angle) );
}

vector2& vector2::rotationSelf( float angle )
{
	float tempX = this->x;
	this->x = this->x*cosf(angle) - this->y*sinf(angle);
	this->y = tempX*sinf(angle)   + this->y*cosf(angle);

	return *this;
}

std::ostream& operator<<( std::ostream &out, const vector2 &v )
{
	out << "(" << v.x << "," << v.y << ")";
	return out;
}

vector2 operator*( float k, const vector2 &v )
{
	return vector2( v.x*k, v.y*k );
}
