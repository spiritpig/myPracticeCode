#include ".\manage.h"

Manage::Manage(void)
{
	m_pSgge=SggeCreate(SGGE_VERSION);
	m_pMap=NULL;
}

Manage::~Manage(void)
{
	SAFE_DELETE(m_pMap);
	m_pSgge->Release();
}

void Manage::Init()
{
	SAFE_DELETE(m_pMap);
	m_pMap=new Map;
	m_pMap->Init();
}

bool Manage::Update()
{
	_ProcessInput();

	m_pMap->Update();
	return false;
}

bool Manage::Render()
{
	if(m_pSgge->Render_Begin())
	{
		m_pSgge->Render_Clear(0xff808080);

		//////////////////////////////////
		m_pMap->Render();
		//////////////////////////////////

		m_pSgge->Render_End();
		return true;
	}
	else
	{
		return false;
	}
}

void Manage::_ProcessInput()
{

}
