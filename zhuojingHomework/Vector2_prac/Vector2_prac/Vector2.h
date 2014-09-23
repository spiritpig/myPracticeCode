#include "stdafx.h"

#ifndef VECTOR_AFX
#define VECTOR_AFX

struct vector2d
{
	float x,y;

public:
	vector2d();
	vector2d( float x, float y );
	vector2d operator+( const vector2d &other );
	vector2d operator-( const vector2d &other );
	vector2d operator*( float n );
	float operator*( const vector2d &other );
	vector2d& operator=( const vector2d &other ); 
	vector2d& operator+=( const vector2d &other ); 
	vector2d& operator-=( const vector2d &other ); 
	vector2d& operator*=( float n );

	float length();
	vector2d  normalized();
	vector2d& normalizedSelf();
	vector2d  rotation( float angle );
	vector2d& rotationSelf( float angle );

	friend std::ostream& operator<<( std::ostream &out, const vector2d &v );
};

vector2d operator*( float n, const vector2d &v );

#endif // END VECTOR_AFX