#include "stdafx.h"

// 判断浮点数是否等于0
#define FLOAT_COMPARE_PRECISION 0.00001f
static bool isFloatEqualToZero( float f )
{
	if( (f <= FLOAT_COMPARE_PRECISION) &&
		(f >= -FLOAT_COMPARE_PRECISION) )
	{
		return true;
	}

	return false;
}

Vector2D::Vector2D(void)
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D( float x, float y )
{
	this->x = x;
	this->y = y;
}

Vector2D Vector2D::operator+( const Vector2D &other ) const
{
	return Vector2D( this->x+other.x, this->y+other.y );
}

Vector2D Vector2D::operator-( const Vector2D &other ) const
{
	return Vector2D( this->x-other.x, this->y-other.y );
}

Vector2D Vector2D::operator*( float k ) const
{
	return Vector2D( x*k, y*k );
}

float Vector2D::operator*( const Vector2D &other ) const
{
	return (this->x*other.x + this->y*other.y);
}

Vector2D& Vector2D::operator+=( const Vector2D &other )
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vector2D& Vector2D::operator-=( const Vector2D &other )
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

Vector2D& Vector2D::operator*=( float k )
{
	this->x *= k;
	this->y *= k;

	return *this;
}

float Vector2D::length() const
{
	return sqrt( this->x*this->x + this->y*this->y );
}

Vector2D Vector2D::normalized() const
{
	float len = this->length();
	
	if( isFloatEqualToZero( len ) )
	{
		return Vector2D( 0.0f, 0.0f );
	}
	else
	{
		return Vector2D( this->x/len, this->y/len );
	}
}

Vector2D& Vector2D::normalizedSelf()
{
	float len = this->length();

	if( !isFloatEqualToZero( len ) )
	{
		this->x /= len;
		this->y /= len;
	}

	return *this;
}

Vector2D Vector2D::rotation( float angle ) const
{
	return Vector2D( this->x*cosf(angle) - this->y*sinf(angle),
					this->x*sinf(angle) + this->y*cosf(angle) );
}

Vector2D& Vector2D::rotationSelf( float angle )
{
	float tempX = this->x;
	this->x = this->x*cosf(angle) - this->y*sinf(angle);
	this->y = tempX*sinf(angle) + this->y*cosf(angle);

	return *this;
}

Vector2D operator*( float k, const Vector2D &v )
{
	return Vector2D( v.x*k, v.y*k );
}