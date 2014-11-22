#include <Windows.h>
#include "cstdarg"
#include <list>
#include <deque>
using namespace std;

#define TRANSPENT

#ifndef AFX_ALLDEFINE
#define AFX_ALLDEFINE

#define GUI_BUTTON                       1
#define GUI_STATICTEXT                 2
#define GUI_EDIT                              3
#define GUI_DAILOGBOX                 4

#define GUIMSG_BTNCLIKE           1
#define GUIMSG_EDITCHANGE     2

struct GuiMsg
{
	UINT guimsg;
	UINT Param1;
	UINT Param2;
};

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p!=NULL) {delete p;p=NULL;}}
#endif

#ifndef SAFE_DELARR
#define SAFE_DELARR(p) {if(p!=NULL) {delete []p;p=NULL;}}
#endif

#ifndef SAFE_DELOBJ
#define SAFE_DELOBJ(p) {if(p!=NULL) {DeleteObject(p);p=NULL;}}
#endif

#ifndef SAFE_DELDC
#define SAFE_DELDC(p) {if(p!=NULL) {DeleteDC(p);p=NULL;}}
#endif

#ifndef SAFE_RELEASEDC
#define SAFE_RELEASEDC(w,p) {if((p!=NULL)&&(w!=NULL)) {ReleaseDC(w,p);p=NULL;}}
#endif

#define IDBTN_CLOSE -1

enum GuiState {
	GUIBTN_UP,
	GUIBTN_DOWN,
	GUIBTN_ON
};

enum EngineState_Bool
{
	ENGINESTATE_FULLSCREEN
};

enum EngineState_Fp
{
	ENGINESTATE_UPDATEFUNC,
	ENGINESTATE_RENDERFUNC
};

enum EngineState_String
{
	ENGINESTATE_TITELNAME,
	ENGINESTATE_CURSOR,
	ENGINESTATE_ICON
};

enum EngineState_Handle
{
	ENGINESTATE_HCURSOR,
	ENGINESTATE_HICON,
	ENGINESTATE_GUIMANAGE,
	ENGINESTATE_GUIPROCE
};

typedef bool (*FUNCPOINT)(void);
typedef void (*TIMERPOINT)(void);
typedef void (*GUIPROCE)(UINT Msg,UINT Param1,UINT Param2);

BOOL MyAlphaBlend(HDC DestHdc,int x,int y,HDC SrcHdc,
				  float DestBlendValue,float SrcBlendValue,COLORREF MaskColor);

struct TimerData
{
	TIMERPOINT pProc;
	float ElapseTime;
	float Time;
	bool IsUse;
};

#define GDIENGINES_FULLSCREEN 0x00000001

class GdiEngine;
class GuiManage;
class GuiObject;
class GuiButton;
class GuiEdit;
class GuiStaticText;
class GuiDailogBox;

struct GuiButtonData
{
	GuiButtonData()
	{
		InResource=false;
		dwId=0;
		_3State=false;
		IsAnimation=false;
		pParent=NULL;
		DownImage=NULL;
		UpImage=NULL;
		OnImage=NULL;
		CtrlName=NULL;
		Pos.x=0;
		Pos.x=0;
		FrameWidth=0;
		FrameHeight=0;
		Fps=0;
		Frames=0;
		IsSpriter=false;
		MaskColor=RGB(0,0,0);
	}
	bool InResource;
	DWORD dwId;
	bool _3State;
	bool IsAnimation;
	GuiObject *pParent;
	char const *DownImage;
	char const *UpImage;
	char const *OnImage;
	char const *CtrlName;
	POINT Pos;
	UINT FrameWidth;
	UINT FrameHeight;
	UINT Fps;
	UINT Frames;
	bool IsSpriter;
	COLORREF MaskColor;
};

struct GuiEditData
{
	GuiEditData()
	{
		InResource=false;
		dwId=0;
		IsAnimation=false;
		pParent=NULL;
		BackImage=NULL;
		CtrlName=NULL;
		Pos.x=0;
		Pos.x=0;
		FrameWidth=0;
		FrameHeight=0;
		Fps=0;
		Frames=0;
		IsSpriter=false;
		MaskColor=RGB(0,0,0);
	}
	bool InResource;
	DWORD dwId;
	bool IsAnimation;
	GuiObject *pParent;
	char const *BackImage;
	char const *CtrlName;
	POINT Pos;
	UINT FrameWidth;
	UINT FrameHeight;
	UINT Fps;
	UINT Frames;
	bool IsSpriter;
	COLORREF MaskColor;
};

struct GuiStaticTextData
{
	GuiStaticTextData()
	{
		dwId=0;
		pParent=NULL;
		CtrlName=NULL;
		Pos.x=0;
		Pos.x=0;
		ZeroMemory(&Logfont,sizeof(Logfont));
		TextColor=RGB(0,0,0);
	}
	DWORD dwId;
	GuiObject *pParent;
	char const *CtrlName;
	POINT Pos;
	LOGFONT Logfont;
	COLORREF TextColor;
};

struct GuiDailogBoxData
{
	GuiDailogBoxData()
	{
		InResource=false;
		dwId=0;
		pParent=NULL;
		LeftTopImage=NULL;
		TopCenterImage=NULL;
		RightTopImage=NULL;
		RightCenterImage=NULL;
		RightDownImage=NULL;
		DownCenterImage=NULL;
		LeftDownImage=NULL;
		LeftCenterImage=NULL;
		MidCenterImage=NULL;
		CloseBtnUpImage=NULL;
		CloseBtnDownImage=NULL;
		CtrlName=NULL;
		Pos.x=0;
		Pos.x=0;
		Width=100;
		Height=0;
		IsSpriter=false;
		MaskColor=RGB(0,0,0);
	}
	bool InResource;
	DWORD dwId;
	GuiObject *pParent;
	char const *LeftTopImage;
	char const *TopCenterImage;
	char const *RightTopImage;
	char const *RightCenterImage;
	char const *RightDownImage;
	char const *DownCenterImage;
	char const *LeftDownImage;
	char const *LeftCenterImage;
	char const *MidCenterImage;
	char const *CloseBtnUpImage;
	char const *CloseBtnDownImage;
	char const *CtrlName;
	POINT Pos;
	UINT Width;
	UINT Height;
	bool IsSpriter;
	COLORREF MaskColor;
};

#include "GdiSpriter.h"
#include "GdiSpriterAlpha.h"
#include "GdiFrameAnimation.h"

#include "GuiObject.h"
#include "GuiManage.h"

#include "GuiButton.h"
#include "GuiEdit.h"
#include "GuiStaticText.h"
#include "GuiDailogBox.h"


#include "GdiEngine.h"

#endif