#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef EGEUISCROLLBAR
#define EGEUISCROLLBAR

//////////////////////////////////////////////////////////////////////////
//	Edit�ؼ����������߿��һ������ͼƬ���
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
class egeUiScrollBar : public egeUiObject
#else
class _declspec( dllexport ) egeUiScrollBar : public egeUiObject
#endif
{
public:
	egeUiScrollBar( char *pName, int id, int x, int y, int width, int height,
					float scrollPercentPerClick, egeUiObject *pParent = NULL );
	virtual ~egeUiScrollBar(void);

	float getRate()
	{
		return m_rate;
	}

	virtual void Update();
	virtual void Render();

private:
	egeUiButton *m_LeftBtn, *m_RightBtn, *m_ScrollBtn;
	egeSprite	*m_bgSprite;

	int m_scrollMoveLen;
	int m_scrollMoveStartX;
	float m_scrollPercentPerClick;
	float m_rate;
};

#endif	// END EGEUISCROLLBAR