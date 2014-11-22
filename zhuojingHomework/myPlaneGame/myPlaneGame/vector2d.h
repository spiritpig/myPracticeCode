#include "commonHeader.h"

#ifndef VECTOR2D_AFX
#define VECTOR2D_AFX

struct vector2d
{
public: 
	float x, y;

public:
	vector2d();
	vector2d( float x, float y );
	vector2d( const vector2d &other );

	vector2d operator+( const vector2d &other );
	vector2d operator-( const vector2d &other );
	vector2d operator*( float k );
	float operator*( const vector2d &other );

	vector2d& operator=( const vector2d &other );
	vector2d& operator+=( const vector2d &other );
	vector2d& operator-=( const vector2d &other );
	vector2d& operator*=( float k );

public:
	float length();
	vector2d  normalized();
	vector2d& normalizedSelf();
	vector2d  roration( float angle );
	vector2d& rotationSelf( float angle );

	friend std::ostream& operator<<( std::ostream &out, const vector2d &v );
};

vector2d operator*( float k, const vector2d &v );

#endif // END VECTOR2D_AFX