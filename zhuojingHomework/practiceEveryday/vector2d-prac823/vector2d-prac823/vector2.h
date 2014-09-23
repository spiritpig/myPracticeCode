#ifndef VECTOR2
#define VECTOR2

struct vector2
{
	float x,y;

public:
	vector2(void);
	vector2( float x, float y );
	vector2( const vector2 &other );

	vector2 operator+( const vector2 &other ) const;
	vector2 operator-( const vector2 &other ) const;
	vector2 operator*( float k ) const;
	float operator*( const vector2 &other ) const;

	vector2& operator=( const vector2 &other );
	vector2& operator+=( const vector2 &other );
	vector2& operator-=( const vector2 &other );
	vector2& operator*=( float k );

	float length() const;
	vector2 rotation( float angle ) const;
	vector2 normalized() const;
	vector2& rotationSelf( float angle );
	vector2& normalizedSelf();

	friend std::ostream& operator<<( std::ostream &out, const vector2 &v );
};

vector2 operator*( float k, const vector2 &v );

#endif // VECTOR2
