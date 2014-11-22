#include ".\egevec2d.h"

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

egeVec2D::egeVec2D(void)
{
	x = 0.0f;
	y = 0.0f;
}

egeVec2D::egeVec2D( float x, float y )
{
	this->x = x;
	this->y = y;
}

egeVec2D egeVec2D::operator+( const egeVec2D &other ) const
{
	return egeVec2D( this->x+other.x, this->y+other.y );
}

egeVec2D egeVec2D::operator-( const egeVec2D &other ) const
{
	return egeVec2D( this->x-other.x, this->y-other.y );
}

egeVec2D egeVec2D::operator*( float k ) const
{
	return egeVec2D( x*k, y*k );
}

float egeVec2D::operator*( const egeVec2D &other ) const
{
	return (this->x*other.x + this->y*other.y);
}

egeVec2D& egeVec2D::operator+=( const egeVec2D &other )
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

egeVec2D& egeVec2D::operator-=( const egeVec2D &other )
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

egeVec2D& egeVec2D::operator*=( float k )
{
	this->x *= k;
	this->y *= k;

	return *this;
}

float egeVec2D::length() const
{
	return sqrt( this->x*this->x + this->y*this->y );
}

egeVec2D egeVec2D::normalized() const
{
	float len = this->length();
	
	if( isFloatEqualToZero( len ) )
	{
		return egeVec2D( 0.0f, 0.0f );
	}
	else
	{
		return egeVec2D( this->x/len, this->y/len );
	}
}

egeVec2D& egeVec2D::normalizedSelf()
{
	float len = this->length();

	if( !isFloatEqualToZero( len ) )
	{
		this->x /= len;
		this->y /= len;
	}

	return *this;
}

egeVec2D egeVec2D::rotation( float angle ) const
{
	return egeVec2D( this->x*cosf(angle) - this->y*sinf(angle),
					this->x*sinf(angle) + this->y*cosf(angle) );
}

egeVec2D& egeVec2D::rotationSelf( float angle )
{
	float tempX = this->x;
	this->x = this->x*cosf(angle) - this->y*sinf(angle);
	this->y = tempX*sinf(angle) + this->y*cosf(angle);

	return *this;
}

egeVec2D operator*( float k, const egeVec2D &v )
{
	return egeVec2D( v.x*k, v.y*k );
}