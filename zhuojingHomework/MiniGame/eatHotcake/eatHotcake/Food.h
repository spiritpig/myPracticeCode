#include "AllDefine.h"

#ifndef FOOD
#define FOOD

class Food : public BaseObject
{
public:
	Food( PTEXTURE tex, bool isMask, COLORREF maskColor );
	~Food(void);

	virtual void Init()
	{
	}
};

#endif	// END FOOD
