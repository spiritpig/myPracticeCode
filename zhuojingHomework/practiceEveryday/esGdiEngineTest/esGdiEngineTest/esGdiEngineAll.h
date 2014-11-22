#ifndef ES_GDIENGINE_ALL
#define ES_GDIENGINE_ALL

#define SAFE_DELETE(p) { if(p) { delete p; p=NULL; } }
#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }

typedef void *PESDC;
typedef void *PESWND;
typedef void *PESINSTANCE;
typedef void *PTEXTURE;

typedef bool (*UpdateFunc) ( void );
typedef bool (*RenderFunc) ( void );

#define FA_LOOP			0x00
#define FA_NOLOOP		0x01
#define FA_NOPINGPONG	0x00
#define FA_PINGPONG		0x02
#define FA_FRONT		0x00
#define FA_BACK			0x04

#include "esGdiEngine.h"
#include "egeSprite.h"
#include "egeFrameAnimation.h"

#endif	// END ES_GDIENGINE_ALL
