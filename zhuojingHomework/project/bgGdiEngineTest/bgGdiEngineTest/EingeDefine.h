#include <Windows.h>
#include <tchar.h>
#include <vld.h>
#include <vector>
#include <list>
using namespace std;
#pragma comment( lib, "GdiEngine.lib" )

#ifndef AFX_ENGINEDEFINE
#define AFX_ENGINEDEFINE

typedef bool (*Funcp)(void);

#define FAMODE_FRONT 0x00
#define FAMODE_BACK 0x01
#define FAMODE_LOOP 0x00
#define FAMODE_NOLOOP 0x02
#define FAMODE_NOPINGPONG 0x00
#define FAMODE_PINGPONG 0x04

typedef void *PSTEXTURE;
typedef void *PSMUSIC;

enum Einge_State_Fp
{
	EINGNES_UPDATEFUNC,
	EINGNES_RENDERFUNC
};

enum Einge_State_Int
{
	EINGNES_SCREENWIDTH,
	EINGNES_SCREENHIGH,
	EINGNES_ICONID,
	EINGNES_SMICONID,
	EINGNES_CURSORID
};

enum Einge_State_Void
{
	EINGNES_HICON,
	EINGNES_HSMICON,
	EINGNES_HCURSOR
};

enum Einge_State_String
{
	EINGNES_TITLENAME,
	EINGNES_FNICON,
	EINGNES_FNSMICON,
	EINGNES_FNCURSOR
};

enum Einge_State_Bool
{
	EINGNES_SHOWCURSOR,
	EINGNES_FULLSCREEN
};

enum UiType
{
	UT_NOTDEFINE,
	UT_BUTTON,
	UT_EDIT,
	UT_STATICTEXT,
	UT_SRCOLLBAR
};

#define UIID_NOTUSED -2
#define UIID_STATIC -1

#define UIAN_SETFOUCE 0
#define UIAN_KILLFOUCE 1
#define UIBN_CLICKED 2
#define UIEN_TEXTCHANGE 3
#define UISBN_MOVE 4

class UiObject;
struct UiMsg
{
	unsigned int Id;
	unsigned int msg;
	unsigned int fParam;
	UiObject *pUiObject;
};

class UiManage;
#include "GdiEinge.h"
#include "Sprite.h"
#include "FrameAnimate.h"
#include "UiObject.h"
#include "UiButton.h"
#include "UiEdit.h"
#include "UiStaticText.h"
#include "UiSrocllBar.h"
#include "UiManage.h"

#endif