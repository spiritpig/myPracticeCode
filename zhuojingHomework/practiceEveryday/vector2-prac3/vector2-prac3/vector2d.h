#ifndef VECTOR2D_AFX
#define VECTOR2D_AFX

struct vector2d
{
public:
	float x,y;

public:
	vector2d();
	vector2d(float x, float y);
	vector2d( const vector2d &other );
	~vector2d(void);

	float length();

	vector2d operator+( const vector2d &other );
	vector2d operator-( const vector2d &other );
	vector2d operator*( float k );
	float	 operator*( const vector2d &other );
	vector2d normalized();
	vector2d rotation( float angle );

	vector2d& operator=( const vector2d &other );
	vector2d& operator+=( const vector2d &other );
	vector2d& operator-=( const vector2d &other );
	vector2d& operator*=( float k );
	vector2d& normalizedSelf();
	vector2d& rotationSelf( float angle );

	friend std::ostream& operator<<( std::ostream &out, const vector2d &v );
};

vector2d operator*( float k, const vector2d &v );

#endif // END VECTOR2D_AFX