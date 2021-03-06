/*
	描述： vector2，二维向量类
		  保留了需要的基本操作

	日期： 2014.08.14

	作者： pinkbeen
 */
#include "stdafx.h"

#ifndef AFX_VECTOR2
#define AFX_VECTOR2

struct vector2
{
	int x,y;
	vector2();
	vector2(int x,int y);
	vector2(vector2 const &other);
	vector2& operator =(vector2 const &other);
	vector2 operator +(vector2 const &other);
	vector2 operator -(vector2 const &other);
	vector2 operator *(int n);
	int operator *(vector2 const &other);
	vector2& operator +=(vector2 const &other);
	vector2& operator -=(vector2 const &other);
	vector2& operator *=(int n);
	float Length();
	bool operator==(const vector2 &other); 

	friend std::ostream& operator<<( std::ostream &out, const vector2 &v );
};

vector2 operator *(int n,vector2 const &right);

#endif