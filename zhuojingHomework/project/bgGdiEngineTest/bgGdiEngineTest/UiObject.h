#include "EingeDefine.h"

#ifndef AFX_UIOBJECT
#define AFX_UIOBJECT

#ifdef _DEBUG
class UiObject
#else
class __declspec(dllexport) UiObject
#endif
{
public:
	UiObject(DWORD Id,char const * const pName,UiType Type,UiManage *pUiManage,UiObject *pParent=NULL);
	virtual void SetPos(POINT const &pos);
	virtual void SetRect(RECT const &rect);
	virtual void SetHotSpot(float ratex,float ratey);
	virtual void SetVisble(bool IsVisble);
	virtual void SetName(char const * const pName);
	virtual UiObject* GetParent();
	virtual POINT const & GetPos();
	virtual POINT const & GetSelfPos();
	virtual RECT const &GetRect();
	virtual DWORD GetId();
	virtual bool GetIsVisble();
	virtual char const * const GetName();
	virtual UiType GetType();
	virtual bool IsInterscert(POINT const &pt);
	virtual void AddChild(UiObject *pUiObject);
	virtual bool ReMoveChild(UiObject *pUiObject);
	virtual void ReMoveChild(DWORD Id);
	virtual void ReMoveAllChild();
	virtual UiObject* FindChild(DWORD Id,int sit=0);
	virtual void SetFocus();
	virtual void KillFocus();

	virtual void UpdateFromParent();
	virtual void Update()=0;
	virtual void Render()=0;
	virtual void RenderChild();
	virtual ~UiObject(void);
protected:
	GdiEinge *m_pGdiEinge;
	UiManage *m_pUiManage;
	POINT m_Pos;
	POINT m_SelfPos;
	POINT m_Hotspot;
	float m_HotspotRateX;
	float m_HotspotRateY;
	RECT m_UiRect;
	DWORD m_Id;
	char *m_pName;
	UiType m_Type;
	bool m_IsVisble;
	UiObject *m_pParent;
	bool m_HaveFocus;
	vector<UiObject *> m_pChild;
	vector<UiObject *>::iterator m_pChildPt;
};

#endif