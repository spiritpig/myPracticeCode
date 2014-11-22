#include ".\Vector2D.h"

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

Vec2D::Vec2D(void)
{
	x = 0.0f;
	y = 0.0f;
}

Vec2D::Vec2D( float x, float y )
{
	this->x = x;
	this->y = y;
}

Vec2D Vec2D::operator+( const Vec2D &other ) const
{
	return Vec2D( this->x+other.x, this->y+other.y );
}

Vec2D Vec2D::operator-( const Vec2D &other ) const
{
	return Vec2D( this->x-other.x, this->y-other.y );
}

Vec2D Vec2D::operator*( float k ) const
{
	return Vec2D( x*k, y*k );
}

float Vec2D::operator*( const Vec2D &other ) const
{
	return (this->x*other.x + this->y*other.y);
}

Vec2D& Vec2D::operator+=( const Vec2D &other )
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vec2D& Vec2D::operator-=( const Vec2D &other )
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

Vec2D& Vec2D::operator*=( float k )
{
	this->x *= k;
	this->y *= k;

	return *this;
}

float Vec2D::length() const
{
	return sqrt( this->x*this->x + this->y*this->y );
}

Vec2D Vec2D::normalized() const
{
	float len = this->length();
	
	if( isFloatEqualToZero( len ) )
	{
		return Vec2D( 0.0f, 0.0f );
	}
	else
	{
		return Vec2D( this->x/len, this->y/len );
	}
}

Vec2D& Vec2D::normalizedSelf()
{
	float len = this->length();

	if( !isFloatEqualToZero( len ) )
	{
		this->x /= len;
		this->y /= len;
	}

	return *this;
}

Vec2D Vec2D::rotation( float angle ) const
{
	return Vec2D( this->x*cosf(angle) - this->y*sinf(angle),
					this->x*sinf(angle) + this->y*cosf(angle) );
}

Vec2D& Vec2D::rotationSelf( float angle )
{
	float tempX = this->x;
	this->x = this->x*cosf(angle) - this->y*sinf(angle);
	this->y = tempX*sinf(angle) + this->y*cosf(angle);

	return *this;
}

Vec2D operator*( float k, const Vec2D &v )
{
	return Vec2D( v.x*k, v.y*k );
}