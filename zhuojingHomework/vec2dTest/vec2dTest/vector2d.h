#include <iostream>
#include <math.h>

#ifndef VECTOR2D
#define VECTOR2D

struct vector2d
{
	float x, y;

public:
	vector2d();
	vector2d( float x, float y );
	vector2d( const vector2d &other );

	vector2d operator +( const vector2d &other ) const;
	vector2d operator -( const vector2d &other ) const;
	vector2d operator *( float k ) const;
	float operator *( const vector2d &other ) const;

	vector2d& operator +=( const vector2d &other );
	vector2d& operator -=( const vector2d &other );
	vector2d& operator *=( float k );
	vector2d& operator  =( const vector2d &other );

	float length() const;
	vector2d normalized() const;
	vector2d& normalizedSelf();
	vector2d rotation( float angle ) const;
	vector2d& rotationSelf( float angle );

	friend std::ostream& operator <<( std::ostream &out, const vector2d &v );
};

vector2d operator *( float k, const vector2d &v );

#endif // END VECTOR2D