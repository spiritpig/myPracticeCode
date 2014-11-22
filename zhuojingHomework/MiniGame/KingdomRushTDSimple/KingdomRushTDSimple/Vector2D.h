#include "commonHeader.h"

#ifndef VECTOR2D
#define VECTOR2D

struct Vector2D
{
	Vector2D(void);
	Vector2D( float x, float y );

	Vector2D operator+( const Vector2D &other ) const;
	Vector2D operator-( const Vector2D &other ) const;
	Vector2D operator*( float k ) const; 
	float operator*( const Vector2D &other ) const;

	Vector2D& operator+=( const Vector2D &other );
	Vector2D& operator-=( const Vector2D &other );
	Vector2D& operator*=( float k ); 

	float length() const;
	Vector2D normalized() const;
	Vector2D& normalizedSelf();
	Vector2D rotation( float angle ) const;
	Vector2D& rotationSelf( float angle );

	float x, y;
};

Vector2D operator*( float k, const Vector2D &v );

#endif	// END VECTOR2D
