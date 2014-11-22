#include ".\egeuimanager.h"

egeUiManager::egeUiManager(void)
{
	m_pEngine = Engine_Create( NULL );
	m_uiObjectList.clear();
}

egeUiManager::~egeUiManager(void)
{
	if( !m_uiObjectList.empty() )
	{
		for ( m_uiObjectListIter = m_uiObjectList.begin();
			m_uiObjectListIter != m_uiObjectList.end(); 
			++m_uiObjectListIter)
		{
			SAFE_DELETE( (*m_uiObjectListIter) );
		}

		m_uiObjectList.clear();
	}

	Engine_Release();
}

void egeUiManager::wndProc( PESWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if ( !m_uiObjectList.empty() && (*m_uiObjectList.begin())->m_UIType == UT_EDIT )
	{
		(*m_uiObjectList.begin())->wndProc( hWnd, message, wParam, lParam );
	}
}

void egeUiManager::addUi( egeUiObject *ui )
{
	if ( !m_uiObjectList.empty() )
	{
		(*m_uiObjectList.begin())->KillFocus();
	}
	ui->SetFocus();
	m_uiObjectList.push_front( ui );
}

egeUiObject* egeUiManager::getUiById( int id )
{
	egeUiObject *tempRet = NULL;
	if( !m_uiObjectList.empty() )
	{
		for ( m_uiObjectListIter = m_uiObjectList.begin(); 
			m_uiObjectListIter != m_uiObjectList.end();
			++m_uiObjectListIter )
		{
			if ( (*m_uiObjectListIter)->GetId() == id )
			{
				return *m_uiObjectListIter;
			}
			else
			{
				tempRet = (*m_uiObjectListIter)->getChildUiById( id );
				if ( tempRet != NULL )
				{
					return tempRet;
				}
			}
		}
	}
	
	return NULL;
}

void egeUiManager::Update()
{
	if( !m_uiObjectList.empty() )
	{
		if ( m_pEngine->KeyDown( VK_LBUTTON ) )
		{
			// 将获取焦点的元素放到最顶层
			for ( m_uiObjectListIter = m_uiObjectList.begin();
				m_uiObjectListIter != m_uiObjectList.end();
				++m_uiObjectListIter )
			{
				if( (*m_uiObjectListIter)->isMouseIntersectObject() )
				{
					egeUiObject *pCtrl = *m_uiObjectListIter;
					(*m_uiObjectList.begin())->KillFocus();
					m_uiObjectList.erase( m_uiObjectListIter );
					m_uiObjectList.push_front( pCtrl );

					(*m_uiObjectList.begin())->SetFocus();
					break;
				}
			}
		}

		(*m_uiObjectList.begin())->Update();
		(*m_uiObjectList.begin())->UpdateChild();
	}
}

void egeUiManager::Render()
{
	if( !m_uiObjectList.empty() )
	{
		for (  m_uiObjectListRIter = m_uiObjectList.rbegin(); 
			m_uiObjectListRIter != m_uiObjectList.rend();
			++m_uiObjectListRIter )
		{
			// 孩子和父亲的绘制顺序交给UiManager调控
			if( (*m_uiObjectListRIter)->IsFocus() )
			{
				(*m_uiObjectListRIter)->RenderAllChild();
				(*m_uiObjectListRIter)->Render();
			}
			else
			{
				(*m_uiObjectListRIter)->Render();
				(*m_uiObjectListRIter)->RenderAllChild();
			}
		}
	}
}


