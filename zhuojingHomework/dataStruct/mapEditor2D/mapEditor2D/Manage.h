#include "AllDefine.h"

#ifndef AFX_MANAGE
#define AFX_MANAGE

class Manage
{
public:
	Manage(void);
	void Init();
	bool Update();
	bool Render();
	~Manage(void);
private:
	void _ProcessInput();
private:
	Sgge *m_pSgge;
private:
	Map *m_pMap;
	POINT m_MousePos;
};

#endif
