#include "AllDefine.h"

#ifndef IOBJECT
#define IOBJECT

class BaseObject
{
public:
	BaseObject( PTEXTURE tex, bool isMask, COLORREF maskColor );
	~BaseObject();

	//////////////////////////////////////////////////////////////////////////
	//	getter/setter
	//////////////////////////////////////////////////////////////////////////
	virtual void setPos( const egeVec2D &newPos );
	virtual void setVec( const egeVec2D &newVec );
	virtual void setAccer( const egeVec2D &newAccer );
	virtual void setResistance( float res );
	virtual void setBorderRange( int left, int top, int right, int bottom );

	virtual const egeVec2D& getPos() const;
	virtual const egeVec2D& getVec() const;
	virtual const egeVec2D& getAccer() const;
	// 阻力系数m_Resistance的运算尚有问题，设置为1.0f
	virtual float getResistance() const;
	virtual const RECT& getBorderRange() const;

	bool isHitObject( BaseObject *bo );
	virtual void onHitObject( BaseObject *bo );
	BOOL isHitBorder();
	virtual void onHitBorder();


	//////////////////////////////////////////////////////////////////////////
	//	虚函数
	//////////////////////////////////////////////////////////////////////////
	virtual void Init() = 0;
	virtual void Update();
	virtual void Render();

protected:
	esGdiEngine *pEngine;
	egeSprite *m_Spr;

	float m_Resistance;
	egeVec2D m_Pos;
	egeVec2D m_Vec;
	egeVec2D m_Accer;
	RECT m_BorderRange;
	RECT m_OuterRect;
};

#endif	// END IOBJECT
