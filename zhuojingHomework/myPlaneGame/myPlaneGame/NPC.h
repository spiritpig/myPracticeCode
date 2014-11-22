#include "commonHeader.h"

#ifndef NPC_AFX
#define NPC_AFX

class npc
{
public:
	npc(void);
	~npc(void);

	void init();
	void update( float mapLen );
	void render( float mapLen );

private:
	void _processInput( float mapLen );
	void _adjustBulletPos( bulletState &blState, float mapLen );
	void _adjustDaodanPos( daodanState &ddState, float mapLen );

private:
	Sgge *m_pSgge;

	// 玩家数据集
	PSTEXTURE m_pNPCTextrue;
	SggeSprite *m_pNPCSpr;
	float m_NPCScalePercent;
	dijiState m_npcData;
};

#endif // END NPC_AFX