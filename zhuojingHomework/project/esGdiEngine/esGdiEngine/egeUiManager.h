#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef EGEUIMANAGER
#define EGEUIMANAGER

//////////////////////////////////////////////////////////////////////////
//	UI管理类，负责统一维护UI控件的更新和渲染
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
class egeUiManager
#else
class _declspec( dllexport ) egeUiManager
#endif
{
public:
	egeUiManager(void);
	~egeUiManager(void);

	void wndProc( PESWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	void addUi( egeUiObject *ui );
	egeUiObject* getUiById( int id );

	void Update();
	void Render();

private:
	esGdiEngine *m_pEngine;

	std::list<egeUiObject *> m_uiObjectList;
	std::list<egeUiObject *>::iterator m_uiObjectListIter;
	std::list<egeUiObject *>::reverse_iterator m_uiObjectListRIter;
};

#endif //	END EGEUIMANAGER