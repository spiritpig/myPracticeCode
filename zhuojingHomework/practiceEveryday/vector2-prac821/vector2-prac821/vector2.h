#ifndef VECTOR2_AFX
#define VECTOR2_AFX

struct vector2
{
	float x,y;

public:
	vector2(void);
	vector2( float x, float y );
	vector2( const vector2 &other );

	vector2 operator+( const vector2 &other );
	vector2 operator-( const vector2 &other );
	vector2 operator*( float k );
	float operator*( const vector2 &other );

	vector2& operator=( const vector2 &other );
	vector2& operator+=( const vector2 &other );
	vector2& operator-=( const vector2 &other );
	vector2& operator*=( float k );

	float length(); 
	vector2 normalized();
	vector2& normalizedSelf();
	vector2 rotation( float angle );
	vector2& rotationSelf( float angle );

	friend std::ostream& operator<<( std::ostream &out, const vector2 &v );
};

vector2 operator*( float k, const vector2 &v );

#endif // END VECTOR2_AFX