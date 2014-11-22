#include "commonHeader.h"

#ifndef PLAYER
#define PLAYER

class Player : public Role
{
public:
	Player(void);
	~Player(void);

	virtual void Init( int row, int cel, GameMap *pMap );
	virtual void Update();

private:
	virtual void _ProcessInput();

	PlayerData m_PlayerData;
};

#endif	// END PLAYER
