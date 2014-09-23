#include "stdafx.h"

#ifndef AFX_VECTOR2
#define AFX_VECTOR2

struct vector2
{
	float x,y;
	vector2();
	vector2(float x,float y);
	vector2(vector2 const &other);
	vector2& operator =(vector2 const &other);
	vector2 operator +(vector2 const &other);
	vector2 operator -(vector2 const &other);
	vector2 operator *(float n);
	float operator *(vector2 const &other);
	vector2& operator +=(vector2 const &other);
	vector2& operator -=(vector2 const &other);
	vector2& operator *=(float n);
	float Length();
	vector2 normal();
	vector2& normalself();
	vector2 rotation(float angle);
	vector2& rotationself(float angle);

	friend std::ostream& operator<<( std::ostream &out, const vector2 &v );
	~vector2();
};

vector2 operator *(float n,vector2 const &right);

#endif