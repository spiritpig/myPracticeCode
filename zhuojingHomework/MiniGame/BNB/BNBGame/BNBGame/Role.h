#include "commonHeader.h"

#ifndef ROLE
#define ROLE

class Role
{
public:
	Role(void);
	~Role(void);

	virtual void Init( GameMap *pMap );
	virtual void Update() = 0;
	virtual void Render();

protected:
	virtual void _ProcessInput() = 0;
	virtual void _KeepRoleInScreenRange( Vec2D &pos );
	bool _IsHitZhangAiWu_Left();
	bool _IsHitZhangAiWu_Right();
	bool _IsHitZhangAiWu_Top();
	bool _IsHitZhangAiWu_Bottom();
	void _PathAdjust_HorziMove( const Vec2D &tempPos );
	void _PathAdjust_VertiMove( const Vec2D &tempPos );

	Sgge *m_pEngine;
	PSTEXTURE m_pRoleTex;
	GameMap *m_pMap;
	ROLE_STATE m_RoleState;
	RoleData m_RoleData;
};

#endif	// END ROLE
