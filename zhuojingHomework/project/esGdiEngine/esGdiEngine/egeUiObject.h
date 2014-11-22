#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef EGEUIOBJECT
#define EGEUIOBJECT

#ifdef _DEBUG
class egeUiObject
#else
class _declspec( dllexport ) egeUiObject
#endif
{
public:
	egeUiObject( char *pName, int id, UI_TYPE uType, 
				int x, int y, egeUiObject *pParent = NULL );
	virtual ~egeUiObject(void);


	//////////////////////////////////////////////////////////////////////////
	//	设置获取参数 类函数
	//////////////////////////////////////////////////////////////////////////
	virtual egePoint& GetRealPos()
	{
		return m_RealPos;
	}
	virtual int GetId()
	{
		return m_Id;
	}
	virtual egeUiObject* getChildUiById( int id );
	virtual char* GetText()
	{
		return m_pName;
	}
	virtual void SetText( const char *text );
	virtual void SetPos( int x, int y );
	void SetHotSpot( float ratex, float ratey );
	virtual void SetParent( egeUiObject * pParent )
	{
		m_pParent = pParent;
		SetPos( m_Pos.x, m_Pos.y );
	}
	void SetFocus()
	{
		isFocus = true;
	}

	void KillFocus()
	{
		isFocus = false;
	}
	bool IsFocus()
	{
		return isFocus;
	}

	void AddChild( egeUiObject *child );
	virtual void wndProc( PESWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {}
	virtual bool isMouseIntersectObject();

	void* operator new( size_t size );
	void* operator new[]( size_t size );
	void operator delete( void* p );
	void operator delete[]( void* p );

	//////////////////////////////////////////////////////////////////////////
	//	孩子的更新及初始化交友UiManager管理，此处只负责定义该行为
	//////////////////////////////////////////////////////////////////////////
	virtual void UpdateChild();
	virtual void Update() = 0;
	virtual void UpdateFromParent();
	virtual void Render() = 0;
	virtual void RenderAllChild();

protected:
	friend egeUiManager;

	esGdiEngine *m_pEngine;

	int m_Id;
	char *m_pName;
	size_t m_NameCapacity;
	UI_TYPE m_UIType;
	egePoint m_RealPos, m_Pos;
	float m_HotSpotRateX, m_HotSpotRateY;
	// 外围大矩形
	RECT m_OuterRect;
	bool isFocus;

	egeUiObject *m_pParent;
	vector<egeUiObject *> m_pChildList;
	vector<egeUiObject *>::iterator m_pChildListIter;
};
 
#endif	// END EGEUIOBJECT