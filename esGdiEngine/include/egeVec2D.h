#pragma once
#include "esgdiengineall.h"

struct egeVec2D
{
	egeVec2D(void);
	egeVec2D( float x, float y );

	egeVec2D operator+( const egeVec2D &other ) const;
	egeVec2D operator-( const egeVec2D &other ) const;
	egeVec2D operator*( float k ) const; 
	float operator*( const egeVec2D &other ) const;

	egeVec2D& operator+=( const egeVec2D &other );
	egeVec2D& operator-=( const egeVec2D &other );
	egeVec2D& operator*=( float k ); 

	float length() const;
	egeVec2D normalized() const;
	egeVec2D& normalizedSelf();
	egeVec2D rotation( float angle ) const;
	egeVec2D& rotationSelf( float angle );

	float x, y;
};

egeVec2D operator*( float k, const egeVec2D &v );

