#include "AllDefine.h"

#ifndef HERO
#define HERO

class Hero : public BaseObject
{
public:
	Hero( PTEXTURE tex, bool isMask, COLORREF maskColor );

	virtual void Init()
	{
	}
	virtual void Update();

private:
	void _ProcessInput();
};

#endif	// END HERO
