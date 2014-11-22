#include "commonHeader.h"

#ifndef VECTOR2D
#define VECTOR2D

struct Vec2D
{
	Vec2D(void);
	Vec2D( float x, float y );

	Vec2D operator+( const Vec2D &other ) const;
	Vec2D operator-( const Vec2D &other ) const;
	Vec2D operator*( float k ) const; 
	float operator*( const Vec2D &other ) const;

	Vec2D& operator+=( const Vec2D &other );
	Vec2D& operator-=( const Vec2D &other );
	Vec2D& operator*=( float k ); 

	float length() const;
	Vec2D normalized() const;
	Vec2D& normalizedSelf();
	Vec2D rotation( float angle ) const;
	Vec2D& rotationSelf( float angle );

	float x, y;
};

Vec2D operator*( float k, const Vec2D &v );

#endif	// END VECTOR2D
