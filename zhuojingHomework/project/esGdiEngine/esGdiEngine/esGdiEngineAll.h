#ifndef ES_GDIENGINE_ALL
#define ES_GDIENGINE_ALL

#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <vector>
#include <list>
using std::vector;
using std::list;

#define SAFE_DELETE(p) { if(p) { delete p; p=NULL; } }
#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }

typedef void *PESDC;
typedef void *PESWND;
typedef void *PESINSTANCE;
typedef void *PTEXTURE;

typedef bool (*UpdateFunc) ( void );
typedef bool (*RenderFunc) ( void );

// Ö¡¶¯»­Ä£Ê½
#define FA_LOOP			0x00
#define FA_NOLOOP		0x01
#define FA_NOPINGPONG	0x00
#define FA_PINGPONG		0x02
#define FA_FRONT		0x00
#define FA_BACK			0x04

enum UI_TYPE
{
	UT_NULL,
	UT_EDIT,
	UT_BUTTON,
	UT_STATIC,
	UT_SCROLLBAR
};

enum UI_STATIC_CONTENT_TYPE
{
	USCT_TEXT,
	USCT_IMAGE
};

struct egePoint
{
	int x;
	int y;
};

class egeUiManager;
#include "esGdiEngine.h"
#include "egeSprite.h"
#include "egeFrameAnimation.h"
#include "egeUiObject.h"
#include "egeUiStatic.h"
#include "egeUiButton.h"
#include "egeUiEdit.h"
#include "egeScrollBar.h"
#include "egeUiManager.h"

#endif	// END ES_GDIENGINE_ALL
